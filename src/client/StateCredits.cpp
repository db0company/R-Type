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
  this->loadCredits();
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
  sf::Sprite &Button = this->getSprite("BasicButton");

  this->_app.Draw(back);
  Button.SetPosition(1100, 730);
  Button.SetRotation(180);
  // this->_app.Draw(Button);
  // Button.SetRotation(180);

  drawText();
  drawCredits();
}

void LibGraphic::StateCredits::loadCredits()
{
  this->_list.push_back("Project Leading : Bideaux Sofia");
  this->_list.push_back("Threading library : Bideaux Sofia, Sylvain Noelie");
  this->_list.push_back("Dynamic loading library : Bideaux Sofia");

  this->_list.push_back("Game mechanics : Munoz Vincent");
  this->_list.push_back("Project portabilities : Munoz Vincent");
  this->_list.push_back("Dynamic monsters library : Munoz Vincent, Bideaux Sofia");
  this->_list.push_back("Map generator : Munoz Vincent");

  this->_list.push_back("Networking library : Sylvain Noelie");
  this->_list.push_back("Graphic design : Sylvain Noelie, Moutawakil Idriss");
  this->_list.push_back("Networking protocol : Sylvain Noelie");
  this->_list.push_back("Packet design : Lepage Barbara, Sylvain Noelie");
  this->_list.push_back("Protocol documentation : Sylvain Noelie, Munoz Vincent, Lepage Barbara");

  this->_list.push_back("Lead designer : Moutawakil Idriss");
  this->_list.push_back("Graphic rendering : Moutawakil Idriss, Sylvain Noelie");
  this->_list.push_back("Graphic creations : Moutawakil Idriss, Sylvain Noelie, Baradel Audrey");
  this->_list.push_back("General conception : Moutawakil Idriss");

  this->_list.push_back("Special Thanks : Baradel Audrey and the Frattelo's brothers");
}

void LibGraphic::StateCredits::drawCredits()
{
}

void LibGraphic::StateCredits::drawText()
{
  sf::String *tmp;

  if (language == ENGLISH)
    {
      tmp = this->getStdToSfString("Back", this->getFont("StartFontF"));
      tmp->SetPosition(965, 700);
    }
  else
    {
      tmp = this->getStdToSfString("Retour", this->getFont("StartFontF"));
      tmp->SetPosition(945, 700);
    }
  tmp->SetScale(0.6, 0.6);
  tmp->SetColor(sf::Color(255,255,0, 255));
  if (this->_currentButton != BUTTON_CREDITS_BACK)
    tmp->SetColor(sf::Color(255,255,255, 205));
  //  this->_app.Draw(*tmp);
}

LibGraphic::Event LibGraphic::StateCredits::gereEvent()
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
		    this->_app.Close();
		    exit(EXIT_SUCCESS);
		  }
		break;
	      }
	    case sf::Key::Return :
	      {
		this->_nextState = START;
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
