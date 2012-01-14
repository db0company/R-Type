#include <iostream>
#include "TimerWindows.hpp"

TimerWindows::TimerWindows()
{
  this->start_time = 0;
  this->time_to_wait = 0;
}

TimerWindows::~TimerWindows()
{

}

bool TimerWindows::isTimeOut()const
{
  if (this->start_time == 0 || this->time_to_wait == 0)
    {
      std::cerr << "ERROR GETTIMEOFDAY" << std::endl;
      return (true);
    }
  else if ((this->start_time + this->time_to_wait) < getTime())
    return (true);
 return (false);
}

DWORD	TimerWindows::getTime()const
{
  DWORD tmp;
  
  if ((tmp = GetTickCount())  == -1)
    std::cerr << "ERROR GETTIMEOFDAY" << std::endl;
  return (tmp);
}
  
void	TimerWindows::initWait(unsigned int sec, unsigned int milli)
{	
  DWORD tmp;

  tmp = getTime();
  this->time_to_wait = sec * 1000 + milli / 1000;
}

void TimerWindows::resetTime()
{
  this->start_time = getTime();
}
