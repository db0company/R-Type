#include "Server.hpp"
#include "Selector.hpp"
#include "PacketManager.hpp"
#include "eProtocolPacketGame.hpp"
#ifndef _WIN32
# include "TCPServerSocketUnix.h"
# include "UDPServerSocketUnix.h"
# include "MutexUnix.hpp"
# include "CondVarUnix.hpp"
# include "TimerUnix.hpp"
#else
# include "TCPServerSocketWindows.h"
# include "UDPServerSocketWindows.h"
# include "CondVarWindows.hpp"
# include "TimerWindows.hpp"
#endif

Server::Server(void) :
  _taskNet(), _taskManager(_taskNet), _threadPool(POOL_NBTHREAD)
{
#ifndef _WIN32
  this->_udpMutex = new MutexUnix;
  this->_selector = new Selector<int>;
  this->_udp = new UDPServerSocketUnix(this->_selector);
  this->_listener = new TCPServerSocketUnix(this->_selector);
  this->_condVar = new CondVarUnix;
  this->_time = new TimerUnix;
#else
  this->_udpMutex = new MutexWindows;
  this->_selector = new Selector<SOCKET>;
  this->_udp = new UDPServerSocketWindows(this->_selector);
  this->_listener = new TCPServerSocketWindows(this->_selector);
  this->_condVar = new CondVarWindows;
  this->_time = new TimerWindows;
#endif
  this->_taskNet.init(this->_udp, this->_udpMutex);
  IThreadData *threadData = new ThreadData<PacketTask *>(this->_taskQueue, this->_condVar);
  this->_threadPool.init(threadData); // thread data todo
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
  if (!(this->_udp->SNCreate(SERV_ADDR, port)))
    {
      std::cerr << "Error: Can't Create Udp Socket on port " << this->_port << std::endl;
      return (false);
    }
  std::cout << "Server Listening on port " << this->_port << std::endl;
 if (!this->_listener->SNListen())
    {
      std::cerr << "Error: Can't listen on socket" << std::endl;
    }
  this->_listener->SNAddRead();
  this->_udp->SNAddRead();
  //debug test//
  // Game *g = new Game;
  // // Game *f = new Game;
  // // g->setName("toto");
  // // f->setOwnerId("prout");
  // // g->setObs(false);
  // // this->_gameManager.addGame(g);
  // // f->setName("nom");
  // // f->setOwnerId("didi");
  // // f->setObs(true);
  // this->_gameManager.addGame(f);
  return (true);
}

bool	Server::addClient(ATCPClientSocket *sock)
{
  User	*user;

  if (sock->getIp())
    {
      user = new User(sock, sock->getIp(), this->_pm);
      if (this->_userMap.find(sock->getIp()) == this->_userMap.end())
	{
	  std::cout << "Info: User "<< sock->getIp() << " added to list"  << std::endl;
	  this->_userMap[sock->getIp()] = user;
	  return (true);
	}
      std::cout << "User " << sock->getIp() << " is already connected" << std::endl;
      sock->SNClose();
      delete user;
      return (false);
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
  PacketData	*to_send = new PacketData;
  ProtocolPacket *packet_to_send;
  Game *game;
  std::map<std::string, User *>maap;
  std::map<std::string, User *>::iterator it;

  if (socket && user)
    {
      std::cout << "Info: User " <<
	socket->getIp() << " disconnected" <<
	std::endl;
      user->setSafe(false);
      if (socket->getIp())
	{
	  if ((game = user->getGame()) != NULL)
	    {
	      maap = game->getUserMap();
	      to_send->addShort(0);
	      to_send->addString(user->getLogin());
	      for (it = maap.begin(); it != maap.end(); ++it)
		{
		  packet_to_send = PacketFactory::createPacket(THE_GAME,
		      static_cast<ushort>(QUITGAME), to_send);
		  it->second->addPacketToSend(packet_to_send);
		}
	      game->setStatus(ENDED);
	    }
	  this->_quitQueue.push(socket->getIp());
	}
      socket->SNDelRead();
      socket->SNDelWrite();
      socket->SNClose();
      return (true);
    }
  return (false);
}

bool Server::readFromClients(void)
{
  std::map<std::string, User *>::iterator	it;
  User				*user = NULL;
  ATCPClientSocket		*socket = NULL;

  for (it = this->_userMap.begin(); it != this->_userMap.end(); ++it)
    {
      user = it->second;
      if (user && user->isSafe() && (socket = user->getSocketTCP()) != NULL)
	{
	  if (socket->SNGetRead() == true)
	    {
	      if (user->feedPacketAggregator() == false)
		{
		  this->removeClient(user, socket);
		}
	    }
	}
    }
  if (this->_udp->SNGetRead())
    {
      int size;
      char msg[1024];
      std::string ip;

      if ((size = this->_udp->SNReadClient(msg, 1024, ip))) //todo check size
  	{
  	  if (this->_userMap.find(ip) != this->_userMap.end())
  	    {
	      this->_userMap[ip]->feedPacketAggregator(msg, size);
  	    }
  	}
    }
  return (true);
}

bool	Server::cleanClients(void)
{
  std::string ip;

  if (this->_quitQueue.empty())
    return (true);
  while (!this->_quitQueue.empty())
    {
      ip = this->_quitQueue.front();
      if (this->_userMap.find(ip) != this->_userMap.end())
	{
	  delete this->_userMap[this->_quitQueue.front()];
	  this->_userMap.erase(ip);
	}
      this->_quitQueue.pop();
    }
  return (true);
}

bool	Server::writeToClients(void)
{
  std::map<std::string, User *>::iterator	it;
  User *user = NULL;

  for (it = this->_userMap.begin(); it != this->_userMap.end(); ++it)
    {
      if ((user = it->second) == NULL)
	continue;
      user->aggregatePacketToSend();
      user->aggregatePacketToSend(this->_udp);
    }
  return (true);
}

bool	Server::processPackets(void)
{
  std::map<std::string, User *>::iterator	it;
  User *user = NULL;

  for (it = this->_userMap.begin(); it != this->_userMap.end(); ++it)
    {
      if ((user = it->second) == NULL)
	continue;
      user->processPackets(*this);
    }
  return (true);
}

bool Server::run(void)
{
  this->_time->resetTime();

  while (true)
    {
      this->_listener->SNAddRead();
      this->_selector->setTimer(1, 0);
      if (!this->_selector->SNSelect())
	{
	  std::cerr << "Error: Select" << std::endl;
	  return (false);
	}
      if (this->_selector->getSec() == 0 && this->_selector->getUsec() == 0)
      	std::cout << "It's time to packet." << std::endl;
      this->getNewClient();
      this->readFromClients();
      this->processPackets();
      this->writeToClients();
      this->cleanClients();
    }
}

Game		*Server::getGameByUser(User *us)
{
  return (this->_gameManager.getGameFromUser(us));
}

TaskManager &Server::getTaskManager(void)
{
  return (this->_taskManager);
}

SafeQueue<PacketTask *> &Server::getTaskQueue(void)
{
  return (this->_taskQueue);
}

ICondVar		*Server::getCondVar(void)
{
  return (this->_condVar);
}

GameManager		&Server::getGameManager(void)
{
  return (this->_gameManager);
}
