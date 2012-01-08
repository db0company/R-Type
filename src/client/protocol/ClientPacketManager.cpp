# include <iostream>
# include <string.h>
# include <cstdlib>
# include "ClientPacketManager.hpp"
# include "actions/ProtocolGame.hpp"
# include "actions/ProtocolGameDetails.hpp"
# include "actions/ProtocolMovement.hpp"
# include "actions/ProtocolLobby.hpp"

ClientPacketManager::ClientPacketManager(void)
{
  this->groupaction[THE_GAME] = new ProtocolGame;
  this->groupaction[GAME_DETAILS] = new ProtocolGameDetails;
  this->groupaction[MOVEMENT] = new ProtocolMovement;
  this->groupaction[LOBBY] = new ProtocolLobby;
}

ClientPacketManager::ClientPacketManager(ClientPacketManager const &other)
{
  this->groupaction = other.groupaction;
}

ClientPacketManager &		ClientPacketManager::operator=(ClientPacketManager const & other)
{
  if (&other != this)
    {
      this->groupaction = other.groupaction;
    }
  return (*this);
}

ClientPacketManager::~ClientPacketManager(void)
{
  //  delete this->groupaction[THE_GAME];
}

bool				ClientPacketManager::Process(ProtocolPacket *packet, Client& client)
{
  PacketData *textData = PacketFactory::getPacketData(packet);
  if (this->groupaction.find(PacketFactory::getPacketGroup(packet)) == this->groupaction.end())
    {
      this->actionError();
      return (false);
    }
  else
    {
      int group = PacketFactory::getPacketGroup(packet);
      std::cout << "\033[31mGroup\033[00m(";
      if (group == THE_GAME)
	std::cout << "THE_GAME";
      else if (group == GAME_DETAILS)
	std::cout << "GAME_DETAILS";
      else if (group == MOVEMENT)
	std::cout << "MOVEMENT";
      else if (group == LOBBY)
	std::cout << "LOBBY";
      else
	std::cout << "ERROR@@@";
      std::cout << ") \033[32mInst\033[00m(" <<
	PacketFactory::getPacketInstruction(packet) << ")" << std::endl;
      return (this->groupaction[PacketFactory::getPacketGroup(packet)]->action
	      (PacketFactory::getPacketInstruction(packet), *textData, client));
    }
  return (false);
}

void				ClientPacketManager::actionError(void)
{
  // if (v)
  //std::cerr << "[warning] Invalid Packet Group: Ignored" << std::endl;
}
