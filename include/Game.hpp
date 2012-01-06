#ifndef GAME_H_
# define GAME_H_

#include <string>
#include <list>
#include <map>
#include "GameParameter.hpp"
#include "User.hpp"
#include "PacketData.hpp"
#include "AObject.hpp"
#include "Position.hpp"
#include "Bullet.hpp"

enum eGameStatus
  {
    INGAME,
    LOBBYROOM
  };

class	Game
{
public:
  Game(void);
  ~Game(void);
  Game(const Game&);
  Game&	operator=(const Game&);

  void	changePlayerPos(PacketData *info);
  void	moveMonster(PacketData *);
  void	createNewPlayer(User *us, const std::string& name);
  void	createNewMonster(void *);
  const std::string& getPlayerByIp(const std::string& ip);
  void	checkCollision(void *);
  void	moveBullet(void *);
  void	moveWall(void *);
  void	createWall();
  void	fireBullet(void *);
  void	sendToAllClient(PacketData *data);
  void	sendToIp(PacketData *data, const std::string& ip);
  // getter // setter
  unsigned int	getId(void) const;
  std::string	&getOwnerLogin(void);
  void		setOwnerId(std::string const &);
  std::string	&getName(void);
  void		setName(std::string const &);
  std::string	&getLvlName(void);
  void		setLvlName(std::string const &);
  bool		addUser(User *user, bool root, bool observer, std::string const &);
  unsigned int	getPlayerMax(void)const;
  void		setPlayerMax(unsigned int);
  bool		getObs(void)const;
  void		setObs(bool);
  unsigned int	getNbPlayer(void)const;
  eGameStatus	getStatus(void)const;
  void		setStatus(eGameStatus e);

private:
  unsigned int _id;
  GameParameter        _param;
  std::map<std::string, AObject *> _players;
  std::map<std::string, AObject *> _monster;
  std::list<std::list<AObject *> > _map;
  std::list<Bullet>	_bullets;
  static unsigned int _sid;
  std::map<std::string , User *> _userMap;
  std::map<std::string, User *> _userObsMap;
  std::string _owner_login;
  std::string _name;
  std::string _lvlname;
  unsigned int player_max;
  bool _observer;
  eGameStatus _status;
};

#endif	// GAME_H_
