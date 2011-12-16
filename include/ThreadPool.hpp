#ifndef __THREADPOOL_HPP_
#define __THREADPOLL_HPP_

#include <list>
#include "Thread.hpp"
#include "ThreadData.hpp"
class ThreadPool
{
private:
  std::list<IThread *> listThread;
public:
  ThreadPool(int nbThread);
  ~ThreadPool();
  bool init(ThreadData *data);
  bool addNewThread(ThreadData *data);
  bool endThread();
};

#endif // __THREADPOOL_HPP_
