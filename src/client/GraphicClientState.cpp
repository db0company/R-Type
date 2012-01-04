//#include <Rect.hpp>
#include <iostream>
#include "StateStart.hpp"
#include "StateOptions.hpp"
#include "StateJoinCreate.hpp"
#include "StateRoomList.hpp"
#include "StateRoom.hpp"
#include "GraphicClientState.hpp"

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
  this->_stateInfos[GAMEPARAMETER] = NULL;
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
