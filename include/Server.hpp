#ifndef _SERVER_RTYPE_HPP_
#define _SERVER_RTYPE_HPP_

#include <map>
#include <queue>
#include <string>
#include "User.hpp"
#include "GameManager.hpp"
#include "ATCPServerSocket.h"
#include "AUDPServerSocket.h"
#include "ISelector.h"
#include "PacketManager.hpp"
#include "TaskManager.hpp"
#include "ThreadPool.hpp"
#include "ThreadData.hpp"
#include "PacketTask.hpp"
#include "IMutex.hpp"
#include "ICondVar.hpp"

#define DEFAULT_PORT 12348

class Server
{
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
  GameManager			_gameManager;
  TaskNetwork			_taskNet;
  TaskManager				_taskManager;
  ThreadPool<ThreadData<PacketTask> >	_threadPool;
  std::map<std::string, User *>	_userMap;
  std::queue<std::string>	_quitQueue;
  ATCPServerSocket*		_listener;
  IMutex*			_udpMutex;
  AUDPServerSocket*		_udp;
  ISelector*			_selector;
  PacketManager			_pm;
  int				_port;
};

#endif// _SERVER_RTYPE_HPP_
