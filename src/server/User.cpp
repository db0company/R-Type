#include <iostream>
#include <string>
#include "User.hpp"
#include "ATCPClientSocket.h"
#include "AUDPServerSocket.h"
#include "PacketAggregator.hpp"
#include "PacketManager.hpp"

User::User(ATCPClientSocket * socket, std::string const & ip, PacketManager &pamanager)
  : safe(true), log(false), login(""), ip(ip), tcp(socket), pm(pamanager)
{}

User::User(User const & other)
  : safe(other.safe), log(other.log), login(other.login),
    ip(other.ip), tcp(other.tcp), pm(other.pm)
{}

User &			User::operator=(User const & other)
{
  if (&other != this)
    {
      this->safe = other.safe;
      this->log = other.log;
      this->login = other.login;
      this->ip = other.ip;
      this->tcp = other.tcp;
    }
  return (*this);
}

User::~User(void)
{}

bool				User::isSafe(void)const
{
  return (this->safe);
}

void				User::setSafe(bool state)
{
  this->safe = state;
}

bool				User::isLog(void)const
{
  return (this->log);
}

void				User::setLog(bool st)
{
  this->log = st;
}

ATCPClientSocket *		User::getSocketTCP(void)
{
  return (this->tcp);
}

std::string const &		User::getIp(void)const
{
  return (this->ip);
}

//tcp
bool				User::feedPacketAggregator(void)
{
  char buffer[1024] = {0};
  int  size;

  if ((size = this->tcp->SNRead(buffer, 1024)) <= 0)
    {
      return (false);
    }
  this->paRead.concat(buffer, size);
  return (true);
}

//udp
bool				User::feedPacketAggregator(char *data, int size)
{
  this->paReadUDP.concat(data, size);
  return (true);
}

// tcp
bool			User::aggregatePacketToSend(void)
{
  unsigned int size;
  unsigned char	*msg;
  int nb;

  if (this->tcp->SNGetWrite())
    {
      nb = this->paWrite.aggregatePacketToChar();
      if (nb > 0)
	{
	  size = this->paWrite.getSize();
	  msg = this->paWrite.getMsg();
	  this->tcp->SNWrite(msg, size);
	  this->paWrite.erase();
	}
    }
  return (true);
}

//udp
bool			User::aggregatePacketToSend(AUDPServerSocket *so)
{
  unsigned int size;
  unsigned char	*msg;
  int nb;

  if (so->SNGetWrite())
    {
      nb = this->paWriteUDP.aggregatePacketToChar();
      if (nb > 0)
	{
	  size = this->paWriteUDP.getSize();
	  msg = this->paWriteUDP.getMsg();
	  so->SNWrite(msg, size);
	  this->paWriteUDP.erase();
	}
    }
  return (true);
}

bool				User::processPackets(void)
{
  int				nb_packet;
  ProtocolPacket		*packet;

  nb_packet = this->paRead.aggregateCharToPackets();
  if (nb_packet > 0)
    std::cout << "packet ds la queue read:" << nb_packet << std::endl;
  if (this->paRead.empty() && this->paReadUDP.empty())
    {
      return (false);
    }
  while (!this->paRead.empty())
    {
      packet = this->paRead.front();
      this->pm.Process(packet, NULL);//null because param ignored 4 the moment
      this->paRead.pop();
    }
  while (!this->paReadUDP.empty())
    {
      packet = this->paReadUDP.front();
      this->pm.Process(packet, NULL);
      this->paReadUDP.pop();
    }
  return (true);
}
