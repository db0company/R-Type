#include <time.h>
#include <string>
#include <iostream>
#include <sstream>
#include <cstdlib>
#include <fstream>
#include "../include/TileInfo.hpp"

int		lengthNb(int nb)
{
  if (nb < 10)
    return (1);
  else if (nb < 100)
    return (2);
  return (3);
}

void		gen_map(int nb)
{
  std::fstream	os;
  int		i = 0;
  int		r;
  int		r2;
  int		flag = 0;
  int		flag2 = 0;

  srand(time(NULL));
  os.open("newMap.txt", std::fstream::out | std::fstream::trunc);
  while (i != nb && os.good() == true)
    {
      std::ostringstream oss;

      if (flag == 0)
	r = rand() % TileEmpty;
      else if (flag == 1)
	r += 1;
      if ((r == 6 || r == 8 || r == 11 || r == 12) && flag == 0)
	continue;
      if (r == 5 || r == 7 || r == 10 || r == 11)
	flag = 1;
      else
	flag = 0;
      oss << r;
      os.write(oss.str().c_str(), lengthNb(r));
      os.write(";", 1);
      oss << r;
      os.write(oss.str().c_str(), lengthNb(r));
      ++i;
      if (i != nb)
	os.write("|", 1);
    }
}

int		main(int ac, char **av)
{
  if (ac != 2)
    gen_map(80);
  else
    gen_map(atoi(av[1]));
}
