#include "ThreadData.hpp"
#include "PacketTask.hpp"

template <typename T>
ThreadData<T>::ThreadData(SafeQueue<T> &sq, ICondVar *cv)
  :QueueTask(sq), condVar(cv)
{
}

template <typename T>
ThreadData<T>::~ThreadData()
{
}

template class ThreadData<PacketTask>;
