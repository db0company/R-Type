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
#include "Player.hpp"
#include "RecupMap.hpp"
#include "IMutex.hpp"
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

  void	changePlayerPos(PacketData &info);
  void	moveMonster(PacketData &);
  void	createNewPlayer(User *us, const std::string& name);
  void	createNewMonster(PacketData &);
  const std::string& getPlayerByIp(const std::string& ip);
  void	checkCollision(PacketData &);
  void	moveBullet(PacketData &);
  void	moveWall(PacketData &);
  void	createWall();
  void	fireBullet(PacketData &);
  void	sendToAllClient(PacketData *data, eProtocolPacketGroup g, ushort fonc);
  void	sendToIp(PacketData *data, eProtocolPacketGroup g, ushort fonc, Player *player);
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
  IMutex	*getMutex();
  std::map<std::string, AObject *>& getPlayerList();
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
  RecupMap	_rMap;
  IMutex	*_mutex;
};

#endif	// GAME_H_
