
#include		<iostream>
#include		<string>
#include		"user/User.hpp"
#include		"ATCPClientSocket.h"

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
  return (dynamic_cast<ATCPClientSocket *>(this->tcp.getSocket()));
}

std::string const &		User::getIp(void)const
{
  return (this->ip);
}

/* ************************************************************************* */
/*                             Member Functions                              */
/* ************************************************************************* */
