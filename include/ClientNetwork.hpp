#ifndef  CLIENTNETWORK_H_
# define CLIENTNETWORK_H_

#include <iostream>
#include <string>
#include "PacketAggregator.hpp"

class		ClientNetwork
{
public:
  ClientNetwork(void);
  ~ClientNetwork(void);
  ClientNetwork(const ClientNetwork&);
  ClientNetwork&	operator=(const ClientNetwork&);
  bool connect(std::string const &ip, int port);
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
};

#endif	// CLIENTNETWORK_H_
