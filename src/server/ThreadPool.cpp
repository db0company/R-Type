#include <iostream>
#include "PacketTask.hpp"
#include "ThreadData.hpp"
#include "IThread.hpp"
#include "ThreadPool.hpp"
#include "ExecThread.hpp"
#ifdef _WIN32
#include "ThreadWindows.hpp"
#else
#include "ThreadUnix.hpp"
#endif


ThreadPool::ThreadPool(int nbThread)
{
#ifdef _WIN32
  for (int i = 0; i < nbThread; ++i)
 listThread.push_front(new ThreadWindows);
#else
  for (int i = 0; i < nbThread; ++i)
    listThread.push_front(new ThreadUnix);
#endif
}

ThreadPool::~ThreadPool()
{
  this->endThread();
}

bool ThreadPool::init(IThreadData *data)
{
  std::list<IThread *>::iterator it;
  IExec *exec = new ExecThread<IThreadData *>(data);
  it = listThread.begin();
  while (it != listThread.end())
    {
      if ((*it)->Create(exec) == false)
	return (false);
      it++;
    }
  return (true);
}


bool ThreadPool::endThread()
{
  std::list<IThread *>::iterator it;

  it = listThread.begin();
  while (it != listThread.end())
    {
      if ((*it)->Wait() == false)
	return (false);
      it++;
    }
  return (true);
}
