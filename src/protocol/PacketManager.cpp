
# include		<string.h>
# include		<cstdlib>
# include		"verbose.h"
# include		"PacketManager.hpp"

# include		"actions/ProtocolGame.hpp"
# include		"actions/ProtocolGameDetails.hpp"
# include		"actions/ProtocolMovement.hpp"
# include		"actions/ProtocolLobby.hpp"

/* ************************************************************************* */
/*                             Coplien Form                                  */
/* ************************************************************************* */

PacketManager::PacketManager(void)
{
  this->groupaction[THE_GAME] = new ProtocolGame();
  this->groupaction[GAME_DETAILS] = new ProtocolGameDetails();
  // this->groupaction[MOVEMENT] = new ProtocolMovement();
  // this->groupaction[LOBBY] = new ProtocolLobby();
}

PacketManager::PacketManager(PacketManager const &)
{}

PacketManager &		PacketManager::operator=(PacketManager const & other)
{
  if (&other != this)
    {
      // If there is a pointer to something allocated, do this :
      // if (this->SomeThingAllocated)
      //   delete this->SomeThingAllocated;
      // this->SomeThingAllocated = CopyFunc(other.SomeThingAllocated);
    }
  return (*this);
}

PacketManager::~PacketManager(void)
{
  delete this->groupaction[THE_GAME];
}

/* ************************************************************************* */
/*                             Member Functions                              */
/* ************************************************************************* */

bool			PacketManager::send(User * user, eProtocolPacketGroup group,
					    ushort instruction,
					    PacketData & data,
					    bool udp)
{
  ISocket * socket = (udp ? /* todo: user->getSocketUDP()*/NULL : user->getSocketTCP());
  if (!socket)
    return (false);
  ProtocolPacket * packet = PacketFactory::createPacket(group, instruction, data);
  if (!packet)
    return (false);
  DataRawType * toSend = new DataRawType[sizeof(packet->header) +
					 PacketFactory::getPacketDataSize(packet)];
  memcpy(toSend, &(packet->header), sizeof(packet->header));
  memcpy(toSend + sizeof(packet->header), PacketFactory::getPacketData(packet),
	 PacketFactory::getPacketDataSize(packet));
  if ((socket->SNWrite(toSend, sizeof(packet->header)
		       + PacketFactory::getPacketDataSize(packet))) < 0)
    return (std::cerr << "[error] Send Packet Failure" << std::endl);
  delete[] toSend;
  PacketFactory::destroyPacket(packet);
  return (true);
}

bool				PacketManager::rcsv(User * user, bool udp)
{
  ProtocolPacket * packet = this->RcvPacket(user, udp);
  if (!packet)
    return (false);
  PacketData * textData = PacketFactory::getPacketData(packet);
  if (!this->groupaction[PacketFactory::getPacketGroup(packet)])
    this->actionError();
  else
    this->groupaction[PacketFactory::getPacketGroup(packet)]->action
      (PacketFactory::getPacketInstruction(packet), *textData/*, user*/);
  delete textData;
  PacketFactory::destroyPacket(packet);
  return (true);
}

// barbara j'ai besoin dune fonction qui prend un packet et un user et qui
// va appeler tes ptrfunct associe au type du packet. comme rcsv mais sans
// le read. Je l'ai faite la mais faut que tu vois si jai bien utiliser
// le packet factory et si il manque pas qqch
//
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

/* ************************************************************************* */
/*                            Private Functions                              */
/* ************************************************************************* */

void				PacketManager::actionError(void)
{
  if (v)
    std::cerr << "[warning] Invalid Packet Group: Ignored" << std::endl;
}

ProtocolPacket *		PacketManager::RcvPacket(User * user, bool udp)
{
  if (!user)
    return (NULL);
  int size = 0;
  ISocket * socket = (udp ? /*user->getSocketUDP()*/NULL : user->getSocketTCP());
  UserSocket & us = /*todo : (udp ? user->udp : */user->tcp;
  if (!(us.getHaveHeader()))
    {
      ProtocolPacketHeader & header = us.getHeader();
      if (((size = socket->SNRead(&header, sizeof(header)))
	   != sizeof(header)))
	{
	  if (size > 0 && v)
	    std::cerr << "[error] Read: Invalid Packet Header (Size = "
		      << size << ") -> Socket rejected" << std::endl;
	  // this->DeleteSocket(user);
	  // todo: important ! delete user from the list
	  return (NULL);
	}
      us.setHaveHeader(true);
      return (NULL);
    }
  ProtocolPacketHeader & header = us.getHeader();
  DataRawType * buffer = new DataRawType[header.size];
  if ((size = socket->SNRead(buffer, header.size)) != header.size)
    {
      if (size > 0 && v)
	    std::cerr << "[error] Read: Invalid Packet Data (Size = "
		      << size << ") -> Socket rejected" << std::endl;
      // this->DeleteSocket(user);
      // todo: important ! delete user from the list
      return (NULL);
    }
  us.setHaveHeader(false);
  return (PacketFactory::createPacket(static_cast<eProtocolPacketGroup>(header.group),
					   header.instruction,
					   buffer, header.size));
}

// void				PacketManager::DeleteSocket(UserNetwork * net,
// 							   User * user)
// {
//   if (!net)
//     return ;
//   net->sethaveHeader(false);
//   net->getsocket()->SNDelRead();
//   net->getsocket()->SNDelWrite();
//   net->getsocket()->SNClose();
//   if (user)
//     {
//       user->setStatus(OFFLINE);
//       if (v)
// 	io.PutErrNotify(user->getLogin(), "User Disconnected");
//       delete (net->getsocket());
//     }
//   else
//     {
//       io.PutErrNotify("Waiting Socket", "Socket Disconnected");
//       this->usermanager.delWaitingSocket(net);
//      }
//   net->setsocket(NULL);
// }
