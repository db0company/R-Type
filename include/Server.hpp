#ifndef _SERVER_RTYPE_HPP_
#define _SERVER_RTYPE_HPP_

#include <map>
#include <queue>
#include <string>
#include "User.hpp"
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
  bool readFromClients(void);
  bool processPackets(void);
  bool writeToClients(void);
  bool cleanClients(void);
  bool removeClient(User *user, ATCPClientSocket *socket);
private:
  std::map<std::string, User *>	_userMap;
  std::queue<std::string>	_quitQueue;
  ATCPServerSocket*		_listener;
  ISelector*			_selector;
  GameManager			_gameManager;
  int				_port;
};

#endif// _SERVER_RTYPE_HPP_
