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
      else
	{
	  this->cGraphic.resetRoomListState();
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
  data->addChar(spec == true ? 1 : 0);

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
	this->cGraphic.resetRoomListState();
	this->cGraphic.setCurrentState(LibGraphic::ROOMLIST);
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

bool Client::actionMove(LibGraphic::eMovement e)
{
  ProtocolPacket *packet;
  PacketData *data = new PacketData;

  switch (e)
    {
    case LibGraphic::UP_LEFT :
      {
      data->addChar(-1);
      data->addChar(1);
      break;
      }
    case LibGraphic::UP :
      {
      data->addChar(0);
      data->addChar(1);
      break;
      }
    case LibGraphic::UP_RIGHT :
      {
      data->addChar(1);
      data->addChar(1);
      break;
      }
    case LibGraphic::RIGHT :
      {
      data->addChar(1);
      data->addChar(0);
      break;
      }
    case LibGraphic::DOWN_RIGHT :
      {
      data->addChar(1);
      data->addChar(-1);
      break;
      }
    case LibGraphic::DOWN :
      {
      data->addChar(0);
      data->addChar(-1);
      break;
      }
    case LibGraphic::DOWN_LEFT :
      {
      data->addChar(-1);
      data->addChar(-1);
      break;
      }
    case LibGraphic::LEFT :
      {
      data->addChar(-1);
      data->addChar(0);
      break;
      }
    default:
      return (false);
    }
  packet = new ProtocolPacket;
  packet->header.size = data->getDataSize();
  packet->header.group = MOVEMENT;
  packet->header.instruction = MOVE;
  packet->header.magic = PACKET_MAGIC;
  packet->data = data->getData();
  this->cNetwork.pushUDP(packet);
  return (true);
}

bool Client::run(void)
{
  LibGraphic::Event event;
  LibGraphic::eMovement move;
  LibGraphic::eBulletType bullet;

  while (true)
    {
      if (!this->cNetwork.select())
	{
	  std::cerr << "Error: Can't Monitor Sockets" << std::endl;
	  system("pause");
	  return (false);
	}
      if ((this->cNetwork.feedPacketAggregatorTCP() == false ||
	   this->cNetwork.feedPacketAggregatorUDP() == false) &&
	  this->cNetwork.isConnected())
	{
	  this->cNetwork.setConnected(false);
	  this->cGraphic.errorMessage("Disconnected From Server\n");
	  this->cGraphic.setCurrentState(LibGraphic::START);
	}
      this->cNetwork.sendPacketToServer();
      this->cNetwork.process(*this);
      event = this->cGraphic.getEvent();
      this->gereAction(event);
      if ((move = this->cGraphic.getLastMove()) != LibGraphic::NO_MOVE)
	actionMove(move);
      if ((bullet = this->cGraphic.getLastBullet()) != LibGraphic::NO_BULLET)
	actionBullet(bullet, this->cGraphic.getLogin());
      this->cGraphic.clean();
      this->cGraphic.draw();
      this->cNetwork.reset();
    }
  return (true);
}

LibGraphic::Sfml &Client::getGraphic(void)
{
  return (this->cGraphic);
}

bool Client::actionBullet(LibGraphic::eBulletType bullet, std::string const &name)
{
  ProtocolPacket	*packet;
  PacketData		*data;

  data = new PacketData;
  packet = new ProtocolPacket;

  data->addString(name);
  data->addChar(bullet);

  packet->header.group = MOVEMENT;
  packet->header.instruction = NEWBULLET;
  packet->header.magic = PACKET_MAGIC;
  packet->header.size = data->getDataSize();
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
