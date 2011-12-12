#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <string.h>
#include <iostream>
#include <string>
#include "ISocket.h"
#include "ISelector.h"
#include "Selector.hpp"
#include "UDPServerSocketUnix.h"

UDPServerSocketUnix::UDPServerSocketUnix(void)
{
}

UDPServerSocketUnix::UDPServerSocketUnix(ISelector *s) :
  _socket(-1), _selector(s), _host("127.0.0.1"), _port(12345), _error(NOERRORSOCKET), _canread(false), _canwrite(false)
{
  memset(&(this->_daddr), 0, sizeof(this->_daddr));
}

UDPServerSocketUnix::~UDPServerSocketUnix(void)
{
}

UDPServerSocketUnix::UDPServerSocketUnix(const UDPServerSocketUnix &other)
{
  this->_socket = other._socket;
  this->_selector = other._selector;
  this->_host = other._host;
  this->_port = other._port;
  this->_error = other._error;
  this->_canread = other._canread;
  this->_canwrite = other._canwrite;
}

UDPServerSocketUnix& UDPServerSocketUnix::operator=(UDPServerSocketUnix const &other)
{
  this->_socket = other._socket;
  this->_selector = other._selector;
  this->_host = other._host;
  this->_port = other._port;
  this->_error = other._error;
  this->_canread = other._canread;
  this->_canwrite = other._canwrite;
  return (*this);
}

bool		UDPServerSocketUnix::SNCreate(std::string const &host, int port)
{
  struct sockaddr_in server;

  this->_host = host;
  this->_port = port;
  memset(&server, 0, sizeof(struct sockaddr_in));
  if ((this->_socket = socket(AF_INET, SOCK_DGRAM, 0)) == -1)
    {
      this->_error = SOCKETCREAT;
      return (false);
    }
  server.sin_family = AF_INET;
  server.sin_addr.s_addr = INADDR_ANY;
  server.sin_port = htons(this->_port);
  if (bind(this->_socket, (struct sockaddr *)&server, sizeof(server)) == -1)
    {
      this->_error = ALREADYBIND;
      return (false);
    }
  this->_error = NOERRORSOCKET;
  listen(this->_socket, 42); // todo: comm?
  return (true);
}

int		UDPServerSocketUnix::SNRead(void *msg, uint32_t size)
{
  int		ret;
  socklen_t	addrsize;

  addrsize = sizeof(this->_daddr);
  if ((ret = recvfrom(this->_socket, msg, size, 0, (sockaddr *)&(this->_daddr), &addrsize)) <= 0)
    {
      if (ret == 0)
	this->_error = CONNECTIONLOST;
      else
	this->_error = CANTREAD;
      return (ret);
    }
  this->_error = NOERRORSOCKET;
  return (ret);
}

int		UDPServerSocketUnix::SNWrite(const void *msg, uint32_t size)
{
  int		ret;
  socklen_t	socklen;

  socklen = sizeof(this->_daddr);
  if ((ret = sendto(this->_socket, msg, size, 0, (sockaddr *)&(this->_daddr), socklen)) <= 0)
    {
      this->_error = CANTWRITE;
      return (ret);
    }
  this->_error = NOERRORSOCKET;
  return (ret);
}

bool		UDPServerSocketUnix::SNClose(void)
{
  if (close(this->_socket) == -1)
    return (false);
  return (true);
}

std::string	UDPServerSocketUnix::getHost(void) const
{
  return (this->_host);
}

int		UDPServerSocketUnix::getPort(void) const
{
  return (this->_port);
}

eSocketErr	UDPServerSocketUnix::SNGetLastErr(void) const
{
  return (this->_error);
}

bool		UDPServerSocketUnix::SNAddRead(void)
{
  if (this->_selector)
    {
      static_cast <Selector<int> *>(this->_selector)->SNAddRead(this->_socket, this);
      return (true);
    }
  return (false);
}

bool		UDPServerSocketUnix::SNAddWrite(void)
{
  if (this->_selector)
    {
      static_cast <Selector<int> *>(this->_selector)->SNAddWrite(this->_socket, this);
      return (true);
    }
  return (false);
}

bool		UDPServerSocketUnix::SNDelRead(void)
{
  if (this->_selector)
    {
      static_cast <Selector<int> *>(this->_selector)->SNDelRead(this->_socket, this);
      return (true);
    }
  return (false);
}

bool		UDPServerSocketUnix::SNDelWrite(void)
{
  if (this->_selector)
    {
      static_cast <Selector<int> *>(this->_selector)->SNDelWrite(this->_socket, this);
      return (true);
    }
  return (false);
}

void		UDPServerSocketUnix::SNSetRead(bool state)
{
  this->_canread = state;
}

void		UDPServerSocketUnix::SNSetWrite(bool state)
{
  this->_canwrite = state;
}

bool		UDPServerSocketUnix::SNGetRead(void) const
{
  return (this->_canread);
}

bool		UDPServerSocketUnix::SNGetWrite(void) const
{
  return (this->_canwrite);
}

char*		UDPServerSocketUnix::getIp(void) const
{
  return (NULL);
}
