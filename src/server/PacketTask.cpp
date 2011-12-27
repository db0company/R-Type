#include "PacketTask.hpp"
#include "TaskManager.hpp"

PacketTask::PacketTask(TaskManager& man, void (TaskNetwork::*point)(void *), void *p)
  : manager(man)
{
  this->gameFunc = NULL;
  this->netFunc = point;
  this->param = p;
}

PacketTask::PacketTask(TaskManager& man, void (Game::*point)(void *), void *p)
  : manager(man)
{
  this->netFunc = NULL;
  this->gameFunc = point;
  this->param = p;
}

void	PacketTask::launchTask()
{
  if (this->netFunc == NULL && this->gameFunc != NULL)
    {
      Game	g = manager.getGame();

      (g.*gameFunc)(this->param);
    }
  else if (this->gameFunc == NULL && this->netFunc != NULL)
    {
      TaskNetwork n = manager.getNet();

      (n.*netFunc)(this->param);
    }
}