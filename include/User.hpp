#ifndef		USERHPP
# define	USERHPP

# include	<string>
# include	"ATCPClientSocket.h"
# include	"AUDPServerSocket.h"
# include	"PacketAggregator.hpp"
# include	"PacketManager.hpp"
# include	"ProtocolPacket.h"

#define AGGREGATE_READ_SIZE 1024

class		Server;
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

 public:
  User(ATCPClientSocket *, std::string const & ip, PacketManager &);
  User(User const & other);
  User &		operator=(User const & other);
  ~User(void);

 public:
  bool			isSafe(void)const;
  void			setSafe(bool);
  bool			isLog(void)const;
  void			setLog(bool);
  ATCPClientSocket *	getSocketTCP(void);
  std::string const &	getIp(void)const;
  bool			addPacketToSend(ProtocolPacket *);
bool			addPacketToSendUDP(ProtocolPacket *);
 //tcp
  bool			feedPacketAggregator(void);
  //udp
  bool			feedPacketAggregator(char *data, int size);
  bool			processPackets(Server &);
  bool			aggregatePacketToSend(void);
  bool			aggregatePacketToSend(AUDPServerSocket*);
};

#endif			// USERHPP
