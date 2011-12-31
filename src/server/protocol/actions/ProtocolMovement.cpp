
#include		"ProtocolMovement.hpp"

ProtocolMovement::ProtocolMovement()
{
  this->actionmap[MOVEMENT_ERROR]	= &ProtocolMovement::actionError;
  this->actionmap[MOVE]			= &ProtocolMovement::actionMove ;
  this->actionmap[UPDATEPLAYER]		= &ProtocolMovement::actionUpdatePlayer;
  this->actionmap[UPDATEENEMY]		= &ProtocolMovement::actionUpdateEnemy;
  this->actionmap[UPDATEBULLET]		= &ProtocolMovement::actionUpdateBullet;
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

bool		ProtocolMovement::actionMove(PacketData &data, User *, Server &)
{
  (void)data;
  return (true);
}

bool		ProtocolMovement::actionUpdatePlayer(PacketData &data, User *, Server &)
{
  (void)data;
  return (true);
}

bool		ProtocolMovement::actionUpdateEnemy(PacketData &data, User *, Server &)
{
  (void)data;
  return (true);
}

bool		ProtocolMovement::actionUpdateBullet(PacketData &data, User *, Server &)
{
  (void)data;
  return (true);
}

bool		ProtocolMovement::actionNewBullet(PacketData &data, User *, Server &)
{
  (void)data;
  return (true);
}
