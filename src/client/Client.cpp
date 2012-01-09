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

bool Client::gereAction(LibGraphic::Event e, bool state_network)
{
  switch (e)
    {
    case LibGraphic::EVENT_START_PLAY :
      {
	if (!this->cNetwork.isConnected())
	  {
	    std::cout << "je suis pas co" << std::endl;
	    if (this->cNetwork.connect(this->cGraphic.getIp(),
				       this->cGraphic.getPort()))
	      {
		this->cGraphic.setCurrentState(LibGraphic::ROOMLIST);
		std::cout << "connection ok" << std::endl;
	      }
	    else
	      {
		this->cGraphic.errorMessage("connection ko\n");
		// std::cout << "connection ko " << std::endl;
		// this->cGraphic.setCurrentState(LibGraphic::START);
	      }
	  }
	else
	  this->cGraphic.setCurrentState(LibGraphic::ROOMLIST);
	break;
      }
    case LibGraphic::EVENT_CHANGE_STATE :
      {
	// todo state network;
	this->cGraphic.goToNextState();
	break;
      }
    default : break;
    }
  return (true);
}

bool Client::run(void)
{
  LibGraphic::Event event;
  bool state_network;

  while (true)
    {
      if (!this->cNetwork.select())
      	{
      	  std::cerr << "Error: Can't Monitor Sockets" << std::endl;
      	  return (false);
      	}
      this->cNetwork.feedPacketAggregatorTCP();
      this->cNetwork.feedPacketAggregatorUDP();
      this->cNetwork.sendPacketToServer();
      state_network = this->cNetwork.process(*this);
      event = this->cGraphic.getEvent();
      this->gereAction(event, state_network);
      this->cGraphic.clean();
      this->cGraphic.draw();
    }
  return (true);
}
