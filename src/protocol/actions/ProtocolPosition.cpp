
#include		"ProtocolPosition.hpp"

ProtocolPosition::ProtocolPosition()
{
  this->actionmap[POSITION_ERROR] = &ProtocolPosition::actionError;
  this->actionmap[MOVE_PLAYER] = &ProtocolPosition::actionMovePlayer;
  this->actionmap[UPDATE_PLAYER] = &ProtocolPosition::actionUpdatePlayer;
  this->actionmap[UPDATE_ENEMY] = &ProtocolPosition::actionUpdateEnemy;
  this->actionmap[UPDATE_BULLETS] = &ProtocolPosition::actionUpdateBullets;
  this->actionmap[NEW_BULLET] = &ProtocolPosition::actionNewBullets;

}

ProtocolPosition::ProtocolPosition(ProtocolPosition const & other)
{
}

ProtocolPosition &		ProtocolPosition::operator=(ProtocolPosition const & other)
{
  if (&other != this)
    {
    }
  return (*this);
}

ProtocolPosition::~ProtocolPosition(void)
{
}

void			ProtocolPosition::action(ushort instruction,
						 PacketData & data)
{
  std::map<eProtocolPacketPosition, ptr_func>::iterator it;
  ptr_func		ptr;

  if (instruction >= POSITION_MAX)
    (void)this->actionError(data);
  if ((it = this->actionmap.find(static_cast<eProtocolPacketPosition>(instruction))) == this->actionmap.end())
    (void)this->actionError(data);
  ptr = it->second;
  (this->*ptr)(data);
  //  (void)((this->*actionmap[static_cast<eProtocolContact>(instruction)]) //oldx
}

bool			ProtocolPosition::actionError(PacketData &)
{
  return (true);
}


bool			ProtocolPosition::actionMovePlayer(PacketData & data)
{
  return (true);
}

bool			ProtocolPosition::actionUpdatePlayer(PacketData & data)
{
  return (true);
}

bool			ProtocolPosition::actionUpdateEnemy(PacketData & data)
{
  return (true);
}

bool			ProtocolPosition::actionUpdateBullets(PacketData & data)
{
  return (true);
}

bool			ProtocolPosition::actionNewBullets(PacketData & data)
{
  return (true);
}
