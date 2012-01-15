//#include <Rect.hpp>
#include <iostream>
#include <sstream>
#include <list>
#include <string>
//#include "Istate.hpp"
#include "StateStart.hpp"
#include "StateOptions.hpp"
#include "StateCreateGame.hpp"
#include "StateRoomList.hpp"
#include "StateRoom.hpp"
#include "StateInGame.hpp"
#include "StateRanking.hpp"
#include "StateCredits.hpp"
#include "GraphicClientState.hpp"
#include "EGraphicAction.hpp"
#include "PlayerMovement.hpp"
#include "AMonsterMovement.hpp"
#include "SpriteInfo.hpp"

using namespace LibGraphic;

static AState const* getValue(std::map<eStates, AState*> const& m, eStates const& key)
{
  std::map<eStates, AState*>::const_iterator it;
  it = m.find(key);
  if (it == m.end())
    return 0;
  return it->second;
}

static AState * getValue(std::map<eStates, AState*> & m, eStates const& key)
{
  std::map<eStates, AState*>::iterator it;
  it = m.find(key);
  if (it == m.end())
    return 0;
  return it->second;
}

LibGraphic::GraphicClientState::GraphicClientState(std::map<std::string const, GraphicRessource *> const & ressourcesSprite,
						   std::map<std::string const, MyMusic *> const & ressourcesPlayList,
						   std::map<std::string const, MySound *> const & ressourcesSounds,
						   std::map<std::string const, sf::Font *> const & ressourcesFont,
						   sf::RenderWindow & app):
  _ressourcesSprite(ressourcesSprite), _ressourcesPlayList(ressourcesPlayList),
  _ressourcesSounds(ressourcesSounds), _ressourcesFont(ressourcesFont),
  _app(app)
{
  loadStates();
}

void LibGraphic::GraphicClientState::loadStates(void)
{
  this->_stateInfos[START] = new StateStart(this->_ressourcesSprite,
					    this->_ressourcesPlayList,
					    this->_ressourcesSounds,
					    this->_ressourcesFont,
					    this->_app);

  this->_stateInfos[ROOMLIST] = new StateRoomList(this->_ressourcesSprite,
						  this->_ressourcesPlayList,
						  this->_ressourcesSounds,
						  this->_ressourcesFont,
						  this->_app);

  this->_stateInfos[CREATEGAME] = new StateCreateGame(this->_ressourcesSprite,
						      this->_ressourcesPlayList,
						      this->_ressourcesSounds,
						      this->_ressourcesFont,
						      this->_app);

  this->_stateInfos[ROOM] = new StateRoom(this->_ressourcesSprite,
					  this->_ressourcesPlayList,
					  this->_ressourcesSounds,
					  this->_ressourcesFont,
					  this->_app);

  this->_stateInfos[OPTIONS] = new StateOptions(this->_ressourcesSprite,
						this->_ressourcesPlayList,
						this->_ressourcesSounds,
						this->_ressourcesFont,
						this->_app);

  this->_stateInfos[CREDITS] = new StateCredits(this->_ressourcesSprite,
						this->_ressourcesPlayList,
						this->_ressourcesSounds,
						this->_ressourcesFont,
						this->_app);

  this->_stateInfos[RANKING] = new StateRanking(this->_ressourcesSprite,
						this->_ressourcesPlayList,
						this->_ressourcesSounds,
						this->_ressourcesFont,
						this->_app);
  this->_stateInfos[INTRO] = NULL;
  this->_stateInfos[INGAME] = new StateInGame(this->_ressourcesSprite,
					      this->_ressourcesPlayList,
					      this->_ressourcesSounds,
					      this->_ressourcesFont,
					      this->_app);
  this->_stateInfos[UNKNOWN_STATE] = NULL;
}

LibGraphic::GraphicClientState::~GraphicClientState(void)
{
}

LibGraphic::eStates LibGraphic::GraphicClientState::goToNextState(eStates scene)
{
  return this->_stateInfos[scene]->getNextState();
}

void LibGraphic::GraphicClientState::draw(eStates scene)
{
  this->_stateInfos[scene]->draw();
}

