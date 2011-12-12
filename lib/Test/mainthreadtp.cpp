#include <iostream>
#include <queue>
#include <string>
#include "IThread.hpp"
#include "IMutex.hpp"
#ifndef _WIN32
# include "MutexUnix.hpp"
# include "ThreadUnix.hpp"
#else
# include "MutexWindows.hpp"
# include "ThreadWindows.hpp"
#endif

class SafeQueue
{
public:
  SafeQueue(void) : w()
  {
#ifndef _WIN32
    this->w = new MutexUnix;
#else
    this->w = new MutexWindows;
#endif
    queue.push("coucou lol");
    queue.push("salut");
    queue.push("j'aime les poney");
    queue.push("prout");
    queue.push("windows sa suxx");
    queue.push("epitech c'est naaaaaze");
    queue.push("le status dAE encore plus");
  }
  ~SafeQueue(void)
  {
  }
  std::queue<std::string> queue;
  IMutex *w;
};


void *toto(void *lol)
{
  SafeQueue *queue;
  std::string s;
  queue = reinterpret_cast<SafeQueue *>(lol);
  if (queue->w->Try())
    {
      if (!queue->queue.empty())
	{
	  s = queue->queue.front();
	  queue->queue.pop();
	  std::cout << s;
	  std::cout << std::endl;
	}
      queue->w->Unlock();
    }
  return (0);
};

#define THREAD_NB 10

int main()
{
  SafeQueue safe;
  IThread *tab[THREAD_NB];
  IMutex  *mutex;

#ifndef _WIN32
  mutex = new MutexUnix;
#else
  mutex = new MutexWindows;
#endif
  int i = 0;
  safe.w->Lock(); // here
  while (!safe.queue.empty())
    {
      safe.w->Unlock();
      for (i = 0; i < THREAD_NB; ++i)
	{
#ifndef _WIN32
	  tab[i] = new ThreadUnix;
#else
	  tab[i] = new ThreadWindows;
#endif
	  tab[i]->Create(&toto, &safe);
	}
      for (i = 0; i < THREAD_NB; ++i)
	tab[i]->Wait();
      safe.w->Lock();
    }
  safe.w->Unlock();
  for (i = 0; i < THREAD_NB; ++i)
    {
      tab[i]->Destroy();
    }
  std::cout << "== fin du test ==" <<std::endl;
#ifdef _WIN32
  system("pause");
#endif
  return (0);
}
