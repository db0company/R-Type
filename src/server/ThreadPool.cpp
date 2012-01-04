#include <iostream>
#include "PacketTask.hpp"
#include "ThreadData.hpp"
#include "IThread.hpp"
#include "ThreadPool.hpp"
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

template <typename T>
bool ThreadPool::init(ThreadData<T> *data)
{
  std::list<IThread *>::iterator it;

  it = listThread.begin();
  while (it != listThread.end())
    {
      if ((*it)->Create(&ThreadPool::manageThread<T>, reinterpret_cast<void *>(data)) == false)
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

template <typename T>
void		*ThreadPool::manageThread(GParam *param)
{
  ThreadData<T>	*data;

  data = reinterpret_cast<ThreadData<T> *>(param);
  while (1)
    {
      if (data->QueueTask.empty() == false)
	{
	  T task = NULL;
	  task = data->QueueTask.tryPop();
	  if (task != NULL)
	    task->launchTask(data->condVar);
	}
      else
	{
	  std::cout << "jattend" << std::endl;
	data->condVar->wait();
	}
    }
  return (NULL);
}

template void		*ThreadPool::manageThread<PacketTask *>(void *param);
template bool ThreadPool::init<PacketTask *>(ThreadData<PacketTask *> *data);
