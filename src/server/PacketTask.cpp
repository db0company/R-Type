#include "PacketTask.hpp"
#include "TaskManager.hpp"
#include "ScopedLock.hpp"

PacketTask::PacketTask(void (TaskNetwork::*point)(PacketData&), PacketData *d, TaskNetwork *t)
{
  this->gameFunc = NULL;
  this->netFunc = point;
  this->network = t;
  this->param = d;
  this->us = NULL;
}

PacketTask::PacketTask(void (Game::*point)(GameParam&), PacketData* d, Game *g, User *u)
  : param(d)
{
  this->netFunc = NULL;
  this->gameFunc = point;
  this->game = g;
  this->param = d;
  this->us = u;
}


PacketTask::PacketTask(PacketTask const &other)
  : param(other.param), netFunc(other.netFunc)
{

}

PacketTask& PacketTask::operator=(PacketTask const &other)
{
  this->param = other.param;  
  this->netFunc = other.netFunc;
  return *this;
}

void	PacketTask::launchTask(ICondVar *)
{
  GameParam	gp(this->param, this->us);

  if (this->netFunc == NULL && this->gameFunc != NULL && this->game != NULL)
    {
      ScopedLock	sc(this->game->getMutex());

      (this->game->*gameFunc)(gp);
    }
  else if (this->gameFunc == NULL && this->netFunc != NULL && this->network != NULL)
    {
      ScopedLock	sc(this->game->getMutex());

      (this->network->*netFunc)(*this->param);
    }
}

