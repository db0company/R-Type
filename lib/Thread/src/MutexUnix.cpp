#include <pthread.h>
#include "MutexUnix.hpp"

MutexUnix::MutexUnix(void)
{
  if (pthread_mutex_init(&this->_mutex, NULL) != 0)
    {
      ;//error
    }
}

MutexUnix::~MutexUnix(void)
{
  int	ret;

  ret = pthread_mutex_destroy(&this->_mutex);
  if (ret != 0)
    {
    ;//error
    }
}

bool MutexUnix::Lock(void)
{
  int	ret;

  ret = pthread_mutex_lock(&this->_mutex);
  if (ret != 0)
    return (false);
  return (true);
}

bool MutexUnix::Unlock(void)
{
  int	ret;

  ret = pthread_mutex_unlock(&this->_mutex);
  if (ret != 0)
    return (false);
  return (true);
}

bool MutexUnix::Try(void)
{
  int	i;

  i = pthread_mutex_trylock(&this->_mutex);
  if (i != 0)
    return (false);
  return (true);
}
