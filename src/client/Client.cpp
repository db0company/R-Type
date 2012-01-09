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
}

bool Client::actionConnect(void)
{
  if (!this->cNetwork.isConnected())
    {
      if (!this->cNetwork.connect(this->cGraphic.getIp(),
				  this->cGraphic.getPort()))
	this->cGraphic.errorMessage("Can't connect to Server " +
				    this->cGraphic.getIp() + "\n");
    }
  else
    this->cGraphic.setCurrentState(LibGraphic::ROOMLIST);
  return (true);
}

bool Client::actionJoin(std::string const &id, int id_game, bool obs)
{
  ProtocolPacket	*packet;
  PacketData		*data;

  data = new PacketData;
  data->addString(id);
  data->addShort(id_game);
  data->addChar(obs);

  packet = new ProtocolPacket;
  packet->header.size = data->getDataSize();
  packet->header.group = THE_GAME;
  packet->header.instruction = JOINGAME;
  packet->header.magic = PACKET_MAGIC;

  packet->data = data->getData();
  this->cNetwork.pushTCP(packet);
  return (true);
}

bool Client::actionCreate(std::string const &log, std::string const &name,
			  std::string const &lvl, int slot, bool spec)
{
  ProtocolPacket	*packet;
  PacketData		*data;

  data = new PacketData;
  data->addString(log);
  data->addString(name);
  data->addString(lvl);
  data->addChar(slot);
  data->addChar(spec);

  packet = new ProtocolPacket;
  packet->header.size = data->getDataSize();
  packet->header.group = THE_GAME;
  packet->header.instruction = CREATEGAME;
  packet->header.magic = PACKET_MAGIC;

  packet->data = data->getData();
  this->cNetwork.pushTCP(packet);
  return (true);
}


bool Client::actionRefresh(void)
{
  ProtocolPacket	*packet;
  PacketData		*data;

  data = new PacketData;
  packet = new ProtocolPacket;
  packet->header.size = 0;
  packet->header.group = THE_GAME;
  packet->header.instruction = GETGAME;
  packet->header.magic = PACKET_MAGIC;
  packet->data = data->getData();

  this->cNetwork.pushTCP(packet);
  return (true);
}

bool Client::gereAction(LibGraphic::Event e, bool state_network)
{
  switch (e)
    {
    case LibGraphic::EVENT_START_PLAY :
      {
	this->actionConnect();
	break;
      }
    case LibGraphic::EVENT_ROOMLIST_REFRESH :
      {
	this->actionRefresh();
	break;
      }
    case LibGraphic::EVENT_ROOMLIST_JOIN :
      {
	this->actionJoin(this->cGraphic.getLogin(),
			 this->cGraphic.getIdGame(), false);
	break;
      }
    case LibGraphic::EVENT_ROOMLIST_SPECTATE :
      {
	this->actionJoin(this->cGraphic.getLogin(),
			 this->cGraphic.getIdGame(), true);
	break;
      }
    case LibGraphic::EVENT_CREATE_CREATE :
      {
	this->actionCreate(this->cGraphic.getLogin(), this->cGraphic.getGameName(),
			   this->cGraphic.getLevel(), this->cGraphic.getSlot(),
			   this->cGraphic.getSpectator());
	break;
      }
    case LibGraphic::EVENT_CHANGE_STATE :
      {
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

LibGraphic::Sfml &Client::getGraphic(void)
{
  return (this->cGraphic);
}
