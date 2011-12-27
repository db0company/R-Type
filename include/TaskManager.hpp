#ifndef		__TASKMANAGER_HPP__
# define	__TASKMANAGER_HPP__

#include "TaskNetwork.hpp"
#include "Game.hpp"

class		TaskManager
{
private:
  TaskNetwork	&_net;
  Game		&_game;
public:
  TaskManager(TaskNetwork &net, Game &game);
  ~TaskManager();
  TaskManager	&operator=(const TaskManager &);
  Game		&getGame();
  TaskNetwork	&getNet();
};

#endif		/*__TASKMANAGER_HPP__*/
