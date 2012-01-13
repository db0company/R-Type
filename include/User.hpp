#ifndef		USERHPP
# define	USERHPP

#include <string>
#include "ATCPClientSocket.h"
#include "AUDPServerSocket.h"
#include "PacketAggregator.hpp"
#include "PacketManager.hpp"
#include "ProtocolPacket.h"
#include "IMutex.hpp"

#define AGGREGATE_READ_SIZE 1024

class		Player;
class		Server;
class		Game;
enum cState
  {
    USER_ROOMLIST,
    USER_GAME_ROOT,
    USER_GAME_PLAYER,
    USER_GAME_SPECTATE
  };

class		User
{
private:
  bool		safe;
  bool		log;
  std::string	login;
  std::string	ip;
  PacketManager &pm;

  ATCPClientSocket *	tcp;

  PacketAggregator	paRead;
  PacketAggregator	paWrite;
  PacketAggregator	paWriteUDP;
  PacketAggregator	paReadUDP;

  Player		*_player;
  cState		_state;
  Game			*_game;
  IMutex		*_mutex;
public:
  User(ATCPClientSocket *, std::string const & ip, PacketManager &);
  User(User const & other);
  User &		operator=(User const & other);
  ~User(void);

public:
  void			setGame(Game *);
  cState		getState(void)const;
  void			setState(cState s);
  bool			isSafe(void)const;
  void			setSafe(bool);
  bool			isLog(void)const;
  void			setLog(bool);
  ATCPClientSocket *	getSocketTCP(void);
  std::string const &	getIp(void)const;
  Game			*getGame(void);
  bool			addPacketToSend(ProtocolPacket *);
  bool			addPacketToSendUDP(ProtocolPacket *);
  //tcp
  bool			feedPacketAggregator(void);
  //udp
  bool			feedPacketAggregator(char *data, int size);
  bool			processPackets(Server &);
  bool			aggregatePacketToSend(void);
  bool			aggregatePacketToSend(AUDPServerSocket*);
  std::string const &	getLogin(void)const;
  void			setLogin(std::string const &);
};

#endif			// USERHPP
