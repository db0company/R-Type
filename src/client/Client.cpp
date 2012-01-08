#include <iostream>
#include "Client.hpp"
#include "Protocol.h"
#include "PacketData.hpp"
#include "PacketFactory.hpp"
#include "EGraphicAction.hpp"

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

bool Client::gereAction(LibGraphic::Event e)
{
  switch (e)
    {
    case LibGraphic::EVENT_CHANGE_STATE :
      this->cGraphic.goToNextState();
      break;
    default : break;
    }
  return (true);
}

bool Client::run(void)
{
  LibGraphic::Event e;

  if (!this->cNetwork.connect("127.0.0.1", 12348))
    {
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
      e = this->cGraphic.getEvent();
      this->gereAction(e);
      this->cGraphic.clean();
      this->cGraphic.draw();
      this->cNetwork.sendPacketToServer();
      this->cNetwork.process(*this);
    }
  return (true);
}
