#include <iostream>
#include <string>
#include "User.hpp"
#include "ATCPClientSocket.h"
#include "AUDPServerSocket.h"
#include "PacketAggregator.hpp"
#include "PacketManager.hpp"

User::User(ATCPClientSocket * socket, std::string const & ip, PacketManager &pamanager)
  : safe(true), log(false), login(""), ip(ip), pm(pamanager), tcp(socket)
{}

User::User(User const & other)
  : safe(other.safe), log(other.log), login(other.login),
    ip(other.ip), pm(other.pm), tcp(other.tcp)
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
  char	*msg;
  int nb;

  if (this->tcp->SNGetWrite())
    {
      nb = this->paWrite.aggregatePacketToChar();
      if (nb > 0)
	{
	  std::cout << nb << " packet(s) to aggregate (TCP)" << std::endl;
	  size = this->paWrite.getSize();
	  msg = this->paWrite.getMsg();
	  this->tcp->SNWrite(msg, size); // verif todo
	  this->paWrite.erase();
	}
      return (true);
    }
  return (false);
}

bool			User::addPacketToSend(ProtocolPacket *packer)
{
  this->paWrite.push(packer);
  return (true);
}

//udp
// bool			User::aggregatePacketToSend(AUDPServerSocket *so)
// {
//   unsigned int size;
//   unsigned char	*msg;
//   int nb;

//   if (so->SNGetWrite())
//     {
//       nb = this->paWriteUDP.aggregatePacketToChar();
//       if (nb > 0)
// 	{
// 	  size = this->paWriteUDP.getSize();
// 	  msg = this->paWriteUDP.getMsg();
// 	  so->SNWrite(msg, size);
// 	  this->paWriteUDP.erase();
// 	}
//     }
//   return (true);
// }

bool				User::processPackets(Server &serv)
{
  int				nb_packet = 0;
  ProtocolPacket		*packet = NULL;
  int				tmp_i = 0;

  nb_packet = this->paRead.aggregateCharToPackets();
  // if (nb_packet > 0)
  //   std::cout << "TCP PacketQueue.size() == " << nb_packet << std::endl;
  nb_packet = this->paReadUDP.aggregateCharToPackets();
  // if (nb_packet > 0)
  //   std::cout << "UDP PacketQueue.size() == " << nb_packet << std::endl;
  if (this->paRead.empty() && this->paReadUDP.empty())
    {
      return (false);
    }
  while (!this->paRead.empty())
    {
      std::cout << "\t\033[33mTCP\033[00m \033[34mPacket\033[00m["<<tmp_i<<"] ";
      packet = this->paRead.front();
      this->pm.Process(packet, this, serv);
      this->paRead.pop();
      ++tmp_i;
    }
  tmp_i = 0;
  while (!this->paReadUDP.empty())
    {
      std::cout << "\t\033[33mUDP\033[00m \033[34mPacket\033[00m["<<tmp_i<<"] ";
      packet = this->paReadUDP.front();
      this->pm.Process(packet, this, serv);
      this->paReadUDP.pop();
      ++tmp_i;
    }
  return (true);
}
