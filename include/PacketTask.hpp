#ifndef _PACKETTASK_HPP_
#define _PACKETTASK_HPP_

#include "TaskManager.hpp"
#include "Game.hpp"
#include "TaskNetwork.hpp"
#include "ICondVar.hpp"

class PacketTask
{
private:
  PacketData	*param;
  Game		*game;
  TaskNetwork	*network;
  User		*us;
  void (TaskNetwork::*netFunc)(PacketData&);
  void (Game::*gameFunc)(GameParam&);
public:
  PacketTask(PacketTask const &other);
  PacketTask&operator=(PacketTask const &other);
  PacketTask(void (TaskNetwork::*point)(PacketData&), PacketData*, TaskNetwork *);
  PacketTask(void (Game::*point)(GameParam&), PacketData*, Game*, User *);
  void	launchTask(ICondVar *);
};

#endif // _PACKETTASK_HPP_
