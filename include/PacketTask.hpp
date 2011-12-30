#ifndef _PACKETTASK_HPP_
#define _PACKETTASK_HPP_

#include "TaskManager.hpp"
#include "Game.hpp"
#include "TaskNetwork.hpp"

class PacketTask
{
private:
  TaskManager	&manager;
  void *param;
  void (TaskNetwork::*netFunc)(void *);
  //  void (Game::*gameFunc)(void *);
public:
  PacketTask(TaskManager& man, void (TaskNetwork::*point)(void *),void *param);
  PacketTask(TaskManager& man, void (Game::*point)(void *), void *param);
  void	launchTask();
};

#endif // _PACKETTASK_HPP_
