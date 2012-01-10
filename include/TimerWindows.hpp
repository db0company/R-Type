#ifndef		__TIMERWINDOWS_HPP__
# define	__TIMERWINDOWS_HPP__

#include <Windows.h>
#include "ITimer.hpp"

class		TimerWindows : ITimer
{
private:
  DWORD	start_time;
  DWORD	time_to_wait;
public:

  TimerWindows();
  virtual ~TimerWindows();
  DWORD	getTime()const;
  virtual bool isTimeOut()const;
  virtual void	initWait(unsigned int sec, unsigned int milli);
  virtual void resetTime();
};

#endif		/*__TIMERUNIX_HPP__*/
