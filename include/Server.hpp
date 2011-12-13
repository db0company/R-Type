#ifndef _SERVER_RTYPE_HPP_
#define _SERVER_RTYPE_HPP_

#include <list>
#include <string>
#include "User.hpp"
//#include "GameManager.hpp"
#include "ATCPServerSocket.h"
#include "ISelector.h"

class Server
{
private:
  Server&operator=(Server const &);
  Server(Server const &);
public:
  Server(void);
  ~Server(void);
  bool init(int port = 12348);
  bool run(void);
private:
  bool getNewClient(void);
  bool addClient(void);
private:
  //  std::map<std::string, User *> _usersMap;
  std::list<User *>		_userList;
  ATCPServerSocket*		_listener;
  ISelector*			_selector;
  //  GameManager			_gameManager;
  int				_port;
};

#endif// _SERVER_RTYPE_HPP_
