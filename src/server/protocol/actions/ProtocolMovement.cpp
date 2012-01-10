#include "Server.hpp"
#include		"ProtocolMovement.hpp"
#include "PacketTask.hpp"

ProtocolMovement::ProtocolMovement()
{
  this->actionmap[MOVEMENT_ERROR]	= &ProtocolMovement::actionError;
  this->actionmap[MOVE]			= &ProtocolMovement::actionMove ;
  this->actionmap[UPDATEPLAYER]		= &ProtocolMovement::actionError;
  this->actionmap[UPDATEENEMY]		= &ProtocolMovement::actionError;
  this->actionmap[UPDATEBULLET]		= &ProtocolMovement::actionError;
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

  tmp = serv.getGameByUser(us);
  if (tmp != NULL)
    {
      pt = new PacketTask(&Game::changePlayerPos, data, tmp);
      serv.getTaskQueue().push(pt);
      serv.getCondVar()->signal();
      return (true);
    }
  return (false);
}

// bool		ProtocolMovement::actionUpdatePlayer(PacketData &, User *, Server &)
// {
//   // nothing to do ;)
//   return (true);
// }

// bool		ProtocolMovement::actionUpdateEnemy(PacketData &, User *, Server &)
// {
//   // nothing to do ;)
//   return (true);
// }

// bool		ProtocolMovement::actionUpdateBullet(PacketData &, User *, Server &)
// {
//   // nothing to do ;)
//   return (true);
// }

bool		ProtocolMovement::actionNewBullet(PacketData &, User *, Server &)
{
  // TODO: si le client nest pas dans une game qui a start: ignor msg
  // sinon on creer un AOBject bullet associe a ce client et on envoi a tt les
  // client de la game (y compri le lanceur) par UDP qu'il y a un new bullet
  // avec les positions
  return (true);
}
