#ifndef __THREADPOOL_HPP_
#define __THREADPOLL_HPP_

#include <list>
#include "IThread.hpp"
#include "ThreadData.hpp"

#define POOL_NBTHREAD 6


class ThreadPool
{
private:
  std::list<IThread *> listThread;
public:
  ThreadPool(int nbThread);
  ~ThreadPool();
  template <typename T>
  bool init(ThreadData<T> *data);
  bool endThread();
};

template <typename T>
void		*manageThread(void *param);



#endif // __THREADPOOL_HPP_