LibGraphic::Event LibGraphic::GraphicClientState::getEventFromState(eStates scene)
{
  return this->_stateInfos[scene]->gereEvent();
}

std::string const & LibGraphic::GraphicClientState::getIp() const
{
  return reinterpret_cast <StateOptions const *>(getValue(this->_stateInfos,OPTIONS))->getIp();
}

std::string const & LibGraphic::GraphicClientState::getLogin() const
{
  return reinterpret_cast <StateOptions const *>(getValue(this->_stateInfos,OPTIONS))->getName();
}

int LibGraphic::GraphicClientState::getPort()
{
  int port;
  std::stringstream ss;

  ss << reinterpret_cast <StateOptions const *>(getValue(this->_stateInfos, OPTIONS))->getPort();
  ss >> port;
  return port;
}

int LibGraphic::GraphicClientState::getIdGame() const
{
  return reinterpret_cast <StateRoomList const *>(getValue(this->_stateInfos, ROOMLIST))->getIdGame();
}

std::string const & LibGraphic::GraphicClientState::getLevel() const
{
  return reinterpret_cast <StateCreateGame const *>(getValue(this->_stateInfos, CREATEGAME))->getLevel();
}

int LibGraphic::GraphicClientState::getSlot() const
{
  return reinterpret_cast <StateCreateGame const *>(getValue(this->_stateInfos, CREATEGAME))->getSlot();
}

bool LibGraphic::GraphicClientState::getSpectator() const
{
  return reinterpret_cast <StateCreateGame const *>(getValue(this->_stateInfos, CREATEGAME))->getSpectator();
}

std::string const & LibGraphic::GraphicClientState::getGameName() const
{
  return reinterpret_cast <StateCreateGame const *>(getValue(this->_stateInfos, CREATEGAME))->getGameName();
}

std::string const & LibGraphic::GraphicClientState::getMessage() const
{
  return reinterpret_cast <StateRoom const *>(getValue(this->_stateInfos, ROOM))->getMessage();
}

void LibGraphic::GraphicClientState::setMessage(std::string const &m)
{
  reinterpret_cast <StateRoom *>(getValue(this->_stateInfos, ROOM))->setMessage(m);
}

std::string const & LibGraphic::GraphicClientState::getConversation() const
{
  return reinterpret_cast <StateRoom const *>(getValue(this->_stateInfos, ROOM))->getConversation();
}

void LibGraphic::GraphicClientState::addToConversation(std::string const & m)
{
  reinterpret_cast <StateRoom *>(getValue(this->_stateInfos, ROOM))->addToConversation(m);
}

std::map<int, InfoGame *> & LibGraphic::GraphicClientState::getInfoGameMap(void)
{
  return reinterpret_cast <StateRoomList *>(getValue(this->_stateInfos, ROOMLIST))->getInfoGameMap();
}

void LibGraphic::GraphicClientState::setInfoGameMap(std::map<int, InfoGame *> &nmap)
{
  reinterpret_cast <StateRoomList *>(getValue(this->_stateInfos, ROOMLIST))->setInfoGameMap(nmap);
}

std::list<std::string > &LibGraphic::GraphicClientState::getLvlList(void)
{
  return reinterpret_cast <StateCreateGame *>(getValue(this->_stateInfos, CREATEGAME))->getLvlList();
}

RecupMap &LibGraphic::GraphicClientState::getRecupMap(void)
{
  return reinterpret_cast <StateInGame *> (getValue(this->_stateInfos, INGAME))->getRecupMap();
}

//
std::string const &LibGraphic::GraphicClientState::getInGameName(void) const
{
  return reinterpret_cast <StateInGame const *> (getValue(this->_stateInfos, INGAME))->getInGameName();
}

std::string const &LibGraphic::GraphicClientState::getGameLvl(void) const
{
  return reinterpret_cast <StateInGame const *> (getValue(this->_stateInfos, INGAME))->getGameLvl();
}

void LibGraphic::GraphicClientState::setGameName(std::string const &s)
{
  reinterpret_cast <StateInGame *>(getValue(this->_stateInfos, INGAME))->setGameName(s);
}

