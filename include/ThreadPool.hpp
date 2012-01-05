#ifndef __THREADPOOL_HPP_
#define __THREADPOLL_HPP_

#include <list>
#include "IThread.hpp"
#include "ThreadData.hpp"

#define POOL_NBTHREAD 6

typedef generic GParam;

class ThreadPool
{
private:
  std::list<IThread *> listThread;
public:
  ThreadPool(int nbThread);
  ~ThreadPool();
  bool init(IThreadData *data);
  bool endThread();
};





#endif // __THREADPOOL_HPP_
