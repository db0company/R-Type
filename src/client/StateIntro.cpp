#include "StateIntro.hpp"
#include "Language.hpp"

extern LibGraphic::Volume gVolume;
extern LibGraphic::Language language;
extern bool errorToPrint;

LibGraphic::StateIntro::StateIntro(std::map<std::string const, GraphicRessource *> const & ressourcesSprite,
				   std::map<std::string const, MyMusic *> const & ressourcesPlayList,
				   std::map<std::string const, MySound *> const & ressourcesSounds,
				   std::map<std::string const, sf::Font *> const & ressourcesFont,
				   sf::RenderWindow & app):
  AState(ressourcesSprite, ressourcesPlayList, ressourcesSounds,
	 ressourcesFont, app)
{
  this->_gameLvl = "Sun";
  this->_nextState = UNKNOWN_STATE;
  this->Clock.Reset();
  this->_frontClock.Reset();
}

LibGraphic::StateIntro::~StateIntro()
{
}

bool LibGraphic::StateIntro::init()
{
  return true;
}

void LibGraphic::StateIntro::draw()
{
  this->drawStarField();
}

void LibGraphic::StateIntro::drawMap()
{
}

void LibGraphic::StateIntro::drawStarField()
{
  static int scale = 0;
  static int scalefront = 0;
  sf::Sprite &b = this->getSprite("Starfield" + this->_gameLvl);
  sf::Sprite &b2 = this->getSprite("Starfield" + this->_gameLvl);
  sf::Sprite &front = this->getSprite("SecondField" + this->_gameLvl);
  sf::Sprite &front2 = this->getSprite("SecondField" + this->_gameLvl);
  float time = this->Clock.GetElapsedTime();
  float timefront = this->_frontClock.GetElapsedTime();

  if (time < 0.05)
    {
      b.SetPosition(0 - scale, 0);
      this->_app.Draw(b);
      b2.SetPosition(1680 - scale, 0);
      this->_app.Draw(b2);
    }
  else
    {
      scale += 1;
      if (scale >= 1680)
	scale = 0;
      b.SetPosition(0 - scale, 0);
      this->_app.Draw(b);
      b2.SetPosition(1680 - scale, 0);
      this->_app.Draw(b2);
      this->Clock.Reset();
    }
  if (timefront < 0.03)
    {
      front.SetPosition(0 - scalefront, 0);
      this->_app.Draw(front);
      front2.SetPosition(1680 - scalefront, 0);
      this->_app.Draw(front2);
    }
  else
    {
      scalefront += 1;
      if (scalefront >= 1680)
	scalefront = 0;
      front.SetPosition(0 - scalefront, 0);
      this->_app.Draw(front);
      front2.SetPosition(1680 - scalefront, 0);
      this->_app.Draw(front2);
      this->_frontClock.Reset();
    }
}

LibGraphic::Event LibGraphic::StateIntro::gereEvent()
{
  sf::Event Event;

  while (this->_app.GetEvent(Event))
    {
      if (Event.Type == sf::Event::KeyPressed)
	{
	  switch (Event.Key.Code)
	    {
	    case sf::Key::Escape :
	      {
		if (errorToPrint)
		  errorToPrint = false;
		else
		  {
		    this->_nextState = START;
		    this->playSound();
		    return EVENT_CHANGE_STATE;
		  }
		break;
	      }
	    case sf::Key::Return :
	      {
		this->_nextState = START;
		this->playSound();
		return EVENT_CHANGE_STATE;
	      }
	    default : break;
	    }
	}
      else if (Event.Type == sf::Event::JoyButtonReleased)
	{
	  switch (Event.JoyButton.Button)
	    {
	    case 1:
	      {
		this->_nextState = START;
		this->playSound();
		return EVENT_CHANGE_STATE;
	      }
	    }
	}
    }
  return EVENT_NONE;
}

LibGraphic::eStates LibGraphic::StateIntro::getNextState()
{
  return this->_nextState;
}

