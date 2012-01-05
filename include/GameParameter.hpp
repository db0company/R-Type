#ifndef GAMEPARAMETER_H_
# define GAMEPARAMETER_H_

#include <string>
//todo
struct	GameParameter
{
  short		id;
  std::string	owner;
  std::string	name;
  std::string	root_login;
  char		slot;
  std::string	lvl;
  bool		observer;
  int		sizeCol;
  int		sizeLine;
  int		nb_player; // clientside
};

#endif	// GAMEPARAMETER_H_
