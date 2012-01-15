#include <iostream>
#include "PacketFactory.hpp"
#include "ProtocolPacket.h"
#include "ProtocolGame.hpp"
#include "User.hpp"
#include "TaskNetwork.hpp"
#include "PacketTask.hpp"
#include "Server.hpp"
#include "eProtocolPacketLobby.hpp"
#include "ScopedLock.hpp"

ProtocolGame::ProtocolGame()
{
  this->actionmap[GAME_ERROR] = &ProtocolGame::actionError;
  this->actionmap[GETGAME] = &ProtocolGame::actionGet;
  this->actionmap[GETLEVELGAME] = &ProtocolGame::actionGetLevel;
  this->actionmap[CREATEGAME] = &ProtocolGame::actionCreate;
  this->actionmap[JOINGAME] = &ProtocolGame::actionJoin;
  this->actionmap[QUITGAME] = &ProtocolGame::actionQuit;
  this->actionmap[ENDGAME] = &ProtocolGame::actionError;
  this->actionmap[STARTGAME] = &ProtocolGame::actionStart;
}

ProtocolGame::ProtocolGame(ProtocolGame const & other)
{
  this->actionmap = other.actionmap;
}

ProtocolGame &		ProtocolGame::operator=(ProtocolGame const & other)
{
  if (&other != this)
    {
      this->actionmap = other.actionmap;
    }
  return (*this);
}

ProtocolGame::~ProtocolGame(void)
{
}

void			ProtocolGame::action(ushort instruction,
					     PacketData & data, User *user, Server &serv)
{
  std::map<eProtocolPacketGame, ptr_func>::iterator it;
  ptr_func		ptr;

  if (instruction >= GAME_MAX)
    (void)this->actionError(data, user, serv);
  if ((it = this->actionmap.find(static_cast<eProtocolPacketGame>(instruction))) == this->actionmap.end())
    {
      (void)this->actionError(data, user, serv);
      return ;
    }
  ptr = it->second;
  (this->*ptr)(data, user, serv);
}

bool			ProtocolGame::actionError(PacketData &, User *, Server &)
{
  return (true);
}

bool			ProtocolGame::actionGet(PacketData &, User *user, Server &server)
{
  PacketData  *to_send = new PacketData;
  ProtocolPacket *packet_to_send;
  std::map<int, Game *> &map =  server.getGameManager().getGames();
  std::map<int, Game *>::iterator it;
  Game *tmp = NULL;
  int nb_game = 0;

  for (it = map.begin(); it != map.end(); ++it)
    {
      if ((*it).second->getStatus() != ENDED)
	{
	  ++nb_game;
	}
    }
  to_send->addShort(nb_game);
  for (it = map.begin(); it != map.end(); ++it)
    {
      tmp = (*it).second;
      if (tmp->getStatus() != ENDED)
	{
	  to_send->addShort(tmp->getId());
	  to_send->addString(tmp->getOwnerLogin());
	  to_send->addString(tmp->getName());
	  to_send->addString(tmp->getLvlName());
	  to_send->addChar(tmp->getPlayerMax());
	  to_send->addChar(tmp->getObs());
	  to_send->addChar(tmp->getNbPlayer());
	}
    }
  packet_to_send = PacketFactory::createPacket(THE_GAME, static_cast<ushort>(GETGAME), to_send);
  user->addPacketToSend(packet_to_send);
  return (true);
}

bool			ProtocolGame::actionGetLevel(PacketData &, User *user, Server &)
{
  PacketData  *to_send = new PacketData;
  ProtocolPacket *packet_to_send;

  to_send->addShort(2);
  to_send->addString("Star");
  to_send->addString("Sun");
  //  to_send->addString("Moon"); + add 1 au short!
  packet_to_send = PacketFactory::createPacket(THE_GAME, static_cast<ushort>(GETLEVELGAME), to_send);
  user->addPacketToSend(packet_to_send);
  return (true);
}

