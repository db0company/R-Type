#ifndef _GAMEMANAGER_HPP_
#define _GAMEMANAGER_HPP_

#include <map>
#include <string>
#include "GameParameter.hpp"
#include "Game.hpp"
#include "Room.hpp"
#include "User.hpp"

class GameManager
{
private:
  GameManager(GameManager const &);
  GameManager& operator=(GameManager const &);
public:
  GameManager(void);
  ~GameManager(void);
  bool createRoom(GameParameter const &param);
  bool createGame(GameParameter const &param);
private:
  std::map<std::string, User *> _userMap;
  std::map<int, Room *>		_roomMap;
  std::map<int, Game *>		_gameMap;
};

#endif //_GAMEMANAGER_HPP_
