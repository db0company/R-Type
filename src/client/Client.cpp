#include <iostream>
#include "Client.hpp"
#include "Protocol.h"
#include "PacketData.hpp"
#include "PacketFactory.hpp"
#include "EGraphicAction.hpp"
#include "GraphicUtils.hpp"

Client::Client(void) : cNetwork("127.0.0.1", 12348), cGraphic(cNetwork)
{}

Client::~Client(void)
{}

Client::Client(const Client&other) :
  cNetwork(other.cNetwork), cGraphic(cNetwork)
{}

Client&	Client::operator=(const Client&)
{
  return *this;
}

Client::Client(std::string const &ip, int port) :
  cNetwork(ip, port), cGraphic(cNetwork)
{
}

bool Client::init(void)
{
  if (!this->cGraphic.init())
    {
      std::cerr << "Error: Can't initialize sfml" << std::endl;
      return (false);
    }
  return (true);
  this->cNetwork.setIp("127.0.0.1");
  this->cNetwork.setPort(12348);
}

bool Client::gereAction(void)
{
  eGraphicAction action = this->cGraphic.getAction();

  if (action == UNKNOWN)
    return (false);
  if (action == START_PLAY)
    {
      if (!this->cNetwork.isConnected())
	{
	  if (!this->cNetwork.connect(this->cGraphic.getIp(),
				      this->cGraphic.getPort()))
	    {
	      std::cout << "todo: afficher un pop up erreur"
			<< std::endl;
	      this->cGraphic.setAction(UNKNOWN);
	      return (false);
	    }
	}
      this->cGraphic.setAction(UNKNOWN);
      this->cGraphic.setNextState(LibGraphic::ROOMLIST);
      this->cGraphic.goToNextState();
    }
  else if (action == ROOMLIST_REFRESH)
    {
      ProtocolPacket *packet_to_send;
      PacketData *to_send = new PacketData;

      packet_to_send = PacketFactory::createPacket(THE_GAME,
		   static_cast<ushort>(GETGAME), to_send);
      this->cNetwork.pushTCP(packet_to_send);
      this->cGraphic.setAction(UNKNOWN);
    }
  else if (action == ROOMLIST_JOIN)
    {
      this->cGraphic.setAction(UNKNOWN);

      ProtocolPacket *packet_to_send;
      PacketData *to_send = new PacketData;

      std::cout << "get name: " << this->cGraphic.getName() << std::endl;
      to_send->addString(this->cGraphic.getName());
      to_send->addShort(0);
      to_send->addChar(0);
      packet_to_send = PacketFactory::createPacket(THE_GAME,
		   static_cast<ushort>(JOINGAME), to_send);
      this->cNetwork.pushTCP(packet_to_send);
      this->cGraphic.setNextState(LibGraphic::ROOM);
      this->cGraphic.goToNextState();
    }
  else if (action == ROOMLIST_SPECTATE)
    {
      this->cGraphic.setAction(UNKNOWN);

      ProtocolPacket *packet_to_send;
      PacketData *to_send = new PacketData;

      std::cout << "get name: " << this->cGraphic.getName() << std::endl;
      to_send->addString(this->cGraphic.getName());
      to_send->addShort(0);
      to_send->addChar(1);
      packet_to_send = PacketFactory::createPacket(THE_GAME,
		   static_cast<ushort>(JOINGAME), to_send);
      this->cNetwork.pushTCP(packet_to_send);

      this->cGraphic.setNextState(LibGraphic::ROOM);
      this->cGraphic.goToNextState();
    }
  // else if (action == CREATE_CREATE)
  //   {
  //   }
  // else if (action == ROOM_CHAT)
  //   {
  //   }
  return (true);
}

bool Client::run(void)
{
  // if (!this->cNetwork.connect("127.0.0.1", 12348))
  //   {
  //     //et pas en dur !
  //     return (false);
  //   }
  while (true)
    {
      if (!this->cNetwork.select())
      	{
      	  std::cerr << "Error: Can't Monitor Sockets" << std::endl;
      	  return (false);
      	}
      this->cNetwork.feedPacketAggregatorTCP();
      this->cNetwork.feedPacketAggregatorUDP();
      this->cGraphic.getEvent();
      this->gereAction();
      this->cGraphic.clean();
      this->cGraphic.draw();
      this->cNetwork.sendPacketToServer(); // static ok?
      this->cNetwork.process(*this);
    }
  return (true);
}
