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

template <typename T>
ThreadData<T>::ThreadData(const ThreadData<T>& old)
  :QueueTask(old.QueueTask), condVar(old.condVar)
{
}

template <typename T>
void ThreadData<T>::ExecParam()
{
  while (1)
    {
      if (this->QueueTask.empty() == false)
	{
	  std::cout << "time to exec task" << std::endl;
	  T task = NULL;
	  task = this->QueueTask.tryPop();
	  if (task != NULL)
	    task->launchTask(this->condVar);
	}
      else
	{
	  //	   std::cout << "jattend" << std::endl;
	  this->condVar->wait();
	}
    }
}


template struct ThreadData<PacketTask *>;
