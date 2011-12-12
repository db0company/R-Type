#ifndef _THREAD_WINDOWS_HH_
#define  _THREAD_WINDOWS_HH_

#include <windows.h>
#include "IThread.hpp"

class ThreadWindows : public IThread
{
public:
  ThreadWindows(void);
  virtual ~ThreadWindows(void);
  virtual bool Create(void *(*pfonct)(void *), void *t);
  virtual bool operator()(void *(*pfonct)(void *), void *t);
  virtual bool Destroy(void);
  virtual bool Wait(void);
  virtual eThreadState getState(void) const;

private:
  DWORD _threadId;
  HANDLE _handle;
  eThreadState _state;
};

#endif //_THREAD_WINDOWS_HH_
