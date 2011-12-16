#include "SafeQueue.hpp"

template <typename T>
SafeQueue<T>::SafeQueue()
{
}

SafeQueue<T>::SafeQueue(SafeQueue &old)
{
  this->QueueTask = old.QueueTask;
  this->mutex = old.mutex;
}

SafeQueue &SafeQueue<T>::operator=(SafeQueue &old)
{
  this->QueueTask = old.QueueTask;
  this->mutex = old.mutex;
}

template <typename T>
SafeQueue<T>::~SafeQueue()
{
}

template <typename T>
bool SafeQueue<T>::push(T value)
{
  QueueTask.push(value);
}

template <typename T>
bool SafeQueue<T>::tryPop(T *elem)
{
  mutex->Lock();
  if (!QueueTask.empty())
    {
      elem = QueueTask.front();
      QueueTask.pop();
      return (true);
    }
  mutex->Unlock;
  return (false);
}

template <typename T>
bool SafeQueue<T>::empty()
{
 mutex->Lock();
  if (QueueTask.empty())
    {
      mutex->Unlock;
      return (true);
    }
  mutex->Unlock;
  return (false);
}
