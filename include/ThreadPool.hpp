#ifndef __THREADPOOL_HPP_
#define __THREADPOLL_HPP_

#include <list>
#include "IThread.hpp"
#include "ThreadData.hpp"

#define POOL_NBTHREAD 4

template <typename T>
class ThreadPool
{
private:
  std::list<IThread *> listThread;
public:
  ThreadPool(int nbThread);
  ~ThreadPool();
  bool init(T *data);
  bool addNewThread(T *data);
  bool endThread();
};

template <typename T>
void		*manageThread(void *param);

//template class ThreadPool<ThreadData>;

#endif // __THREADPOOL_HPP_
