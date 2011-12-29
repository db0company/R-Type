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
  this->groupaction[THE_GAME] = new ProtocolGame;
  this->groupaction[GAME_DETAILS] = new ProtocolGameDetails;
  this->groupaction[MOVEMENT] = new ProtocolMovement;
  this->groupaction[LOBBY] = new ProtocolLobby;
}

PacketManager::PacketManager(PacketManager const &other)
{
  this->groupaction = other.groupaction;
}

PacketManager &		PacketManager::operator=(PacketManager const & other)
{
  if (&other != this)
    {
      this->groupaction = other.groupaction;
    }
  return (*this);
}

PacketManager::~PacketManager(void)
{
  //  delete this->groupaction[THE_GAME];
}

bool				PacketManager::Process(ProtocolPacket *packet, User *)
{
  std::cout << "group: " << PacketFactory::getPacketGroup(packet) << std::endl;
  PacketData *textData = PacketFactory::getPacketData(packet);
  // if (this->groupaction.find(PacketFactory::getPacketGroup(packet)) == this->groupaction.end())
  if (this->groupaction.find(PacketFactory::getPacketGroup(packet)) == this->groupaction.end())
    {
      // std::cout << "if here" << std::endl;
      this->actionError();
      return (false);
    }
  else
    {
      this->groupaction[PacketFactory::getPacketGroup(packet)]->action
      	(PacketFactory::getPacketInstruction(packet), *textData);
      //-> debug
      std::cout << "packet received ";
      textData->prettyPrint();
      //<- end debug
    }
  return (true);
}

void				PacketManager::actionError(void)
{
  if (v)
    std::cerr << "[warning] Invalid Packet Group: Ignored" << std::endl;
}
