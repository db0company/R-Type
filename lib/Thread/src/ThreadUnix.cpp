#include <pthread.h>
#include "ThreadUnix.hpp"

ThreadUnix::ThreadUnix(void) :
  _state(OFF)
{
}

ThreadUnix::~ThreadUnix(void)
{
}

bool ThreadUnix::Create(void *(*pfonct)(void *), void *t)
{
  if (pthread_create(&this->_thread, NULL, pfonct, t) != 0)
    return (false);
  this->_state = ON;
  return (true);
}

bool ThreadUnix::operator()(void *(*pfonct)(void *), void *t)
{
  if (pthread_create(&this->_thread, NULL, pfonct, t) != 0)
    return (false);
  this->_state = ON;
  return (true);
}

bool ThreadUnix::Destroy(void)
{
  if (pthread_cancel(this->_thread) == 0)
    return (true);
  return (false);
}

bool ThreadUnix::Wait(void)
{
  void *res;

  if (pthread_join(this->_thread, &res) != 0)
    return (false);
  this->_state = DEAD;
  return (false);
}

eThreadState ThreadUnix::getState(void) const
{
  return (this->_state);
}

