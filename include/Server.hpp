#ifndef _SERVER_RTYPE_HPP_
#define _SERVER_RTYPE_HPP_

#include <list>
#include <string>
#include "user/User.hpp"
#include "GameManager.hpp"
#include "ATCPServerSocket.h"
#include "ISelector.h"

#define DEFAULT_PORT 12348

class Server
{
private:
  Server&operator=(Server const &);
  Server(Server const &);
public:
  Server(void);
  ~Server(void);
  bool init(int port = DEFAULT_PORT);
  bool run(void);
private:
  bool getNewClient(void);
  bool addClient(ATCPClientSocket *);
  bool readFromClient(void);
  bool removeClient(User *user, ATCPClientSocket *socket);
private:
  std::list<User *>		_userList;
  ATCPServerSocket*		_listener;
  ISelector*			_selector;
  GameManager			_gameManager;
  int				_port;
};

#endif// _SERVER_RTYPE_HPP_
