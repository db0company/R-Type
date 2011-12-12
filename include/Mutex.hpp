#ifndef MUTEX_HPP_
#define MUTEX_HPP_

class Mutex
{
  pthread_mutex_t _mutex;

public:
  Mutex();
  Mutex(const Mutex &m);
  ~Mutex();
  bool lock();
  bool unlock();
  bool trylock();
  pthread_mutex_t *getMutex();
};


#endif
