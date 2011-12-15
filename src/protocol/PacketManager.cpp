
# include		<string.h>
# include		<cstdlib>
# include		"PacketManager.hpp"

//todo: vincent new objects from r-type, see RFC
//todo: vincent create them from the model actions/ProtocolExample.*pp
// # include		"protocol/actions/ProtocolUserManager.hpp"
// # include		"protocol/actions/ProtocolContactList.hpp"
// # include		"protocol/actions/ProtocolPrepareClients.hpp"

/* ************************************************************************* */
/*                             Coplien Form                                  */
/* ************************************************************************* */

PacketManager::PacketManager(void)
{
  // todo: vincent: the new map of new objects, new projet r-type it's a revolution !
  // this->groupaction[USERMANAGER] = new ProtocolUserManager(usermanager, *this);
  // this->groupaction[CONTACTLIST] = new ProtocolContactList(usermanager, *this);
  // this->groupaction[PREPARECLIENTS] = new ProtocolPrepareClients(usermanager, *this);
}

PacketManager::PacketManager(PacketManager const & other)
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
  // todo: vincent: delete r-type objects
  // delete (this->groupaction[USERMANAGER]);
  // delete (this->groupaction[CONTACTLIST]);
  // delete (this->groupaction[PREPARECLIENTS]);
}

/* ************************************************************************* */
/*                             Member Functions                              */
/* ************************************************************************* */

bool				PacketManager::send(User * user, eProtocolPacketGroup group,
						    ushort instruction,
						    ProtocolPacketData & data)
{
  // if (!user->getSocket())
  return (true);
}

// bool				PacketManager::send(UserNetwork & net, eProtocolPacketGroup group,
// 						   ushort instruction, char const * data, uint size)
// {
//   if (!net.getsocket())
//     return (false);
//   ProtocolPacket * packet = this->packetfactory.createPacket(group, instruction, data, size);
//   if (!packet)
//     return (false);
//   char * toSend = new char[sizeof(packet->header) + this->packetfactory.getPacketDataSize(packet)];
//   memcpy(toSend, &(packet->header), sizeof(packet->header));
//   memcpy(toSend + sizeof(packet->header), this->packetfactory.getPacketData(packet),
// 	 this->packetfactory.getPacketDataSize(packet));
//   if ((net.getsocket()->SNWrite(toSend, sizeof(packet->header)
// 				+ this->packetfactory.getPacketDataSize(packet))) < 0)
//     return (io.PutError("[error] Send Packet Failure"));
//   delete[] toSend;
//   this->packetfactory.destroyPacket(packet);
//   return (true);
// }

// bool				PacketManager::send(UserNetwork & net, eProtocolPacketGroup group,
// 				     ushort instruction, ProtocolPacketData & data)
// {
//   return (this->send(net, group, instruction, data.getstr(), data.getsize()));
// }

// bool				PacketManager::send(UserNetwork & net, eProtocolPacketGroup group,
// 				     ushort instruction, std::string const & data)
// {
//   ProtocolPacketData ndata(data);
//   return (this->send(net, group, instruction, ndata));
// }

// bool				PacketManager::rcsv(UserNetwork * net)
// {
//   ProtocolPacket * packet = this->RcvPacket(net);
//   if (!packet)
//     return (false);
//   ProtocolPacketData textData(this->packetfactory.getPacketData(packet),
//   			    this->packetfactory.getPacketDataSize(packet));
//   if (!this->groupaction[this->packetfactory.getPacketGroup(packet)])
//     {
//       this->actionError();
//     }
//   else
//     {
//       this->groupaction[this->packetfactory.getPacketGroup(packet)]->action
// 	(this->packetfactory.getPacketInstruction(packet), textData, *net);
//     }
//   this->packetfactory.destroyPacket(packet);
//   return (true);
// }

// bool				PacketManager::rcsv(User * user)
// {
//   ProtocolPacket * packet = this->RcvPacket(user->getUserNetwork(), user);
//   if (!packet)
//     return (false);
//   ProtocolPacketData textData(this->packetfactory.getPacketData(packet),
//   			    this->packetfactory.getPacketDataSize(packet));
//   if (!this->groupaction[this->packetfactory.getPacketGroup(packet)])
//     this->actionError();
//   else
//     this->groupaction[this->packetfactory.getPacketGroup(packet)]->action
//       (this->packetfactory.getPacketInstruction(packet), textData,
//        *(user->getUserNetwork()), user);
//   this->packetfactory.destroyPacket(packet);
//   return (true);
// }


// /* ************************************************************************* */
// /*                            Private Functions                              */
// /* ************************************************************************* */

// void				PacketManager::actionError(void)
// {
//   if (v)
//     io.PutErrorEndLine("[warning] Invalid Packet Group: Ignored");
// }

// ProtocolPacket *		PacketManager::RcvPacket(UserNetwork * net,
// 							User * user)
// {
//   if (!net || !(net->isConnected()))
//     {
//       this->DeleteSocket(net, user);
//       return (NULL);
//     }
//   int size = 0;
//   if (!(net->gethaveHeader()))
//     {
//       ProtocolPacketHeader & header = net->getheader();
//       if (((size = (net->getsocket())->SNRead(&header, sizeof(header)))
// 	   != sizeof(header)))
// 	{
// 	  if (size > 0 && v)
// 	    {
// 	      io.PutError("[error] Read: Invalid Packet Header (Size = ");
// 	      io.Put(size);
// 	      io.PutErrorEndLine(") -> Socket rejected");
// 	    }
// 	  this->DeleteSocket(net, user);
// 	  return (NULL);
// 	}
//       net->sethaveHeader(true);
//       return (NULL);
//     }
//   ProtocolPacketHeader & header = net->getheader();
//   char * buffer = reinterpret_cast<char *>(malloc(header.size + 1));
//   if (!buffer)
//     exit(0);
//   if ((size = (net->getsocket())->SNRead(buffer, header.size)) != header.size)
//     {
//       if (size > 0 && v)
// 	{
// 	  io.PutError("[error] Read: Invalid Packet Data (Size = ");
// 	  io.Put(size);
// 	  io.PutErrorEndLine(") -> Socket rejected");
// 	}
//       this->DeleteSocket(net, user);
//       return (NULL);
//     }
//   buffer[header.size] = '\0';
//   net->sethaveHeader(false);
//   return (this->packetfactory.createPacket(static_cast<eProtocolPacketGroup>(header.group),
// 					   header.instruction,
// 					   buffer, header.size));
// }

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
