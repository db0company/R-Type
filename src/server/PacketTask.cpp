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
  if (this->gameFunc == &Game::changePlayerPos)
    {
      std::cout << "&Game::changePlayerPos" << std::endl;
    }
  if (this->gameFunc == &Game::moveMonster)
    {
      std::cout << "&Game::moveMonster" << std::endl;
    }
  if (this->gameFunc == &Game::createNewMonster)
    {
      std::cout << "&Game::createNewMonster" << std::endl;
    }
  if (this->gameFunc == &Game::checkCollision)
    {
      std::cout << "&Game::checkCollision" << std::endl;
    }
  if (this->gameFunc == &Game::moveBullet)
    {
      std::cout << "&Game::moveBullet" << std::endl;
    }
  if (this->gameFunc == &Game::fireBullet)
    {
      std::cout << "&Game::fireBullet" << std::endl;
    }
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
      // std::cout << "#######jai locker " << std::endl;
      (this->game->*gameFunc)(gp);
    }
  // else if (this->gameFunc == NULL && this->netFunc != NULL && this->network != NULL)
  //   {
  //   //   ScopedLock	sc(this->game->getMutex());

  //   //   (this->network->*netFunc)(*this->param);
  //   // }
  // std::cout << "#######jai FINI DE LOCKer " << std::endl;
}

