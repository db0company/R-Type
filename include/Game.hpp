#ifndef GAME_H_
# define GAME_H_

#include <string>
#include <list>
#include "GameParameter.hpp"
#include "User.hpp"
#include "AObject.hpp"
#include "Position.hpp"
#include "Bullet.hpp"

//todo
class	Game
{
public:
  Game(const GameParameter& param);
  ~Game(void);
  Game(const Game&);
  Game&	operator=(const Game&);
  void	changePlayerPos(void *);
  void	moveMonster(void *);
  void	createNewPlayer(User *us, const std::string& name);
  void	createNewMonster(void *);
  const std::string getPlayerByIp(const std::string& ip);
  void	checkCollision(void *);
  void	moveBullet(void *);
private:
  GameParameter	_param;
  std::map<std::string, AObject *> _players;
  std::map<std::string, AObject *> _monster;
  std::map<std::string, AObject *> _map;
  std::list<Bullet>		_bullets;
};

#endif	// GAME_H_
