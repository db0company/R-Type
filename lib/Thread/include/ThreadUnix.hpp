#ifndef _THREAD_UNIX_HPP_
#define _THREAD_UNIX_HPP_

#include <pthread.h>
#include "IThread.hpp"

class ThreadUnix : public IThread
{
public:
  ThreadUnix(void);
  ThreadUnix(ThreadUnix const &);
  ThreadUnix &operator=(ThreadUnix const &);
  virtual ~ThreadUnix(void);
  virtual bool Create(generic *(*pfonct)(generic *), generic *t);
  virtual bool operator()(generic *(*pfonct)(generic *), generic *t);
  virtual bool Destroy(void);
  virtual bool Wait(void);
  virtual eThreadState getState(void) const;
private:
  eThreadState	_state;
  pthread_t	_thread;
};

#endif //_THREAD_UNIX_HPP_
