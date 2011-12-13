#include <iostream>
#include <string>
#include "User.hpp"
#include "ATCPClientSocket.h"

User::User(void){}

User::User(ATCPClientSocket *socket, std::string const &ip) :
  _safe(true), _log(false), _login(""), _socket(socket), _ip(ip)
{
}

User::~User(void)
{
}

User& User::operator=(User const &)
{
  //todo
  return (*this);
}

User::User(User const &)
{
  //todo
}

bool			User::isSafe(void)const
{
  return (this->_safe);
}

void			User::setSafe(bool state)
{
  this->_safe = state;
}

bool			User::isLog(void)const
{
  return (this->_log);
}

void			User::setLog(bool st)
{
  this->_log = st;
}

ATCPClientSocket	*User::getSocket(void)
{
  return (this->_socket);
}

std::string const	&User::getIp(void)const
{
  return (this->_ip);
}
