#ifndef __THREADDATA_HPP__
#define __THREADDATA_HPP__

#include "SafeQueue.hpp"
#include "ICondVar.hpp"
#include "IThreadData.hpp"

template <typename T>
struct ThreadData : public IThreadData
{
  SafeQueue<T> &QueueTask;
  ICondVar *condVar;
  ThreadData(const ThreadData& old);
  ThreadData(SafeQueue<T>&, ICondVar *);
  ~ThreadData();
  void ExecParam();

};

#endif // __THREADDATA_HPP__
