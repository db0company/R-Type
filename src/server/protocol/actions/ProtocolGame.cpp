#include	<iostream>
#include	"PacketFactory.hpp"
#include	"ProtocolPacket.h"
#include	"ProtocolGame.hpp"
#include	"User.hpp"

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

bool			ProtocolGame::actionGet(PacketData &, User *user, Server &)
{
  PacketData  *to_send = new PacketData;
  ProtocolPacket *packet_to_send;
  // TODO:
  // to_send: [id_group(short), login(string), game_name(string),
  //             lvl(string), player_max(char), observer(char), nb_player(char)]+
  packet_to_send = PacketFactory::createPacket(THE_GAME, static_cast<ushort>(GETGAME), to_send);
  user->addPacketToSend(packet_to_send);
  return (true);
}

bool			ProtocolGame::actionGetLevel(PacketData &, User *user, Server &)
{
  PacketData  *to_send = new PacketData;
  ProtocolPacket *packet_to_send;
  // TODO:
  // to_send: [game_name(string)]+
  packet_to_send = PacketFactory::createPacket(THE_GAME, static_cast<ushort>(GETLEVELGAME), to_send);
  user->addPacketToSend(packet_to_send);
  return (true);
}

bool			ProtocolGame::actionCreate(PacketData & received, User *user, Server &)
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
	    << game_lvl << ") max(" << player_max << ") observer("
	    << observer << ")" << std::endl;

  // TODO :
  // verifier si game_name pas deja pris. si game_lvl existe ds le server
  if (player_max < 1 || player_max > 4)
    {
      to_send->addChar(0);
      to_send->addString("Number of Player must be between 1 and 4");
      to_send->prettyPrint();
      packet_to_send = PacketFactory::createPacket(THE_GAME, static_cast<ushort>(CREATEGAME), to_send);
      user->addPacketToSend(packet_to_send);
      return (false);
    }
  // TODO :
  // arrive ici tout est verrifier c'est bon donc on doit creer la game ici
  to_send->addChar(1);
  packet_to_send = PacketFactory::createPacket(THE_GAME, static_cast<ushort>(CREATEGAME), to_send);
  user->addPacketToSend(packet_to_send);
  return (true);
}

bool			ProtocolGame::actionJoin(PacketData & received, User *user, Server &)
{
  PacketData	*to_send = new PacketData;
  ProtocolPacket *packet_to_send;
  std::string	login;
  short		id_game;
  char		observer;

  login = received.getNextString();
  id_game = received.getNextShort();
  observer = received.getNextChar();
  // TODO:
  // verifier si id_game existe et si le logine st dispo pour cette game
  // + si observer != 0: verifier si la game est pas deja full.
  // + si observer == 0: verif si game accept observer
  // to_send: status(char) textinfo()
  to_send->addChar(0);
  to_send->addString("Not Yet Implemented");
  packet_to_send = PacketFactory::createPacket(THE_GAME, static_cast<ushort>(JOINGAME), to_send);
  user->addPacketToSend(packet_to_send);
  return (true);
}

bool			ProtocolGame::actionQuit(PacketData &, User *, Server &)
{
  // TODO:
  // enlever le player de la game.
  // ne renvoi rien
  // BIG TODO: dire au autre clients qu'il se barre (add protocol)
  return (true);
}

// bool			ProtocolGame::actionEnd(PacketData &, User *, Server &)
// {
//   // nothing to do here ;)
//   return (true);
// }

bool			ProtocolGame::actionStart(PacketData &, User *user, Server &)
{
  PacketData	*to_send = new PacketData;
  ProtocolPacket *packet_to_send;

  // TODO:
  // verrifier si le user a bien creer la game (rootgame) et pas quit
  // et si la game est bien en mode lobby(attente dautre personne/chat)
  // si oui -> start game + envoyer packet ok. sinon envoyer packet failure
  packet_to_send = PacketFactory::createPacket(THE_GAME, static_cast<ushort>(STARTGAME), to_send);
  to_send->addChar(0);
  to_send->addString("Not Yet implemented");
  user->addPacketToSend(packet_to_send);
  return (true);
}
