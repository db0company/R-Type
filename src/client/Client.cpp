#include <iostream>
#include "Client.hpp"
#include "Protocol.h"
#include "PacketData.hpp"
#include "PacketFactory.hpp"

Client::Client(void) : cNetwork("10.224.1.6", 12348), cGraphic(cNetwork)
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

bool Client::run(void)
{
  int i;

  i = 0;
  if (!this->cNetwork.connect("10.41.167.195", 12348))
    {
      //et pas en dur !
      return (false);
    }
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
      this->cGraphic.clean();
      this->cGraphic.draw();
      if (i == 0)
      	{
      	  PacketData *dataGame = new PacketData;
	  PacketData *data = new PacketData;
	  dataGame->addString("DarkK3vinNaruto666");
	  dataGame->addString("Game de la Mort");
	  dataGame->addString("lvl1");
	  dataGame->addChar(4);
	  dataGame->addChar(0);
	  data->addString("coucou lol");
	  ProtocolPacket *protocolPacket = PacketFactory::createPacket(THE_GAME, static_cast<ushort>(CREATEGAME), dataGame);
	  ProtocolPacket *protocolPacket1 = PacketFactory::createPacket(LOBBY, static_cast<ushort>(CHAT), data);
	  this->cNetwork.pushUDP(protocolPacket);
	  this->cNetwork.pushTCP(protocolPacket1);
	  ++i;
	}
      this->cNetwork.sendPacketToServer(); // static ok?
      this->cNetwork.process(*this);
    }
  return (true);
}
