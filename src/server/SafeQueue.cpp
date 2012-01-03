#ifdef _WIN32
# include "MutexWindows.hpp"
#else
# include "MutexUnix.hpp"
#endif

#include <iostream>
#include "SafeQueue.hpp"
#include "ScopedLock.hpp"
#include "PacketTask.hpp"

template <typename T>
SafeQueue<T>::SafeQueue()
{
#ifdef _WIN32
  this->mutex = new MutexWindows;
#else
  this->mutex = new MutexUnix;
#endif
}

template <typename T>
SafeQueue<T>::SafeQueue(SafeQueue<T> &old)
{
  this->QueueTask = old.QueueTask;
  this->mutex = old.mutex;
}

template <typename T>
SafeQueue<T> &SafeQueue<T>::operator=(SafeQueue<T> &old)
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

  if (QueueTask.empty() == false)
    {
      *elem = QueueTask.front();
      QueueTask.pop();
      return (true);
    }
  return (false);
}

template <typename T>
bool SafeQueue<T>::empty()
{
  ScopedLock sl(this->mutex);

  if (QueueTask.empty() == true)
    return (true);
  return (false);
}

template class SafeQueue<PacketTask>;
