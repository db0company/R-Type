/*
** timer.c for  in /home/munoz_v//svn/zappy
** 
** Made by vincent munoz
** Login   <munoz_v@epitech.net>
** 
** Started on  Wed Jun 22 15:17:28 2011 vincent munoz
** Last update Sun Jul 10 14:40:06 2011 vincent munoz
*/

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
