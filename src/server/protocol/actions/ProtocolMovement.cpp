
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
						 PacketData & data, User *, Server &)
{
  std::map<eProtocolPacketMovement, ptr_funct>::iterator it;
  ptr_funct		ptr;

  if (instruction >= MOVEMENT_MAX)
    (void)this->actionError(data);
  if ((it = this->actionmap.find(static_cast<eProtocolPacketMovement>(instruction))) == this->actionmap.end())
    {
    (void)this->actionError(data);
    return ;
    }
  ptr = it->second;
  (this->*ptr)(data);
  //  (void)((this->*actionmap[static_cast<eProtocolContact>(instruction)]) //oldx
}

bool			ProtocolMovement::actionError(PacketData &)
{
  return (true);
}

bool		ProtocolMovement::actionMove(PacketData &data)
{
  (void)data;
  return (true);
}

bool		ProtocolMovement::actionUpdatePlayer(PacketData &data)
{
  (void)data;
  return (true);
}

bool		ProtocolMovement::actionUpdateEnemy(PacketData &data)
{
  (void)data;
  return (true);
}

bool		ProtocolMovement::actionUpdateBullet(PacketData &data)
{
  (void)data;
  return (true);
}

bool		ProtocolMovement::actionNewBullet(PacketData &data)
{
  (void)data;
  return (true);
}
