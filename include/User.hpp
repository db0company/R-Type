#ifndef			USERHPP
# define		USERHPP

# include		"ATCPClientSocket.h"
# include		"PacketAggregator.hpp"
# include		<string>

#define AGGREGATE_READ_SIZE 1024

class			User
{
 private:
  bool			safe;
  bool			log;
  std::string		login;
  std::string		ip;

 public:
  ATCPClientSocket *	tcp;
  PacketAggregator	paRead;
  PacketAggregator	paWrite;
 public:
  User(ATCPClientSocket *, std::string const & ip);
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
  bool			feedPacketAggregator(void);
  bool			processPackets(void);
  bool			aggregatePacketToSend(void);
};

#endif			// USERHPP
