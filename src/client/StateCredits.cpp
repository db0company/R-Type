#include "StateCredits.hpp"

#include "Language.hpp"

extern LibGraphic::Volume gVolume;
extern LibGraphic::Language language;
extern bool errorToPrint;

LibGraphic::StateCredits::StateCredits(std::map<std::string const, GraphicRessource *> const & ressourcesSprite,
				       std::map<std::string const, MyMusic *> const & ressourcesPlayList,
				       std::map<std::string const, MySound *> const & ressourcesSounds,
				       std::map<std::string const, sf::Font *> const & ressourcesFont,
				       sf::RenderWindow & app):
  AState(ressourcesSprite, ressourcesPlayList, ressourcesSounds,
	 ressourcesFont, app)
{
  this->_currentButton = BUTTON_CREDITS_BACK;
  this->_nextState = START;
  this->Clock.Reset();
  this->loadCredits();
  this->_end = false;
}

LibGraphic::StateCredits::~StateCredits()
{
}

bool LibGraphic::StateCredits::init()
{
  return true;
}

void LibGraphic::StateCredits::draw()
{
  sf::Sprite &back = this->getSprite("StartMenuBackground");

  this->_app.Draw(back);

  drawText();
  drawCredits();
}

void LibGraphic::StateCredits::loadCredits()
{
  this->_list.push_back(new credit("Project Leading : Bideaux Sofia", 1050));
  this->_list.push_back(new credit("Threading library : Bideaux Sofia, Sylvain Noelie", 1100));
  this->_list.push_back(new credit("Dynamic loading library : Bideaux Sofia", 1150));
  this->_list.push_back(new credit("Game mechanics : Munoz Vincent", 1200));
  this->_list.push_back(new credit("Project portabilities : Munoz Vincent", 1250));
  this->_list.push_back(new credit("Dynamic monsters library : Munoz Vincent, Bideaux Sofia", 1300));
  this->_list.push_back(new credit("Map generator : Munoz Vincent", 1350));
  this->_list.push_back(new credit("Networking library : Sylvain Noelie", 1400));
  this->_list.push_back(new credit("Graphic design : Sylvain Noelie, Moutawakil Idriss", 1450));
  this->_list.push_back(new credit("Networking protocol : Sylvain Noelie", 1500));
  this->_list.push_back(new credit("Packet design : Lepage Barbara, Sylvain Noelie", 1550));
  this->_list.push_back(new credit("Protocol documentation : Sylvain Noelie, Munoz Vincent, Lepage Barbara", 1600));
  this->_list.push_back(new credit("Lead designer : Moutawakil Idriss", 1650));
  this->_list.push_back(new credit("Graphic rendering : Moutawakil Idriss, Sylvain Noelie", 1700));
  this->_list.push_back(new credit("Graphic creations : Moutawakil Idriss, Sylvain Noelie, Baradel Audrey", 1750));
  this->_list.push_back(new credit("General conception : Moutawakil Idriss", 1800));
  this->_list.push_back(new credit("Special Thanks : Baradel Audrey", 1850));
}

void LibGraphic::StateCredits::drawCredits()
{
}

void LibGraphic::StateCredits::drawText()
{
  std::list<credit *>::const_iterator it;
  sf::String *tmp;
  unsigned int test = 1;

  if (this->Clock.GetElapsedTime() < 0.01)
    return;
  for (it = this->_list.begin(); it != this->_list.end(); ++it)
    {
      tmp = this->getStdToSfString((*it)->s ,this->getFont("StartFontF"));
      tmp->SetPosition(200, (*it)->pos);
      tmp->SetScale(0.8, 0.8);
      (*it)->pos -= 1;
      test = (*it)->pos;
      this->_app.Draw(*tmp);
    }
  this->Clock.Reset();
  if (test <= 0)
    this->_end = true;
}

LibGraphic::Event LibGraphic::StateCredits::gereEvent()
{
  sf::Event Event;

  if (this->_end)
    {
      this->_end = false;
      this->_list.clear();
      this->loadCredits();
      this->_nextState = START;
      return EVENT_CHANGE_STATE;
    }
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
		    this->_end = false;
		    this->_list.clear();
		    this->loadCredits();
 		    this->_nextState = START;
		    this->playSound();
		    return EVENT_CHANGE_STATE;
		  }
		break;
	      }
	    case sf::Key::Return :
	      {
		this->_end = false;
		this->_list.clear();
		this->loadCredits();
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
		this->_end = false;
		this->_list.clear();
		this->loadCredits();
		this->_nextState = START;
		this->playSound();
		return EVENT_CHANGE_STATE;
	      }
	    }
	}
    }
  return EVENT_NONE;
}

LibGraphic::eStates LibGraphic::StateCredits::getNextState()
{
  return this->_nextState;
}
