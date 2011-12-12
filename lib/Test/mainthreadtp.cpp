#include <iostream>
#include <queue>
#include <string>
#include "IThread.hpp"
#include "IMutex.hpp"
#include "MutexWindows.hpp"
#include "ThreadWindows.hpp"

class SafeQueue
{
public:
	SafeQueue(void) : w()
	{
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
	MutexWindows w;
};


void *toto(void *lol)
{
	SafeQueue *queue;
	std::string s;
	queue = reinterpret_cast<SafeQueue *>(lol);
	if (queue->w.Try())
	{
	if (!queue->queue.empty())
	{
	s = queue->queue.front();
	queue->queue.pop();
	std::cout << s;
	std::cout << std::endl;
	queue->w.Unlock();
	}
	}
	return (0);
};

#define THREAD_NB 10

int main()
{
	SafeQueue safe;
	ThreadWindows tab[THREAD_NB];
	MutexWindows  mutex;
	int i = 0;
	safe.w.Lock();
	while (!safe.queue.empty())
	{
	safe.w.Unlock();
	for (i = 0; i < THREAD_NB; ++i)
	{
		tab[i].Create(&toto, &safe);
	}
	for (i = 0; i < THREAD_NB; ++i)
		tab[i].Wait();
	safe.w.Lock();
	}
	safe.w.Unlock();
	for (i = 0; i < THREAD_NB; ++i)
	{
		tab[i].Destroy();
	}
	std::cout << "fin" << std::endl;
	system("pause");
	return (0);
}