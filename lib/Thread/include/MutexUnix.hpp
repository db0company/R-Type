#ifndef __MUTEX_UNIX_HPP__
#define  __MUTEX_UNIX_HPP__

#include <pthread.h>
#include "IMutex.hpp"

class MutexUnix : public IMutex
{
public:
  MutexUnix(void);
  virtual ~MutexUnix(void);
  virtual bool Lock(void);
  virtual bool Unlock(void);
  virtual bool Try(void);
private:
  pthread_mutex_t _mutex;
};

#endif //  __MUTEX_UNIX_HPP__
