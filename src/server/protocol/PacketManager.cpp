#include <string.h>
#include <cstdlib>
#include "PacketManager.hpp"
#include "actions/ProtocolGame.hpp"
#include "actions/ProtocolGameDetails.hpp"
#include "actions/ProtocolMovement.hpp"
#include "actions/ProtocolLobby.hpp"
#include "User.hpp"

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

bool				PacketManager::Process(ProtocolPacket *packet, User *user, Server &serv)
{
  PacketData *textData = PacketFactory::getPacketData(packet);
  if (this->groupaction.find(PacketFactory::getPacketGroup(packet)) == this->groupaction.end())
    {
      this->actionError();
      return (false);
    }
  else
    {
      // int group = PacketFactory::getPacketGroup(packet);
      // std::cout << "\033[31mGroup\033[00m(";
      // if (group == THE_GAME)
      // 	std::cout << "THE_GAME";
      // else if (group == GAME_DETAILS)
      // 	std::cout << "GAME_DETAILS";
      // else if (group == MOVEMENT)
      // 	std::cout << "MOVEMENT";
      // else if (group == LOBBY)
      // 	std::cout << "LOBBY";
      // else
      // 	std::cout << "ERROR@@@";
      // std::cout << ") \033[32mInst\033[00m(" <<
	// packet->header.instruction << ")" << std::endl;
      // uglyPrinter((char *)packet->data, packet->header.size);
      this->groupaction[PacketFactory::getPacketGroup(packet)]->action
      	(PacketFactory::getPacketInstruction(packet), *textData, user, serv);
    }
  return (true);
}

void				PacketManager::actionError(void)
{
  // if (v)
  //   std::cerr << "[warning] Invalid Packet Group: Ignored" << std::endl;
}
