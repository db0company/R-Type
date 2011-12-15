#ifndef GAMEPARAMETER_H_
# define GAMEPARAMETER_H_

#include <string>

struct	GameParameter
{
  std::string	name;
  std::string	root_login;
  int		nb_player_max;
  int		difficulty;
  bool		observer;
  int		nb_observer_max;
  int		lvl;
};

#endif	// GAMEPARAMETER_H_
