
#ifndef __SAFEQUEUE_HPP__
#define  __SAFEQUEUE_HPP__

#include <queue>
#include "IMutex.hpp"

template <typename T>
class SafeQueue
{
private:
  std::queue<T> QueueTask;
  IMutex *mutex;
public:
  SafeQueue();
  SafeQueue(SafeQueue<T> &old);
  SafeQueue &operator=(SafeQueue<T> &old);
  ~SafeQueue();
  bool push(T value);
  T tryPop();
  bool empty();
};

#endif // __SAFEQUEUE_HPP__
