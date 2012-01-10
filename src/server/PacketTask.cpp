#include "PacketTask.hpp"
#include "TaskManager.hpp"
#include "ScopedLock.hpp"

PacketTask::PacketTask(void (TaskNetwork::*point)(PacketData&), PacketData& d, TaskNetwork *t)
  : param(d)
{
  this->gameFunc = NULL;
  this->netFunc = point;
  this->network = t;
}

PacketTask::PacketTask(void (Game::*point)(PacketData&), PacketData& d, Game *g)
  : param(d)
{
  this->netFunc = NULL;
  this->gameFunc = point;
  this->game = g;
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
  if (this->netFunc == NULL && this->gameFunc != NULL && this->game != NULL)
    {
      ScopedLock	sc(this->game->getMutex());

      (this->game->*gameFunc)(this->param);
    }
  else if (this->gameFunc == NULL && this->netFunc != NULL && this->network != NULL)
    {
      ScopedLock	sc(this->game->getMutex());

      (this->network->*netFunc)(this->param);
    }
}

