
#include		<iostream>
#include		<string>
#include		"user/User.hpp"
#include		"ATCPClientSocket.h"

/* ************************************************************************* */
/*                             Coplien Form                                  */
/* ************************************************************************* */

User::User(ATCPClientSocket * socket, std::string const & ip)
  : _safe(true), _log(false), _login(""), _socket(socket), _ip(ip)
{}

User::User(User const & other)
  : safe(other._safe), _log(other._log), _login(other._login),
    _socket(other._socket), _ip(other._ip)
{}

User &			User::operator=(User const & other)
{
  if (&other != this)
    {
      this->_safe = other._safe;
      this->_log = other._log;
      this->_login = other._login;
      this->_socket = other._socket;
      this->_ip = other._ip;

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
/*                             Member Functions                              */
/* ************************************************************************* */

bool				User::isSafe(void)const
{
  return (this->_safe);
}

void				User::setSafe(bool state)
{
  this->_safe = state;
}

bool				User::isLog(void)const
{
  return (this->_log);
}

void				User::setLog(bool st)
{
  this->_log = st;
}

ATCPClientSocket *		User::getSocket(void)
{
  return (this->_socket);
}

std::string const &		User::getIp(void)const
{
  return (this->_ip);
}
