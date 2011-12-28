#include "SafeQueue.hpp"
#include "ScopedLock.hpp"

template <typename T>
SafeQueue<T>::SafeQueue()
{
}

template <typename T>
SafeQueue<T>::SafeQueue(SafeQueue &old)
{
  this->QueueTask = old.QueueTask;
  this->mutex = old.mutex;
}

template <typename T>
SafeQueue<T> &SafeQueue<T>::operator=(SafeQueue &old)
{
  this->QueueTask = old.QueueTask;
  this->mutex = old.mutex;
  return (*this);
}

template <typename T>
SafeQueue<T>::~SafeQueue()
{
}

template <typename T>
bool SafeQueue<T>::push(T value)
{
  ScopedLock sl(this->mutex);

  QueueTask.push(value);
  return (true);
}

template <typename T>
bool SafeQueue<T>::tryPop(T *elem)
{
  ScopedLock sl(this->mutex);

  if (!QueueTask.empty())
    {
      elem = QueueTask.front();
      QueueTask.pop();
      return (true);
    }
  return (false);
}

template <typename T>
bool SafeQueue<T>::empty()
{
  ScopedLock sl(this->mutex);

  if (QueueTask.empty())
    return (true);
  return (false);
}
