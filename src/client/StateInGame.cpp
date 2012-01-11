#include <iostream>
#include "StateInGame.hpp"
#include "Language.hpp"

extern LibGraphic::Volume gVolume;
extern LibGraphic::Language language;
extern bool errorToPrint;

LibGraphic::StateInGame::StateInGame(std::map<std::string const, GraphicRessource *> const & ressourcesSprite,
						   std::map<std::string const, MyMusic *> const & ressourcesPlayList,
						   std::map<std::string const, MySound *> const & ressourcesSounds,
						   std::map<std::string const, sf::Font *> const & ressourcesFont,
						   sf::RenderWindow & app):
  _ressourcesSprite(ressourcesSprite), _ressourcesPlayList(ressourcesPlayList),
  _ressourcesSounds(ressourcesSounds), _ressourcesFont(ressourcesFont),
  _app(app), _lives(0), _score(0)
{
  this->_nextState = UNKNOWN_STATE;
}

LibGraphic::StateInGame::~StateInGame()
{
}

bool LibGraphic::StateInGame::init()
{
  return true;
}

void LibGraphic::StateInGame::draw()
{
  // sf::Sprite &back = this->getSprite("StartMenuBackground");
  sf::Sprite &back = this->getSprite("Starfield2");
  this->_app.Draw(back);
  this->drawText();
}

void LibGraphic::StateInGame::drawText()
{
}

LibGraphic::Event LibGraphic::StateInGame::gereEvent()
{
  sf::Event Event;

  while (this->_app.GetEvent(Event))
    {
      if (Event.Type == sf::Event::KeyPressed)
	{
	  switch (Event.Key.Code)
	    {
	    case sf::Key::Escape :
	      //return LibGraphic::__EVENT_QUIT;
	      {
		// if (errorToPrint)
		//   errorToPrint = false;
		// else
		//   {
		// this->_app.Close();
		// exit(EXIT_SUCCESS);
		this->_nextState = ROOMLIST;
		return (EVENT_CHANGE_STATE);
		// }
		break;
	      }
	    default : break;
	    }
	}
      if (Event.Type == sf::Event::JoyButtonReleased)
      	{
      	  switch (Event.JoyButton.Button)
      	    {
	    case 0:
      	      {
		break;
      	      }
      	    case 1:
      	      {
		break;
      	      }
      	    default : break;
      	    }
      	}
    }
  return EVENT_NONE;
}

void LibGraphic::StateInGame::readText(const sf::Event & Event)
{
}

LibGraphic::eStates LibGraphic::StateInGame::getNextState()
{
  return this->_nextState;
}

sf::Sprite & LibGraphic::StateInGame::getSprite(std::string const & spriteName) const
{
  return ((*this->_ressourcesSprite.find(spriteName)).second->_sprite);
}

LibGraphic::MyMusic * LibGraphic::StateInGame::getMusic(std::string const & musicName) const
{
  return ((*this->_ressourcesPlayList.find(musicName)).second);
}

sf::Font * LibGraphic::StateInGame::getFont(std::string const & fontName) const
{
  return ((*this->_ressourcesFont.find(fontName)).second);
}

inline sf::String * LibGraphic::StateInGame::getStdToSfString(std::string const & s, sf::Font * daFont)
{
  return (new sf::String(s, *daFont));
}

RecupMap &LibGraphic::StateInGame::getRecupMap(void)
{
  return (this->_rMap);
}

std::string const &LibGraphic::StateInGame::getInGameName(void) const
{
  return (this->_gameName);
}

std::string const &LibGraphic::StateInGame::getGameLvl(void) const
{
  return (this->_gameLvl);
}

void LibGraphic::StateInGame::setGameName(std::string const &s)
{
  this->_gameName = s;
}

void LibGraphic::StateInGame::setGameLvl(std::string const &s)
{
  this->_gameLvl = s;
}
