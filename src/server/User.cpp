
#include		<iostream>
#include		<string>
#include		"User.hpp"
#include		"ATCPClientSocket.h"
#include		"PacketAggregator.hpp"

/* ************************************************************************* */
/*                             Coplien Form                                  */
/* ************************************************************************* */

User::User(ATCPClientSocket * socket, std::string const & ip)
  : safe(true), log(false), login(""), ip(ip), tcp(socket)
{}

User::User(User const & other)
  : safe(other.safe), log(other.log), login(other.login),
    ip(other.ip), tcp(other.tcp)
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

      // If there is a pointer to something allocated, do this :
      // if (this->SomeThingAllocated)
      //   delete this->SomeThingAllocated;
      // this->SomeThingAllocated = CopyFunc(other.SomeThingAllocated);
    }
  return (*this);
}

User::~User(void)
{}

/* ************************************************************************* */
/*                             Getters/Setters                               */
/* ************************************************************************* */

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
  return (false);
}


bool				User::processPackets(void)
{
  int				nb_packet;
  ProtocolPacket		*packet;

  nb_packet = this->paRead.aggregateCharToPackets();
  if (this->paRead.empty())
    return (false);
  while (!this->paRead.empty())
    {
      packet = this->paRead.front();
      // ici on a le packet a executer!
      // serai parfait : packetManager->Process(packet, this);
      this->paRead.pop();
    }
  return (true);
}
