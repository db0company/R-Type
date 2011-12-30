#include "TaskManager.hpp"

TaskManager::TaskManager(TaskNetwork &net)
  : _net(net)
{

}

// TaskManager::TaskManager(TaskNetwork &net, Game &game)
//   : _net(net), _game(game)
// {

// }

TaskManager::~TaskManager()
{

}

TaskManager	&TaskManager::operator=(const TaskManager &old)
{
  return (*this);
}

// Game		&TaskManager::getGame()
// {
//   return (this->_game);
// }

TaskNetwork	&TaskManager::getNet()
{
  return (this->_net);
}
