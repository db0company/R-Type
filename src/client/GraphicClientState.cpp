//#include <Rect.hpp>
#include <iostream>
#include <sstream>
//#include "Istate.hpp"
#include "StateStart.hpp"
#include "StateOptions.hpp"
#include "StateCreateGame.hpp"
#include "StateRoomList.hpp"
#include "StateRoom.hpp"
#include "GraphicClientState.hpp"
#include "EGraphicAction.hpp"

using namespace LibGraphic;

static IState const* getValue(std::map<eStates, IState*> const& m, eStates const& key)
{
  std::map<eStates, IState*>::const_iterator it;
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
  this->_stateInfos[CREDITS] = NULL;
  this->_stateInfos[RANKING] = NULL;
  this->_stateInfos[INTRO] = NULL;
  this->_stateInfos[INGAME] = NULL;
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

eGraphicAction LibGraphic::GraphicClientState::getAction(eStates scene)
{
  return this->_stateInfos[scene]->getAction();
}

std::string const & LibGraphic::GraphicClientState::getIp() const
{
  return reinterpret_cast <StateOptions const *>(getValue(this->_stateInfos,OPTIONS))->getIp();
}

std::string const & LibGraphic::GraphicClientState::getName() const
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
  return -1;
}

std::string const & LibGraphic::GraphicClientState::getLevel() const
{
  std::string * toto = new std::string("bite");
  return *toto;
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

void LibGraphic::GraphicClientState::setAction(eGraphicAction eAction, eStates scene)
{
  return this->_stateInfos[scene]->setAction(eAction);
}

void LibGraphic::GraphicClientState::setNextState(eStates current, eStates next)
{
  this->_stateInfos[current]->setNextState(next);
}
