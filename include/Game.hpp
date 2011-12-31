#ifndef GAME_H_
# define GAME_H_

#include <string>
#include "GameParameter.hpp"
#include "User.hpp"
#include "AObject.hpp"

//todo
class	Game
{
public:
  Game(const GameParameter& param);
  ~Game(void);
  Game(const Game&);
  Game&	operator=(const Game&);
  void	changePlayerPos();
private:
  GameParameter	_param;
  std::map<std::string, AObject *> _players;
  std::map<std::string, AObject *> _monster;
  std::map<std::string, AObject *> _map;
};

#endif	// GAME_H_
