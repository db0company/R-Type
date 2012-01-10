#include <list>
#include <string>
#include <iostream>
#include "GameParameter.hpp"
#include "ProtocolGame.hpp"
#include "Client.hpp"
#include "InfoGame.hpp"

ProtocolGame::ProtocolGame()
{
  this->actionmap[GAME_ERROR] = &ProtocolGame::actionError;
  this->actionmap[GETGAME] = &ProtocolGame::actionGet;
  this->actionmap[GETLEVELGAME] = &ProtocolGame::actionGetLevel;
  this->actionmap[CREATEGAME] = &ProtocolGame::actionCreate;
  this->actionmap[JOINGAME] = &ProtocolGame::actionJoin;
  this->actionmap[QUITGAME] = &ProtocolGame::actionQuit;
  this->actionmap[ENDGAME] = &ProtocolGame::actionEnd;
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

bool			ProtocolGame::action(ushort instruction,
					     PacketData & data, Client &client)
{
  std::map<eProtocolPacketGame, ptr_func>::iterator it;
  ptr_func		ptr;

  if (instruction >= GAME_MAX)
    (void)this->actionError(data, client);
  if ((it = this->actionmap.find(static_cast<eProtocolPacketGame>(instruction))) == this->actionmap.end())
    {
      (void)this->actionError(data, client);
      return false;
    }
  ptr = it->second;
  return ((this->*ptr)(data, client));
}

bool			ProtocolGame::actionError(PacketData &, Client &)
{
  return (false);
}

bool			ProtocolGame::actionGet(PacketData & data, Client &client)
{
  short nb_game = 0;
  short i;
  int id;
  std::string owner;
  std::string name;
  std::string lvl;
  char slot;
  char observer;
  std::map<int, InfoGame *> &rmap = client.getGraphic().getInfoGameMap();
  std::map<int, InfoGame *>::iterator it;
  InfoGame *newGame;
  char nb_player;

  i = 0;
  nb_game = data.getNextShort();
  if (!nb_game)
    return (false);
  while (i < nb_game)
    {
      id = data.getNextShort();
      owner = data.getNextString();
      name = data.getNextString();
      lvl = data.getNextString();
      slot = data.getNextChar();
      observer = data.getNextChar();
      nb_player = data.getNextChar();
      if ((it = rmap.find(id)) == rmap.end())
      	{
      	  newGame = new InfoGame;

      	  newGame->setId(id);
      	  newGame->setOwner(owner);
      	  newGame->setName(name);
      	  newGame->setMap(lvl);
      	  newGame->setObs(observer);
      	  newGame->setPlayers(nb_player);
      	  newGame->setPlayerMax(slot);
      	  rmap[id] = newGame;
      	}
      else
      	{
      	  newGame = it->second;
      	  newGame->setId(id);
      	  newGame->setOwner(owner);
      	  newGame->setName(name);
      	  newGame->setMap(lvl);
      	  newGame->setObs(observer);
      	  newGame->setPlayers(nb_player);
      	  newGame->setPlayerMax(slot);
      	}
      ++i;
    }
  return (false);
}

bool			ProtocolGame::actionGetLevel(PacketData & data, Client &client)
{
  std::string lvl;
  short nb;
  short i;
  std::list<std::string>&list = client.getGraphic().getLvlList();
  std::list<std::string>::iterator it;
  bool exist = false;

  i = 0;
  nb = data.getNextShort();
  while (i < nb)
    {
      lvl = data.getNextString();
      exist = false;
      for (it = list.begin(); it != list.end(); ++it)
	{
	  if (*it == lvl)
	    exist = true;
	}
      if (!exist)
	list.push_front(lvl);
      ++i;
    }
  return (false);
}

bool			ProtocolGame::actionCreate(PacketData & data, Client &client)
{
  char			status;
  std::string		details;

  status = data.getNextChar();
  details = data.getNextString();
  std::cout << "status(" << (int)status << ") details(" << details << ")" << std::endl;
 if (status)
    {
      client.getGraphic().setCurrentState(LibGraphic::ROOM);
      return (true);
    }
  else
    {
      client.getGraphic().errorMessage("Error From Server. " + details + "\n");
    }
  return (false);
}

bool			ProtocolGame::actionJoin(PacketData & data, Client &client)
{
  char			status;
  std::string		details;

  status = data.getNextChar();
  details = data.getNextString();
  std::cout << "status(" << (int)status << ") details(" << details << ")" << std::endl;
  if (status)
    {
      client.getGraphic().setCurrentState(LibGraphic::ROOM);
    }
  else
    {
      client.getGraphic().errorMessage("Error From Server. " + details + "\n");
    }
  return (false);
}

bool			ProtocolGame::actionEnd(PacketData &, Client &)
{
  // TODO: la game est fini. clean memoire + go ecran de fin (puis game list)
  return (false);
}

bool			ProtocolGame::actionStart(PacketData & data, Client &client)
{
  char			status;
  std::string		details;

  status = data.getNextChar();
  details = data.getNextString();
  std::cout << "status(" << (int)status << ") details(" << details << ")" << std::endl;
  if (status)
    {
      client.getGraphic().setCurrentState(LibGraphic::INGAME);
      // client.getGraphic().errorMessage("la game peut commencer... todo didi :)");
    }
  else
    {
      client.getGraphic().errorMessage("Error From Server. " + details + "\n");
    }
  return (false);
}

bool			ProtocolGame::actionQuit(PacketData & data, Client &client)
{
  std::string	log;
  int		quit;

  quit = data.getNextShort();
  log = data.getNextString();
  if (quit)
    {
      client.getGraphic().errorMessage("The Creator "+ log +" deleted this game" + "\n");
      client.getGraphic().setCurrentState(LibGraphic::ROOMLIST);
    }
  else
    {
      // un mec a quit. what u wanna do 'bout it ?
    }
  return (false);
}
