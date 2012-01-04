
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <time.h>
#include <math.h>
#include <sys/time.h>
#include "server.h"

double		reset_time()
{
  struct timeval	t;
  double	time;

  if (gettimeofday(&t, NULL) == -1)
    return (-1);
  time = t.tv_sec + t.tv_usec / pow(10, 6);
  return (time);
}

double		elapsed_time(double time)
{
  struct timeval	t;
  double		tmp;

  if (gettimeofday(&t, NULL) == -1)
    return (-1);
  tmp = t.tv_sec + t.tv_usec / pow(10, 6);
  return (tmp - time);
}

int		is_time_out(double time, double wait)
{
  if (time == 0 || wait == 0)
    return (TRUE);
  if (wait <= elapsed_time(time))
    return (TRUE);
  return (FALSE);
}
