#include "Server.hpp"
#include "Selector.hpp"
#include "protocol/PacketManager.hpp"
#ifndef _WIN32
# include "TCPServerSocketUnix.h"
#else
# include "TCPServerSocketWindows.h"
#endif

PacketManager * pm = NULL;

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

bool	Server::addClient(ATCPClientSocket *sock)
{
  User	*user;

  if (sock->getIp())
    {
      std::cout << "Info: User "<< sock->getIp() << " added to list"  << std::endl;
      user = new User(sock, sock->getIp());
      this->_userList.push_front(user);
      return (true);
    }
  std::cerr << "Error: Can't resolve client ip adress" << std::endl;
  return (false);
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
	{
	  std::cout << " from " << newClient->getIp();
	}
      std::cout << std::endl;
      this->addClient(newClient);
    }
  return (true);
}

bool Server::removeClient(User *user, ATCPClientSocket *socket)
{
  if (socket && user)
    {
      std::cout << "Info: User " <<
	socket->getIp() << " disconnected" <<
	std::endl;
      user->setSafe(false);
      socket->SNDelRead();
      socket->SNDelWrite();
      return (true);
    }
  return (false);
}

//todo :removelist safely-o !
bool Server::readFromClient(void)
{
  std::list<User *>::iterator	it;
  User				*user = NULL;
  ATCPClientSocket		*socket = NULL;

  for (it = this->_userList.begin(); it != this->_userList.end(); ++it)
    {
      user = *it;
      if (user && user->isSafe() && (socket = user->getSocketTCP()))
	{
	  if (socket->SNGetRead() == true)
	    {
	      char		buff[512] = {0};
	      if (socket->SNRead(buff, 514) <= 0)
		this->removeClient(user, socket); // not from list !
	      else
		std::cout << socket->getIp() << ": " << buff;
	    }
	}
    }
  return (true);
}

bool Server::run(void)
{
  PacketManager pmp;
  // todo: maybe some arguments needed by packetmanager, like gamemanager
  pm = &pmp;
  while (true)
    {
      this->_listener->SNAddRead();
      if (!this->_selector->SNSelect())
	{
	  std::cerr << "Error: Select" << std::endl;
	  return (false);
	}
      this->getNewClient();
      this->readFromClient();
    }
}
