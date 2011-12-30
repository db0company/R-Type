#ifndef		__TASKNETWORK_HPP__
# define	__TASKNETWORK_HPP__

#include <iostream>
#include "AUDPServerSocket.h"
#include "IMutex.hpp"
#include "ProtocolPacket.h"

class		TaskNetwork
{
private:
  AUDPServerSocket *udpSock;
  IMutex	   *udpMutex;
public:
  TaskNetwork(void);
  void init(AUDPServerSocket *udp, IMutex *mutex);
  void setSock(AUDPServerSocket *udp);
  void setMutex(IMutex *mutex);
  ~TaskNetwork(void);
  void sendToClient(void *data);
};

struct sendToClientData
{
  ProtocolPacket *packet;
  std::string     ip;
  int		  port;
};

#endif		/*__TASKNETWORK_HPP__*/