bool			ProtocolGame::actionCreate(PacketData & received, User *user,
						   Server &server)
{
  std::string name;
  std::string game_name;
  std::string game_lvl;
  char	      player_max;
  char	      observer;
  PacketData  *to_send = new PacketData;
  ProtocolPacket *packet_to_send;

  name = received.getNextString();
  game_name = received.getNextString();
  game_lvl = received.getNextString();
  player_max = received.getNextChar();
  observer = received.getNextChar();
  if (game_name.size() < 3)
    {
      to_send->addChar(0);
      to_send->addString("The Game's name must contain at least 3 characters");
      packet_to_send = PacketFactory::createPacket(THE_GAME, static_cast<ushort>(CREATEGAME), to_send);
      user->addPacketToSend(packet_to_send);
      return (false);
    }
  if (server.getGameManager().getGameFromName(game_name) != NULL &&
      server.getGameManager().getGameFromName(game_name)->getStatus() != ENDED)
    {
      to_send->addChar(0);
      to_send->addString("This name already exist");
      packet_to_send = PacketFactory::createPacket(THE_GAME, static_cast<ushort>(CREATEGAME), to_send);
      user->addPacketToSend(packet_to_send);
      return (false);
    }
  if (!(game_lvl == "Star" || game_lvl == "Sun"))
    {
      to_send->addChar(0);
      to_send->addString("The map " + game_lvl + " don't exist");
      packet_to_send = PacketFactory::createPacket(THE_GAME, static_cast<ushort>(CREATEGAME), to_send);
      user->addPacketToSend(packet_to_send);
      return (false);
    }
  if (player_max < 1 || player_max > 4)
    {
      to_send->addChar(0);
      to_send->addString("Number of Player must be between 1 and 4");
      to_send->prettyPrint();
      packet_to_send = PacketFactory::createPacket(THE_GAME, static_cast<ushort>(CREATEGAME), to_send);
      user->addPacketToSend(packet_to_send);
      return (false);
    }
  Game		*game;

  game = new Game;
  user->setLogin(name);
  game->setOwnerId(name);
  game->setName(game_name);
  game->setLvlName(game_lvl);
  game->setPlayerMax(player_max);
  game->setObs(observer);
  game->addUser(user, true, false, name);
  server.getGameManager().addGame(game);
  to_send->addChar(1);
  packet_to_send = PacketFactory::createPacket(THE_GAME, static_cast<ushort>(CREATEGAME), to_send);
  PacketData *to_send_log = new PacketData;
  ProtocolPacket *packetlogin;
  to_send_log->addChar(1);
  to_send_log->addString(name);
  packetlogin = PacketFactory::createPacket(LOBBY,
  static_cast<ushort>(LOBBY_PLAYERS), to_send_log);
  user->addPacketToSend(packet_to_send);
  user->addPacketToSend(packetlogin);
  user->setState(USER_GAME_ROOT);
  user->setGame(game);
  return (true);
}

bool		ProtocolGame::actionJoin(PacketData & received,
					 User *user, Server &server)
{
  PacketData	*to_send = new PacketData;
  ProtocolPacket *packet_to_send;
  std::string	login;
  short		id_game;
  char		observer;
  Game		*game;
  bool		exist = false;

  login = received.getNextString();
  id_game = received.getNextShort();
  observer = received.getNextChar();
  if ((game = server.getGameManager().getGameFromId(id_game)) == NULL ||
      game->getStatus() == ENDED)
    {
      // ScopedLock s(game->getMutex()); // Mserver
      to_send->addChar(0);
      to_send->addString("This Game don't Exist");
      packet_to_send = PacketFactory::createPacket(THE_GAME,
		   static_cast<ushort>(JOINGAME), to_send);
      user->addPacketToSend(packet_to_send);
      return (false);
    }
  if (game->getStatus() == INGAME)
    {
      to_send->addChar(0);
      to_send->addString("This Game already started");
      packet_to_send = PacketFactory::createPacket(THE_GAME,
				static_cast<ushort>(JOINGAME), to_send);
      user->addPacketToSend(packet_to_send);
      return (false);
    }
  std::map<std::string, User *> &map = game->getUserMap();
  std::map<std::string, User *>::iterator uit;
  for (uit = map.begin(); uit != map.end(); ++uit)
    {
      if (login == uit->second->getLogin())
	exist = true;
    }
  if (exist)
    {
      to_send->addChar(0);
      to_send->addString("This login is already Taken for this Game");
      packet_to_send = PacketFactory::createPacket(THE_GAME,
				static_cast<ushort>(JOINGAME), to_send);
      user->addPacketToSend(packet_to_send);
      return (false);
    }
  if (observer)
    {
      if (game->getObs() == false)
	{
	  to_send->addChar(0);
	  to_send->addString("This game don't accept Spectators");
	  packet_to_send = PacketFactory::createPacket(THE_GAME,
	       static_cast<ushort>(JOINGAME), to_send);
	  user->addPacketToSend(packet_to_send);
	  return (false);
	}
    }
  else
    {
      if (game->getNbPlayer() >= game->getPlayerMax())
	{
	  to_send->addChar(0);
	  to_send->addString("This game is full.");
	  packet_to_send = PacketFactory::createPacket(THE_GAME,
	       static_cast<ushort>(JOINGAME), to_send);
	  user->addPacketToSend(packet_to_send);
	  return (false);
  	}
    }
  if (observer)
    user->setState(USER_GAME_SPECTATE);
  else
    user->setState(USER_GAME_PLAYER);
  // ScopedLock s(game->getMutex()); // Mserver
  game->addUser(user, false, (observer == 0 ? false : true), login);
  user->setLogin(login);
  user->setGame(game);
  to_send->addChar(1);
  packet_to_send = PacketFactory::createPacket(THE_GAME,
					       static_cast<ushort>(JOINGAME), to_send);
  user->addPacketToSend(packet_to_send);
  std::map<std::string , User *>::iterator it;
  PacketData	*to_send_log = new PacketData;
  ProtocolPacket *packetlogin;

  to_send_log->addChar(1);
  to_send_log->addString(login);
  packetlogin = PacketFactory::createPacket(LOBBY,
  static_cast<ushort>(LOBBY_PLAYERS), to_send_log);
  for (it = map.begin(); it != map.end(); ++it)
    {
      it->second->addPacketToSend(packetlogin);
    }
  return (true);
}

