#include "ThreadData.hpp"
#include "IThread.hpp"
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
}

bool ThreadPool::init(ThreadData *data)
{
  std::list<IThread *>::iterator it;

  it = listThread.begin();
  while (it != listThread.end())
    {
      if (it->Create(&manageThread, reinterpret_cast<void *>(data)) == false)
	return (false);
      it++;
    }
  return (true);
}


bool ThreadPool::addNewThread(ThreadData *data)
{
}

bool ThreadPool::endThread()
{
  std::list<IThread *>::iterator it;

  it = listThread.begin();
  while (it != listThread.end())
    {
      if (it->Wait() == false)
	return (false);
      it++;
    }
  return (true);
}




void		*manageThread(void *param)
{
  ThreadData	*data;

  data = reinterpret_cast<ThreadData *>(param);
  while (1)
    {
    }
 
}
