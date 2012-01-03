#ifndef __THREADDATA_HPP__
#define __THREADDATA_HPP__

#include "SafeQueue.hpp"
#include "ICondVar.hpp"


template <typename T>
struct ThreadData
{
  SafeQueue<T> &QueueTask;
  ICondVar *condVar;
  ThreadData();
  ThreadData(SafeQueue<T>&, ICondVar *);
  ~ThreadData();
};

#endif // __THREADDATA_HPP__
