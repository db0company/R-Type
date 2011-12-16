#include "ThreadData.hpp"
#include "IThread.hpp"
#include "ThreadPool.hpp"
#ifdef _WIN32
#include "ThreadWindows.hpp"
#else
#include "ThreadUnix.hpp"   
#endif

template <typename T>
ThreadPool<T>::ThreadPool(int nbThread)
{

#ifdef _WIN32
  for (int i = 0; i < nbThread; ++i)
 listThread.push_front(new ThreadWindows);
#else
  for (int i = 0; i < nbThread; ++i)
    listThread.push_front(new ThreadUnix);
#endif
}

template <typename T>
ThreadPool<T>::~ThreadPool()
{
}

template <typename T>
bool ThreadPool<T>::init(T *data)
{
  std::list<IThread *>::iterator it;

  it = listThread.begin();
  while (it != listThread.end())
    {
      if ((*it)->Create(&manageThread<T>, reinterpret_cast<void *>(data)) == false)
	return (false);
      it++;
    }
  return (true);
}

template <typename T>
bool ThreadPool<T>::addNewThread(T *data)
{
  return (true);
}

template <typename T>
bool ThreadPool<T>::endThread()
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
void		*manageThread(void *param)
{
  T	*data;

  data = reinterpret_cast<T *>(param);
  while (1)
    {
    }

  return (NULL); 
}
