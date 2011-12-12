
#include "Thread.hpp"

Thread::Thread()
  : state(OFF)
{
}

Thread::~Thread()
{
}

bool	       Thread::CreatThread(void * (*ptr)(void *), void * arg)
{
  if (pthread_create(&this->_thread, NULL, ptr, arg) != 0)
    return (false);
  state = ON;
  return (true);
}
bool		Thread::operator()(void * (*ptr)(void *), void * arg)
{
  if (pthread_create(&this->_thread, NULL, ptr, arg) != 0)
    return (false);
  this->state = ON;
  return (true);
}
bool		Thread::ThreadJoin()
{
  void *res;

  if (pthread_join(this->_thread, &res) != 0)
    return (false);
  state = DEAD;
    return (false);
}

ThreadState Thread::GetThreadState()const
{
  return (state);
}

