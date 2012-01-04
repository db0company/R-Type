#include	"GameParameter.hpp"
#include	"ProtocolGame.hpp"

ProtocolGame::ProtocolGame()
{
  this->actionmap[GAME_ERROR] = &ProtocolGame::actionError;
  this->actionmap[GETGAME] = &ProtocolGame::actionGet;
  this->actionmap[GETLEVELGAME] = &ProtocolGame::actionGetLevel;
  this->actionmap[CREATEGAME] = &ProtocolGame::actionCreate;
  this->actionmap[JOINGAME] = &ProtocolGame::actionJoin;
  this->actionmap[QUITGAME] = &ProtocolGame::actionError;
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

void			ProtocolGame::action(ushort instruction,
					     PacketData & data, Client &client)
{
  std::map<eProtocolPacketGame, ptr_func>::iterator it;
  ptr_func		ptr;

  if (instruction >= GAME_MAX)
    (void)this->actionError(data, client);
  if ((it = this->actionmap.find(static_cast<eProtocolPacketGame>(instruction))) == this->actionmap.end())
    {
      (void)this->actionError(data, client);
      return ;
    }
  ptr = it->second;
  (this->*ptr)(data, client);
}

bool			ProtocolGame::actionError(PacketData &, Client &)
{
  return (true);
}

bool			ProtocolGame::actionGet(PacketData & data, Client &)
{
  short nb_game = 0;
  short i;
  GameParameter *gameParam = new GameParameter;

  i = 0;
  nb_game = data.getNextShort();
  if (!nb_game)
    return (false);
  while (i < nb_game)
    {
      gameParam->id = data.getNextShort();
      gameParam->owner = data.getNextString();
      gameParam->name = data.getNextString();
      gameParam->lvl = data.getNextString();
      gameParam->slot = data.getNextChar();
      //gameParam->observer = data.getNextChar();
      gameParam->nb_player = data.getNextChar();
      // TODO: verif toutes les donnees sont ok puis ajouter a la
      // map des games du client
      // pour lafficher dans le Game list.
      // truc du genre:
      // client->addNewGame(gameParam);
      ++i;
    }
  return (true);
}

bool			ProtocolGame::actionGetLevel(PacketData & data, Client &)
{
  (void)data;
    return (true);
}

bool			ProtocolGame::actionCreate(PacketData & data, Client &)
{
  char			status;
  std::string		details;

  status = data.getNextChar();
  details = data.getNextString();
  if (status)
    {
      // TODO la creation de la game a reussi
      //  -> on passe en affichage room (join ?)
    }
  else
    {
      // TODO creation fail. popup error
    }
  return (true);
}

bool			ProtocolGame::actionJoin(PacketData & data, Client &)
{
  char			status;
  std::string		details;

  status = data.getNextChar();
  details = data.getNextString();
  if (status)
    {
      // TODO join de la game a reussi
      // -> on passe en affichage room
    }
  else
    {
      // TODO join fail. popup error
    }
  return (true);
}

// bool			ProtocolGame::actionQuit(PacketData & data, Client &)
// {
//   (void)data;
//   return (true);
// }

bool			ProtocolGame::actionEnd(PacketData &, Client &)
{
  // TODO: la game est fini. clean memoire + go ecran de fin (puis game list)
  return (true);
}

bool			ProtocolGame::actionStart(PacketData & data, Client &)
{
  char			status;
  std::string		details;

  status = data.getNextChar();
  details = data.getNextString();
  if (status)
    {
      // Todo
    }
  else
    {
      // Todo
    }
  return (true);
  (void)data;
  return (true);
}
