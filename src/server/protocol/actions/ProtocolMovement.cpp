#include "Server.hpp"
#include		"ProtocolMovement.hpp"
#include "PacketTask.hpp"

ProtocolMovement::ProtocolMovement()
{
  this->actionmap[MOVEMENT_ERROR]	= &ProtocolMovement::actionError;
  this->actionmap[MOVE]			= &ProtocolMovement::actionMove ;
  //  this->actionmap[UPDATEPLAYER]		= &ProtocolMovement::actionError;
  //  this->actionmap[UPDATEENEMY]		= &ProtocolMovement::actionError;
  //  this->actionmap[UPDATEBULLET]		= &ProtocolMovement::actionError;
  this->actionmap[NEWBULLET]		= &ProtocolMovement::actionNewBullet;
}

ProtocolMovement::ProtocolMovement(ProtocolMovement const & other)
{
  this->actionmap = other.actionmap;
}

ProtocolMovement &		ProtocolMovement::operator=(ProtocolMovement const & other)
{
  if (&other != this)
    {
      this->actionmap = other.actionmap;
    }
  return (*this);
}

ProtocolMovement::~ProtocolMovement(void)
{
}

void			ProtocolMovement::action(ushort instruction,
						 PacketData & data, User *user, Server &serv)
{
  std::map<eProtocolPacketMovement, ptr_funct>::iterator it;
  ptr_funct		ptr;

  if (instruction >= MOVEMENT_MAX)
    (void)this->actionError(data, user, serv);
  if ((it = this->actionmap.find(static_cast<eProtocolPacketMovement>(instruction))) == this->actionmap.end())
    {
      (void)this->actionError(data, user, serv);
      return ;
    }
  ptr = it->second;
  (this->*ptr)(data, user, serv);
}

bool			ProtocolMovement::actionError(PacketData &, User *, Server &)
{
  return (true);
}

bool		ProtocolMovement::actionMove(PacketData &data, User *us, Server &serv)
{
  PacketTask	*pt;
  Game		*tmp;
  PacketData	*newPack = new PacketData(data);

  // tmp = serv.getGameByUser(us);
  tmp = us->getGame();
  if (tmp != NULL && tmp->getStatus() != ENDED)
    {
      pt = new PacketTask(&Game::changePlayerPos, newPack, tmp, us);
      serv.getTaskQueue().push(pt);
      serv.getCondVar()->signal();
      return (true);
    }
  return (false);
}

bool		ProtocolMovement::actionNewBullet(PacketData &data, User *us, Server &serv)
{
  PacketTask	*pt;
  Game		*tmp;
  PacketData	*newPack = new PacketData(data);

  tmp = serv.getGameByUser(us);
  std::cout << "new packet" << std::endl;
  if (tmp != NULL && tmp->getStatus() != ENDED)
    {
      std::cout << "ITS WOORRK" << std::endl;
      pt = new PacketTask(&Game::fireBullet, newPack, tmp, us);
      serv.getTaskQueue().push(pt);
      serv.getCondVar()->signal();
      return (true);
    }
  return (false);
}
