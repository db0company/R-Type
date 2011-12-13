#include "Server.hpp"
#include "Selector.hpp"
#ifndef _WIN32
# include "TCPServerSocketUnix.h"
#else
# include "TCPServerSocketWindows.h"
#endif

Server&	Server::operator=(Server const &){return *this;}
Server::Server(Server const &){}


Server::Server(void)
{
#ifndef _WIN32
  this->_selector = new Selector<int>;
  this->_listener = new TCPServerSocketUnix(this->_selector);
#else
  this->_selector = new Selector<SOCKET>;
  this->_listener = new TCPServerSocketWindows(this->_selector);
#endif
}

Server::~Server(void)
{
}

bool Server::init(int port)
{
  this->_port = port;
  if (!(this->_listener->SNCreate(SERV_ADDR, port)))
    {
      std::cerr << "Error: Can't Create Listener Socket on port " << this->_port << std::endl;
      return (false);
    }
  std::cout << "Server Listening on port " << this->_port << std::endl;
  if (!this->_listener->SNListen())
    {
      std::cerr << "Error: Can't listen on socket" << std::endl;
    }
  this->_listener->SNAddRead();
  return (true);
}

bool Server::getNewClient(void)
{
  if (this->_listener->SNGetRead())
    {
      ATCPClientSocket *newClient = NULL;
      if ((newClient = this->_listener->SNAccept()) == false)
  	  return (false);
      newClient->SNAddRead();
      newClient->SNAddWrite();
      std::cout << "New connection";
      if (newClient->getIp())
  	std::cout << " from " << newClient->getIp();
      std::cout << std::endl;
    }
  return (true);
}

bool Server::run(void)
{
  while (true)
    {
      this->_listener->SNAddRead();
      if (!this->_selector->SNSelect())
	{
	  std::cerr << "Error: Select" << std::endl;
	  return (false);
	}
      this->getNewClient();
    }
}

