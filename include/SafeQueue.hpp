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
  SafeQueue(SafeQueue &old);
  SafeQueue &operator=(SafeQueue &old);
  ~SafeQueue();
  bool push(T value);
  bool tryPop(T *elem);
  bool empty();
};

#endif // __SAFEQUEUE_HPP__
