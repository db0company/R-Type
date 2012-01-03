#include "TaskNetwork.hpp"
#include "ScopedLock.hpp"
#ifndef _WIN32
#include <cstring>
#endif

void TaskNetwork::setSock(AUDPServerSocket *udp)
{
  this->udpSock = udp;
}

void TaskNetwork::setMutex(IMutex *mutex)
{
  this->udpMutex = mutex;
}

void TaskNetwork::init(AUDPServerSocket *udp, IMutex *mutex)
{
  this->udpSock = udp;
  this->udpMutex = mutex;
}

TaskNetwork::TaskNetwork() : udpSock(NULL), udpMutex(NULL)
{
}

TaskNetwork::~TaskNetwork()
{
}

TaskNetwork::TaskNetwork(const TaskNetwork& old)
  : udpSock(old.udpSock), udpMutex(old.udpMutex)
{

}

TaskNetwork&	TaskNetwork::operator=(const TaskNetwork& old)
{
  this->udpSock = old.udpSock;
  this->udpMutex = old.udpMutex;
  return (*this);
}

void	TaskNetwork::sendToClient(void *data)
{
  sendToClientData	*dataSend = NULL;
  ScopedLock		sc(this->udpMutex);
  char			*msg_to_send;
  int			size = 0;

  dataSend = reinterpret_cast<sendToClientData *>(data);
  if (dataSend->packet)
    {
      size = dataSend->packet->header.size +
	sizeof(dataSend->packet->header);
      msg_to_send = new char[size];
      memset(msg_to_send, 0, size);
      memcpy(msg_to_send, &(dataSend->packet->header),
	     sizeof(dataSend->packet->header));
      memcpy(msg_to_send + sizeof(dataSend->packet->header),
	     &(dataSend->packet->data),
	     dataSend->packet->header.size);
      if (this->udpSock)
	this->udpSock->SNWriteToClient(msg_to_send, size, dataSend->ip);
    }
}
