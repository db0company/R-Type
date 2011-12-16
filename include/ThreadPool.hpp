#ifndef __THREADPOOL_HPP_
#define __THREADPOLL_HPP_

#include <list>
#include "IThread.hpp"
#include "ThreadData.hpp"

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

#endif // __THREADPOOL_HPP_
