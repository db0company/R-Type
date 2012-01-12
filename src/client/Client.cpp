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
	{
	  this->cGraphic.errorMessage("Can't connect to Server " +
				      this->cGraphic.getIp() + "\n");
	  return (false);
	}
    }
  this->actionRefresh();
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
  data->addChar(obs ? 1 : 0);

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

bool Client::actionChat(std::string const &log, std::string const &msg)
{
  ProtocolPacket	*packet;
  PacketData		*data;

  data = new PacketData;
  data->addString(log);
  data->addString(msg);

  packet = new ProtocolPacket;
  packet->header.size = data->getDataSize();
  packet->header.group = LOBBY;
  packet->header.instruction = CHAT;
  packet->header.magic = PACKET_MAGIC;

  packet->data = data->getData();
  this->cGraphic.setMessage("");
  this->cNetwork.pushTCP(packet);
  return (true);
}

bool Client::gereAction(LibGraphic::Event e)
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
	this->actionGetLvl();
	break;
      }
    case LibGraphic::EVENT_ROOMLIST_JOIN :
      {
	this->actionJoin(this->cGraphic.getLogin(),
			 this->cGraphic.getIdGame(), false);
	this->cGraphic.setGameForPreview(
	this->cGraphic.getGameForPreviewFromRoomlist());
	break;
      }
    case LibGraphic::EVENT_ROOMLIST_SPECTATE :
      {
	this->actionJoin(this->cGraphic.getLogin(),
			 this->cGraphic.getIdGame(), true);
	this->cGraphic.setGameForPreview(
	this->cGraphic.getGameForPreviewFromRoomlist());
	break;
      }
    case LibGraphic::EVENT_CREATE_CREATE :
      {
	this->actionCreate(this->cGraphic.getLogin(), this->cGraphic.getGameName(),
			   this->cGraphic.getLevel(), this->cGraphic.getSlot(),
			   this->cGraphic.getSpectator());
	this->cGraphic.setGameForPreview(
	this->cGraphic.getGameForPreviewFromCreate());
	break;
      }
    case LibGraphic::EVENT_ROOM_CHAT :
      {
	this->actionChat(this->cGraphic.getLogin(), this->cGraphic.getMessage());
	break;
      }
    case LibGraphic::EVENT_CHANGE_STATE :
      {
	this->cGraphic.goToNextState();
	break;
      }
    case LibGraphic::EVENT_ROOM_QUIT :
      {
	this->actionQuit();
	break;
      }
    case LibGraphic::EVENT_ROOM_START :
      {
	this->actionStart();
	break;
      }
    case LibGraphic::EVENT_ROOMLIST_CREATE :
      {
	this->actionGetLvl();
	this->cGraphic.setCurrentState(LibGraphic::CREATEGAME);
	break;
      }
    default : break;
    }
  return (true);
}

bool Client::run(void)
{
  LibGraphic::Event event;

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
      this->cNetwork.process(*this);
      event = this->cGraphic.getEvent();
      this->gereAction(event);
      this->cGraphic.clean();
      this->cGraphic.draw();
    }
  return (true);
}

LibGraphic::Sfml &Client::getGraphic(void)
{
  return (this->cGraphic);
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

bool Client::actionStart(void)
{
  ProtocolPacket	*packet;
  PacketData		*data;

  data = new PacketData;
  packet = new ProtocolPacket;
  packet->header.size = 0;
  packet->header.group = THE_GAME;
  packet->header.instruction = STARTGAME;
  packet->header.magic = PACKET_MAGIC;
  packet->data = data->getData();

  this->cNetwork.pushTCP(packet);
  return (true);
}

bool Client::actionQuit(void)
{
  ProtocolPacket	*packet;
  PacketData		*data;

  data = new PacketData;
  data->addString(this->cGraphic.getLogin());
  packet = new ProtocolPacket;
  packet->header.size = 0;
  packet->header.group = THE_GAME;
  packet->header.instruction = QUITGAME;
  packet->header.magic = PACKET_MAGIC;
  packet->data = data->getData();

  this->cNetwork.pushTCP(packet);
  return (true);
}

bool Client::actionGetLvl(void)
{
  ProtocolPacket	*packet;
  PacketData		*data;

  data = new PacketData;
  packet = new ProtocolPacket;
  packet->header.size = 0;
  packet->header.group = THE_GAME;
  packet->header.instruction = GETLEVELGAME;
  packet->header.magic = PACKET_MAGIC;
  packet->data = data->getData();

  this->cNetwork.pushTCP(packet);
  return (true);
}
