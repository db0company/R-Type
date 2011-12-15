
#include		"UserSocket.hpp"

/* ************************************************************************* */
/*                             Coplien Form                                  */
/* ************************************************************************* */

UserSocket::UserSocket(ISocket * socket)
  : haveHeader(false), header(), socket(socket)
{}

UserSocket::UserSocket(UserSocket const & other)
  : haveHeader(other.haveHeader), header(other.header), socket(other.socket)
{}

UserSocket &		UserSocket::operator=(UserSocket const & other)
{
  if (&other != this)
    {
      this->haveHeader = false;
      this->socket = other.socket;

      // If there is a pointer to something allocated, do this :
      // if (this->SomeThingAllocated)
      //   delete this->SomeThingAllocated;
      // this->SomeThingAllocated = CopyFunc(other.SomeThingAllocated);
    }
  return (*this);
}

UserSocket::~UserSocket(void)
{}

/* ************************************************************************* */
/*                             Getters/Setters                               */
/* ************************************************************************* */

bool				UserSocket::getHaveHeader(void) const
{
    return (this->haveHeader);
}

void				UserSocket::setHaveHeader(bool haveHeader)
{
    this->haveHeader = haveHeader;
}

ProtocolPacketHeader &		UserSocket::getHeader(void)
{
    return (this->header);
}

ISocket *			UserSocket::getSocket(void) const
{
    return (this->socket);
}

void				UserSocket::setSocket(ISocket * socket)
{
    this->socket = socket;
}

bool				UserSocket::isConnected(void) const
{
    return (this->socket != NULL);
}