void LibGraphic::GraphicClientState::setGameLvl(std::string const &s)
{
  reinterpret_cast <StateInGame *>(getValue(this->_stateInfos, INGAME))->setGameLvl(s);
}

void LibGraphic::GraphicClientState::setGameForPreview(InfoGame *g)
{
  reinterpret_cast <StateRoom *>(getValue(this->_stateInfos, ROOM))->setGameForPreview(g);
}

InfoGame * LibGraphic::GraphicClientState::getGameForPreviewFromRoomlist(void)
{
  return reinterpret_cast <StateRoomList *>(getValue(this->_stateInfos, ROOMLIST))->getGamePreview();
}

InfoGame * LibGraphic::GraphicClientState::getGameForPreviewFromCreate(void)
{
  return reinterpret_cast <StateCreateGame *>(getValue(this->_stateInfos, CREATEGAME))->getGamePreview();
}

std::list<std::string> &LibGraphic::GraphicClientState::getPlayerNameList(void)
{
  return reinterpret_cast <StateRoom *>(getValue(this->_stateInfos, ROOM))->getPlayerNameList();
}

LibGraphic::eMovement LibGraphic::GraphicClientState::getLastMove() const
{
  return reinterpret_cast <StateInGame const *>(getValue(this->_stateInfos, INGAME))->getLastMove();
}

// std::map<int, LibGraphic::PlayerMovement *> const & LibGraphic::GraphicClientState::getPlayerMap() const
// {
//   return reinterpret_cast <StateInGame const *>(getValue(this->_stateInfos, INGAME))->getPlayerMap();
// }

std::map<int, PlayerMovement *> & LibGraphic::GraphicClientState::getPlayerMap()
{
  return reinterpret_cast <StateInGame *>(getValue(this->_stateInfos, INGAME))->getPlayerMap();
}

std::map<int, AMonsterMovement *> & LibGraphic::GraphicClientState::getMonsterMap()
{
  return reinterpret_cast <StateInGame *>(getValue(this->_stateInfos, INGAME))->getMonsterMap();
}

std::list<BulletMovement *> & LibGraphic::GraphicClientState::getBulletList()
{
  return reinterpret_cast <StateInGame *>(getValue(this->_stateInfos, INGAME))->getBulletList();
}

eShipColor LibGraphic::GraphicClientState::getMyId() const
{
  return reinterpret_cast <StateInGame const *>(getValue(this->_stateInfos, INGAME))->getMyId();
}

void LibGraphic::GraphicClientState::setMyId(eShipColor id)
{
  reinterpret_cast <StateInGame *>(getValue(this->_stateInfos, INGAME))->setMyId(id);
}

void LibGraphic::GraphicClientState::setMyPosition(Coord c)
{
  reinterpret_cast <StateInGame *>(getValue(this->_stateInfos, INGAME))->setMyPosition(c);
}

LibGraphic::eBulletType LibGraphic::GraphicClientState::getLastBullet(void)const
{
  return reinterpret_cast <StateInGame const *>(getValue(this->_stateInfos, INGAME))->getLastBullet();
}

void LibGraphic::GraphicClientState::resetInGameState()
{
  reinterpret_cast <StateInGame *>(getValue(this->_stateInfos, INGAME))->resetInGameState();
}

void LibGraphic::GraphicClientState::resetRoomListState()
{
  reinterpret_cast <StateRoomList *>(getValue(this->_stateInfos, ROOMLIST))->resetRoomListState();
}

void LibGraphic::GraphicClientState::setScore(unsigned int i)
{
  reinterpret_cast <StateInGame *>(getValue(this->_stateInfos, INGAME))->setScore(i);
}

void LibGraphic::GraphicClientState::setLives(unsigned int lives)
{
  reinterpret_cast <StateInGame *>(getValue(this->_stateInfos, INGAME))->setLives(lives);
}

std::list<std::string> &LibGraphic::GraphicClientState::getRankingList()
{
  return reinterpret_cast <StateRanking *>(getValue(this->_stateInfos, RANKING))->getRankingList();
}
