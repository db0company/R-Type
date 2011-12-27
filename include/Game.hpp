#ifndef GAME_H_
# define GAME_H_

#include <string>
#include "GameParameter.hpp"
#include "User.hpp"

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
};

#endif	// GAME_H_
