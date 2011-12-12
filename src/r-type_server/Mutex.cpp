#include "Mutex.hpp"

Mutex::Mutex()
{
  if (pthread_mutex_init(&this->_mutex, NULL) != 0)
    ;//error
}

Mutex::Mutex(const Mutex &m)
{
  this->_mutex = m._mutex;
}
Mutex::~Mutex()
{
  int	ret;

  ret = pthread_mutex_destroy(&this->_mutex);
  if (ret != 0)
    ;//error
}

bool	Mutex::lock()
{
  int	ret;

  ret = pthread_mutex_lock(&this->_mutex);
  if (ret != 0)
    return (false);
  return (true);
}

bool Mutex::unlock()
{
  int	ret;

  ret = pthread_mutex_unlock(&this->_mutex);
  if (ret != 0)
    return (false);
  return (true);
}

bool Mutex::trylock()
{
  int	i;

  i = pthread_mutex_trylock(&this->_mutex);
  if (i != 0)
    return (false);
  return (true);
}

pthread_mutex_t *Mutex::getMutex()
{
  return (&_mutex);
}
