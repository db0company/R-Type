
#include <pthread.h>

#ifndef THREAD_HPP_
#define THREAD_HPP_

enum ThreadState
  {
    OFF,
    ON,
    DEAD
  };

class Thread
{
  pthread_t _thread;
  ThreadState state;
public:
  Thread();
  ~Thread();
  bool CreatThread(void * (*ptr)(void *), void * arg);
  bool operator()(void * (*ptr)(void *), void * arg);
  bool ThreadJoin();
  ThreadState GetThreadState()const;
};


#endif
