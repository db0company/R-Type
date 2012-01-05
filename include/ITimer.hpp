#ifndef		__ITIMER_HPP__
# define	__ITIMER_HPP__

class		ITimer
{
public:
  virtual ~ITimer() {}
  virtual bool isTimeOut()const = 0;
  virtual void	initWait(unsigned int sec, unsigned int milli) = 0;
  virtual void resetTime() = 0;
};

#endif		/*__ITIMER_HPP__*/