bool		ProtocolGame::actionQuit(PacketData &data, User *user, Server &)
{
  PacketData	*to_send_log = new PacketData;
  ProtocolPacket *packetlogin;
  PacketData	*to_send = new PacketData;
  ProtocolPacket *packet_to_send;
  std::string log = data.getNextString();
  Game *g;
  std::map<std::string, User *>maap;
  std::map<std::string, User *>::iterator it;

  if ((g = user->getGame()) == NULL)
    return (false);
  //  ScopedLock s(g->getMutex()); //Mserver
  maap = g->getUserMap();
  if (user->getState() == USER_GAME_ROOT)
    {
      if (g->getStatus() == LOBBYROOM)
	{
	  user->getGame()->setStatus(ENDED);
	  to_send->addShort(1);
	  to_send->addString(log);
	  to_send_log->addChar(-1);
	  to_send_log->addString(user->getLogin());
	  for (it = maap.begin(); it != maap.end(); ++it)
	    {
	      packetlogin = PacketFactory::createPacket(LOBBY,
			static_cast<ushort>(LOBBY_PLAYERS), to_send_log);
	      packet_to_send = PacketFactory::createPacket(THE_GAME,
		   static_cast<ushort>(QUITGAME), to_send);
	      it->second->addPacketToSend(packet_to_send);
	      it->second->addPacketToSend(packetlogin);
	    }
	  g->setStatus(ENDED);
	  return (false);
	}
      // g->delUser(log);
    }
  else
    {
      to_send->addShort(0);
      to_send->addString(log);
      to_send_log->addChar(-1);
      to_send_log->addString(user->getLogin());
      for (it = maap.begin(); it != maap.end(); ++it)
	{
	  packet_to_send = PacketFactory::createPacket(THE_GAME,
       static_cast<ushort>(QUITGAME), to_send);
	  packetlogin = PacketFactory::createPacket(LOBBY,
       static_cast<ushort>(LOBBY_PLAYERS), to_send_log);
	  it->second->addPacketToSend(packet_to_send);
	  it->second->addPacketToSend(packetlogin);
	}
      // g->delUser(log);
    }
  std::cout << "ici faut del le user/player de la game" << std::endl;
  return (true);
}

bool		ProtocolGame::actionStart(PacketData &, User *user, Server &)
{
  PacketData	*to_send = new PacketData;
  ProtocolPacket *packet_to_send;
  std::map<std::string, User *> map;
  std::map<std::string, User *>::iterator it;

  if (user->getState() == USER_GAME_ROOT && user->getGame() != NULL)
    {
      if (user->getGame()->getStatus() == LOBBYROOM)
	{
	  //	  ScopedLock s(user->getGame()->getMutex()); // Mserver
	  to_send->addChar(1);
	  to_send->addString(user->getGame()->getName());
	  to_send->addString(user->getGame()->getLvlName());
	  user->getGame()->setStatus(INGAME);
	  packet_to_send = PacketFactory::createPacket(THE_GAME,
						       static_cast<ushort>(STARTGAME), to_send);
	  map = user->getGame()->getUserMap();
	  for (it = map.begin(); it != map.end(); ++it)
	    {
	      user->getGame()->createNewPlayer(it->second, it->second->getLogin());
	      it->second->addPacketToSend(packet_to_send);
	    }
	}
      else
	{
	  to_send->addChar(0);
	  to_send->addString("Game Already Started");
	  packet_to_send = PacketFactory::createPacket(THE_GAME, static_cast<ushort>(STARTGAME), to_send);
	  user->addPacketToSend(packet_to_send);
	}
    }
  else
    {
      to_send->addChar(0);
      to_send->addString("You must be the game creator");
      packet_to_send = PacketFactory::createPacket(THE_GAME, static_cast<ushort>(STARTGAME), to_send);
      user->addPacketToSend(packet_to_send);
    }
  return (true);
}
