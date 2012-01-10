#include	<iostream>
#include	"PacketFactory.hpp"
#include	"ProtocolPacket.h"
#include	"ProtocolGame.hpp"
#include	"User.hpp"
#include	"TaskNetwork.hpp"
#include	"PacketTask.hpp"
#include	"Server.hpp"

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

  to_send->addShort(map.size());
  for (it = map.begin(); it != map.end(); ++it)
    {
      tmp = (*it).second;
      to_send->addShort(tmp->getId());
      to_send->addString(tmp->getOwnerLogin());
      to_send->addString(tmp->getName());
      to_send->addString(tmp->getLvlName());
      to_send->addChar(tmp->getPlayerMax());
      to_send->addChar(tmp->getObs());
      to_send->addChar(tmp->getNbPlayer());
    }
  packet_to_send = PacketFactory::createPacket(THE_GAME, static_cast<ushort>(GETGAME), to_send);
  user->addPacketToSend(packet_to_send);
  return (true);
}

bool			ProtocolGame::actionGetLevel(PacketData &, User *user, Server &)
{
  PacketData  *to_send = new PacketData;
  ProtocolPacket *packet_to_send;

  to_send->addShort(1);
  to_send->addString("level1");
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
  std::cout << "login(" << name << ") game(" << game_name << ") lvl("
	    << game_lvl << ") max(" << (int)player_max << ") observer("
	    << (int)observer << ")" << std::endl;

  if (game_name.size() < 3)
    {
      to_send->addChar(0);
      to_send->addString("The Game's name must contain at least 3 characters");
      packet_to_send = PacketFactory::createPacket(THE_GAME, static_cast<ushort>(CREATEGAME), to_send);
      user->addPacketToSend(packet_to_send);
      return (false);
    }
  if (server.getGameManager().getGameFromName(game_name) != NULL)
    {
      to_send->addChar(0);
      to_send->addString("This name already exist");
      packet_to_send = PacketFactory::createPacket(THE_GAME, static_cast<ushort>(CREATEGAME), to_send);
      user->addPacketToSend(packet_to_send);
      return (false);
    }
  // TODO : verrifier si le lvl existe
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
  game->setOwnerId(name);
  game->setName(game_name);
  game->setLvlName(game_lvl);
  game->setPlayerMax(player_max);
  game->setObs(observer);
  game->addUser(user, true, false, name);
  server.getGameManager().addGame(game);
  to_send->addChar(1);
  packet_to_send = PacketFactory::createPacket(THE_GAME, static_cast<ushort>(CREATEGAME), to_send);
  user->addPacketToSend(packet_to_send);
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

  login = received.getNextString();
  id_game = received.getNextShort();
  observer = received.getNextChar();
  std::cout << "login(" << login << ") id_game(" << id_game << ") observer("
	    << (int)observer << ")" << std::endl;
  if ((game = server.getGameManager().getGameFromId(id_game)) == NULL)
    {
      to_send->addChar(0);
      to_send->addString("This Game don't Exist");
      packet_to_send = PacketFactory::createPacket(THE_GAME,
                static_cast<ushort>(JOINGAME), to_send);
      user->addPacketToSend(packet_to_send);
      return (false);
    }
  // TODO: verrif si login dispo pour la game
  if (observer)
    {
      if (game->getObs() == false)
	{
	  to_send->addChar(0);
	  to_send->addString("This login is already Taken for this Game");
	  packet_to_send = PacketFactory::createPacket(THE_GAME,
                 static_cast<ushort>(JOINGAME), to_send);
	  user->addPacketToSend(packet_to_send);
	  return (false);
	}
    }
  game->addUser(user, false, (observer == 0 ? false : true), login);
  to_send->addChar(1);
  packet_to_send = PacketFactory::createPacket(THE_GAME, static_cast<ushort>(JOINGAME), to_send);
  user->addPacketToSend(packet_to_send);
  return (true);
}

bool			ProtocolGame::actionQuit(PacketData &, User *, Server &)
{
  // TODO: enlever le player de la game.
  // ne renvoi rien
  // BIG TODO: dire au autre clients qu'il se barre (add protocol)
  return (true);
}

bool			ProtocolGame::actionStart(PacketData &, User *user, Server &)
{
  PacketData	*to_send = new PacketData;
  ProtocolPacket *packet_to_send;

  // TODO: actionstart
  // verrifier si le user a bien creer la game (rootgame) et pas quit
  // et si la game est bien en mode lobby(attente dautre personne/chat)
  // si oui -> start game + envoyer packet ok. sinon envoyer packet failure
  to_send->addChar(0);
  to_send->addString("Not Yet implemented");
  packet_to_send = PacketFactory::createPacket(THE_GAME, static_cast<ushort>(STARTGAME), to_send);
  user->addPacketToSend(packet_to_send);
  return (true);
}
