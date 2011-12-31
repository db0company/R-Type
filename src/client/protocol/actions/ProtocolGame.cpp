
#include		"ProtocolGame.hpp"

ProtocolGame::ProtocolGame()
{
  this->actionmap[GAME_ERROR] = &ProtocolGame::actionError;
  this->actionmap[GETGAME] = &ProtocolGame::actionGet;
  this->actionmap[GETLEVELGAME] = &ProtocolGame::actionGetLevel;
  this->actionmap[CREATEGAME] = &ProtocolGame::actionCreate;
  this->actionmap[JOINGAME] = &ProtocolGame::actionJoin;
  this->actionmap[QUITGAME] = &ProtocolGame::actionQuit;
  this->actionmap[ENDGAME] = &ProtocolGame::actionEnd;
  this->actionmap[STARTGAME] = &ProtocolGame::actionStart;
}

ProtocolGame::ProtocolGame(ProtocolGame const & other)
{
  this->actionmap = other.actionmap;
}

ProtocolGame &		ProtocolGame::operator=(ProtocolGame const & other)
{
  if (&other != this)
    {
      this->actionmap = other.actionmap;
    }
  return (*this);
}

ProtocolGame::~ProtocolGame(void)
{
}

void			ProtocolGame::action(ushort instruction,
					     PacketData & data, Client &client)
{
  std::map<eProtocolPacketGame, ptr_func>::iterator it;
  ptr_func		ptr;

  if (instruction >= GAME_MAX)
    (void)this->actionError(data, client);
  if ((it = this->actionmap.find(static_cast<eProtocolPacketGame>(instruction))) == this->actionmap.end())
    {
      (void)this->actionError(data, client);
      return ;
    }
  ptr = it->second;
  (this->*ptr)(data, client);
}

bool			ProtocolGame::actionError(PacketData &, Client &)
{
  return (true);
}

bool			ProtocolGame::actionGet(PacketData & data, Client &)
{
  (void)data;
  return (true);
}

bool			ProtocolGame::actionGetLevel(PacketData & data, Client &)
{
  (void)data;
    return (true);
}

bool			ProtocolGame::actionCreate(PacketData & data, Client &)
{
  (void)data;
  return (true);
}

bool			ProtocolGame::actionJoin(PacketData & data, Client &)
{
  (void)data;
  return (true);
}

bool			ProtocolGame::actionQuit(PacketData & data, Client &)
{
  (void)data;
  return (true);
}
bool			ProtocolGame::actionEnd(PacketData & data, Client &)
{
  (void)data;
  return (true);
}

bool			ProtocolGame::actionStart(PacketData & data, Client &)
{
  (void)data;
  return (true);
}
