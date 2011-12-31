
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
						 PacketData & data, Client&c)
{
  std::map<eProtocolPacketMovement, ptr_funct>::iterator it;
  ptr_funct		ptr;

  if (instruction >= MOVEMENT_MAX)
    (void)this->actionError(data, c);
  if ((it = this->actionmap.find(static_cast<eProtocolPacketMovement>(instruction))) == this->actionmap.end())
    {
      (void)this->actionError(data, c);
    return ;
    }
  ptr = it->second;
  (this->*ptr)(data, c);
}

bool			ProtocolMovement::actionError(PacketData &, Client &)
{
  return (true);
}

bool		ProtocolMovement::actionMove(PacketData &data, Client &)
{
  (void)data;
  return (true);
}

bool		ProtocolMovement::actionUpdatePlayer(PacketData &data, Client &)
{
  (void)data;
  return (true);
}

bool		ProtocolMovement::actionUpdateEnemy(PacketData &data, Client &)
{
  (void)data;
  return (true);
}

bool		ProtocolMovement::actionUpdateBullet(PacketData &data, Client &)
{
  (void)data;
  return (true);
}

bool		ProtocolMovement::actionNewBullet(PacketData &data, Client &)
{
  (void)data;
  return (true);
}
