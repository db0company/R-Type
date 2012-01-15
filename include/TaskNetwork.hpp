#ifndef		__TASKNETWORK_HPP__
# define	__TASKNETWORK_HPP__

#include <iostream>
#include "AUDPServerSocket.h"
#include "IMutex.hpp"
#include "ProtocolPacket.h"


struct sendToClientData
{
  ProtocolPacket *packet;
  std::string     ip;
  int		  port;
};

class		TaskNetwork
{
private:
  AUDPServerSocket *udpSock;
  IMutex	   *udpMutex;
public:
  TaskNetwork(void);
  TaskNetwork(const TaskNetwork& old);
  TaskNetwork&	operator=(const TaskNetwork& old);
  void init(AUDPServerSocket *udp, IMutex *mutex);
  void setSock(AUDPServerSocket *udp);
  void setMutex(IMutex *mutex);
  ~TaskNetwork(void);
  void sendToClient(sendToClientData const &data);
};

#endif		/*__TASKNETWORK_HPP__*/
