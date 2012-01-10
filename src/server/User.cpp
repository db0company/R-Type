#include <iostream>
#include <string>
#include "User.hpp"
#include "ATCPClientSocket.h"
#include "AUDPServerSocket.h"
#include "PacketAggregator.hpp"
#include "PacketManager.hpp"

User::User(ATCPClientSocket * socket, std::string const & ip, PacketManager &pamanager)
  : safe(true), log(false), login(""), ip(ip), pm(pamanager), tcp(socket), _player(NULL), _state(USER_ROOMLIST), _game(NULL)
{}

User::User(User const & other)
  : safe(other.safe), log(other.log), login(other.login),
    ip(other.ip), pm(other.pm), tcp(other.tcp), _state(other._state), _game(NULL)
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
      this->paRead = other.paRead;
      this->paWrite = other.paWrite;
      this->paWriteUDP = other.paWriteUDP;
      this->paReadUDP = other.paReadUDP;
      this->_state = other._state;
      this->_player = other._player;
      this->_game = other._game;
    }
  return (*this);
}

User::~User(void)
{}

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

bool				User::isSafe(void)const
{
  return (this->safe);
}

void				User::setSafe(bool state)
{
  this->safe = state;
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

bool				User::feedPacketAggregator(char *data, int size)
{
  this->paReadUDP.concat(data, size);
  return (true);
}

std::string const &User::getLogin(void)const
{
  return (this->login);
}

void		User::setLogin(std::string const &log)
{
  this->login = log;
}

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
	  std::cout << nb << " packet(s) to aggregate (send TCP)" << std::endl;
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


bool			User::addPacketToSendUDP(ProtocolPacket *packer)
{
  this->paWriteUDP.push(packer);
  return (true);
}

bool			User::aggregatePacketToSend(AUDPServerSocket *so)
{
  unsigned int size;
  char	*msg;
  int nb;

  nb = this->paWriteUDP.aggregatePacketToChar();
  if (nb > 0)
    {
      std::cout << nb << " packet(s) to aggregate (send UDP)" << std::endl;
      size = this->paWriteUDP.getSize();
      msg = this->paWriteUDP.getMsg();
      so->SNWrite(msg, size); // read verif udp omg wtf bbq
      this->paWriteUDP.erase();
    }
  return (true);
}

bool				User::processPackets(Server &serv)
{
  ProtocolPacket		*packet = NULL;
  int				tmp_i = 0;

  this->paRead.aggregateCharToPackets();
  this->paReadUDP.aggregateCharToPackets();
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

cState		User::getState(void)const
{
  return (this->_state);
}

void			User::setState(cState s)
{
  this->_state = s;
}

void User::setGame(Game *h)
{
  this->_game = h;
}

Game *User::getGame(void)
{
  return (this->_game);
}
