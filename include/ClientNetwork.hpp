#ifndef  CLIENTNETWORK_H_
# define CLIENTNETWORK_H_

#include <iostream>
#include <string>
#include "PacketAggregator.hpp"
#include "ATCPClientSocket.h"
#include "ISelector.h"
#include "ISocket.h"

class		ClientNetwork
{
public:
  ClientNetwork(void);
  ClientNetwork(std::string const &ip, int port);
  ~ClientNetwork(void);
  ClientNetwork(const ClientNetwork&);
  ClientNetwork&	operator=(const ClientNetwork&);
  void init(std::string const &ip, int port);
  bool connect(std::string const &ip, int port);
  bool connect(void);
  bool select(void);
  bool feedPacketAggregator(void);
  bool process(void);
  bool sendPackettoServer(void);
private:

  ATCPClientSocket *_tcp;
  ISocket	   *_udp;
  ISelector	   *_selector;
  PacketAggregator	paRead;
  PacketAggregator	paWrite;
  std::string		_ip;
  int			_port;
};

#endif	// CLIENTNETWORK_H_
