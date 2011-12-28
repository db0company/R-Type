# include <string.h>
# include <cstdlib>
# include "verbose.h"
# include "PacketManager.hpp"
# include "ProtocolGame.hpp"
# include "ProtocolGameDetails.hpp"
# include "ProtocolMovement.hpp"
# include "ProtocolLobby.hpp"
# include "User.hpp"

PacketManager::PacketManager(void)
{
  this->groupaction[THE_GAME] = new ProtocolGame();
  this->groupaction[GAME_DETAILS] = new ProtocolGameDetails();
  this->groupaction[MOVEMENT] = new ProtocolMovement();
  this->groupaction[LOBBY] = new ProtocolLobby();
}

PacketManager::PacketManager(PacketManager const &)
{}

PacketManager &		PacketManager::operator=(PacketManager const & other)
{
  if (&other != this)
    {
    }
  return (*this);
}

PacketManager::~PacketManager(void)
{
  delete this->groupaction[THE_GAME];
}

bool				PacketManager::Process(ProtocolPacket *packet, User *)
{
  PacketData *textData = PacketFactory::getPacketData(packet);
  if (!this->groupaction[PacketFactory::getPacketGroup(packet)])
    {
      this->actionError();
      return (false);
    }
  else
    this->groupaction[PacketFactory::getPacketGroup(packet)]->action
      (PacketFactory::getPacketInstruction(packet), *textData);
  return (true);
}

void				PacketManager::actionError(void)
{
  if (v)
    std::cerr << "[warning] Invalid Packet Group: Ignored" << std::endl;
}
