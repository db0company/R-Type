#ifndef GAME_H_
# define GAME_H_

#include <string>
#include <map>
#include "GameParameter.hpp"
#include "User.hpp"
#include "GameNetwork.hpp"

//todo
class	Game
{
public:
  Game(void);
  ~Game(void);
  Game(const Game&);
  Game&	operator=(const Game&);

private:
  GameParameter	_param;
  GameNetwork	_network;
};

#endif	// GAME_H_
