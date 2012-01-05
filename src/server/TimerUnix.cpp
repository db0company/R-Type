#include <iostream>
#include <cstdio>
#include <sys/time.h>
#include <ctime>
#include <cmath>
#include "TimerUnix.hpp"

TimerUnix::TimerUnix()
{
  this->start_time = 0;
  this->time_to_wait = 0;
}

TimerUnix::~TimerUnix()
{

}

bool TimerUnix::isTimeOut()const
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

double	TimerUnix::getTime()const
{
  struct timeval	t;
  double tmp;
  
  if (gettimeofday(&t, NULL) == -1)
    std::cerr << "ERROR GETTIMEOFDAY" << std::endl;
  tmp = t.tv_sec + t.tv_usec / pow(10, 6);
  return (tmp);
}
  
void	TimerUnix::initWait(unsigned int sec, unsigned int milli)
{
  double tmp;

  tmp = getTime();
  this->time_to_wait = sec + milli / pow(10, 6);
}

void TimerUnix::resetTime()
{
  this->start_time = getTime();
}
