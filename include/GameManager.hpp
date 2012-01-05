#ifndef _GAMEMANAGER_HPP_
#define _GAMEMANAGER_HPP_

#include <map>
#include <string>
#include "GameParameter.hpp"
#include "Game.hpp"
#include "User.hpp"

class GameManager
{
private:
  GameManager(GameManager const &);
  GameManager& operator=(GameManager const &);
public:
  GameManager(void);
  ~GameManager(void);
  bool createGame(GameParameter const &param);
  bool addPlayerToGame(User *user, unsigned int game_id, std::string const &,
		       bool root = true, bool observer = false);
  bool delPlayerFromGame(User *user);
  Game *getGameFromId(unsigned int id);
private:
  std::map<int, Game *>		_gameMap;
};

#endif //_GAMEMANAGER_HPP_
