#ifndef		__TIMERUNIX_HPP__
# define	__TIMERUNIX_HPP__

#include "ITimer.hpp"

class		TimerUnix : public ITimer
{
private:
  double	start_time;
  double	time_to_wait;
public:
  TimerUnix();
  virtual ~TimerUnix();
  double	getTime()const;
  virtual bool isTimeOut()const;
  virtual void	initWait(unsigned int sec, unsigned int milli);
  virtual void resetTime();
};

#endif		/*__TIMERUNIX_HPP__*/
