#include <iostream>
#include "StateStart.hpp"
#include "Language.hpp"

extern LibGraphic::Language language;
extern bool errorToPrint;
extern bool helpToShow;

LibGraphic::StateStart::StateStart(std::map<std::string const, GraphicRessource *> const & ressourcesSprite,
						   std::map<std::string const, MyMusic *> const & ressourcesPlayList,
						   std::map<std::string const, MySound *> const & ressourcesSounds,
						   std::map<std::string const, sf::Font *> const & ressourcesFont,
						   sf::RenderWindow & app):
  AState(ressourcesSprite, ressourcesPlayList, ressourcesSounds, ressourcesFont, app)
{
  this->_currentButton = BUTTON_PLAY;
  this->_nextState = UNKNOWN_STATE;
}

LibGraphic::StateStart::~StateStart()
{
}

bool LibGraphic::StateStart::init()
{
  return true;
}

void LibGraphic::StateStart::draw()
{
  sf::String *tmp;
  sf::Sprite &back = this->getSprite("StartMenuBackground");
  sf::Sprite &menu = this->getSprite("StartMenu");
  int x = 170;
  int y = 300;

  menu.SetPosition(250 + x, 350 + y);
  this->_app.Draw(back);
  menu.SetColor(sf::Color(255, 255, 255, 230));

  switch (this->_currentButton)
    {
    case BUTTON_PLAY :
      {
	menu.SetSubRect(sf::IntRect(841, 311, 841 * 2, 311 * 2));
	this->_app.Draw(menu);
	menu.SetColor(sf::Color(255, 255, 255, 150));
	menu.SetSubRect(sf::IntRect(0, 311, 841, 311 * 2));
	this->drawText();
	this->_app.Draw(menu);
	if (language == ENGLISH)
	  tmp = this->getStdToSfString("PLAY", this->getFont("StartFontF"));
	else
	  tmp = this->getStdToSfString("JOUER", this->getFont("StartFontF"));
	tmp->SetPosition(320 + x, 455 + y);
	tmp->Scale(2.3, 2.3);
	tmp->SetColor(sf::Color(255,255,255, 220));
	this->_app.Draw(*tmp);
	break;
      }
    case BUTTON_OPTIONS :
      {
	menu.SetSubRect(sf::IntRect(841, 311 * 4, 841 * 2, 311 * 5));
	this->_app.Draw(menu);
	menu.SetColor(sf::Color(255, 255, 255, 150));
	menu.SetSubRect(sf::IntRect(0, 311 * 4, 841, 311 * 5));
	this->drawText();
	this->_app.Draw(menu);
	tmp = this->getStdToSfString("OPTIONS", this->getFont("StartFontF"));
	tmp->SetPosition(740 + x, 462 + y);
	tmp->Scale(1.7, 2.2);
	tmp->SetColor(sf::Color(255,255,255, 220));
	this->_app.Draw(*tmp);
	break;
      }
    case BUTTON_CREDITS :
      {
	menu.SetSubRect(sf::IntRect(841, 311 * 2, 841 * 2, 311 * 3));
	this->_app.Draw(menu);
	menu.SetColor(sf::Color(255, 255, 255, 150));
	menu.SetSubRect(sf::IntRect(0, 311 * 2, 841, 311 * 3));
	this->drawText();
	this->_app.Draw(menu);
	tmp = this->getStdToSfString("CREDITS", this->getFont("StartFontF"));
	tmp->SetPosition(440 + x, 595 + y);
	tmp->SetColor(sf::Color(255,255,255, 220));
	this->_app.Draw(*tmp);
	break;
      }
    case BUTTON_EXIT :
      {
	menu.SetSubRect(sf::IntRect(841, 311 * 5, 841 * 2, 311 * 6));
	this->_app.Draw(menu);
	menu.SetColor(sf::Color(255, 255, 255, 150));
	menu.SetSubRect(sf::IntRect(0, 311 * 5, 841, 311 * 6));
	this->drawText();
	this->_app.Draw(menu);
	if (language == ENGLISH)
	  {
	    tmp = this->getStdToSfString("EXIT", this->getFont("StartFontF"));
	    tmp->SetPosition(810 + x, 595 + y);
	  }
	else
	  {
	    tmp = this->getStdToSfString("SORTIR", this->getFont("StartFontF"));
	    tmp->SetPosition(810 + x - 60, 595 + y);
	  }
	tmp->SetColor(sf::Color(255,255,255, 220));
	this->_app.Draw(*tmp);
	break;
      }
    case BUTTON_INTRO :
      {
	menu.SetSubRect(sf::IntRect(841, 0, 841 * 2, 311));
	this->_app.Draw(menu);
	menu.SetColor(sf::Color(255, 255, 255, 150));
	menu.SetSubRect(sf::IntRect(0, 0, 841, 311));
	this->drawText();
	this->_app.Draw(menu);
	tmp = this->getStdToSfString("INTRO", this->getFont("StartFontF"));
	tmp->SetPosition(440 + x, 375 + y);
	tmp->SetColor(sf::Color(255,255,255, 220));
	this->_app.Draw(*tmp);
	break;
      }
    case BUTTON_RANKING :
      {
	menu.SetSubRect(sf::IntRect(841, 311 * 3, 841 * 2, 311 * 4));
	this->_app.Draw(menu);
	menu.SetColor(sf::Color(255, 255, 255, 150));
	menu.SetSubRect(sf::IntRect(0, 311 * 3 , 841, 311 * 4));
	this->drawText();
	this->_app.Draw(menu);
	if (language == ENGLISH)
	  {
	    tmp = this->getStdToSfString("RANKING", this->getFont("StartFontF"));
	    tmp->SetPosition(725 + x, 375 + y);
	  }
	else
	  {
	    tmp = this->getStdToSfString("CLASSEMENT", this->getFont("StartFontF"));
	    tmp->SetPosition(725 + x - 60, 375 + y);
	  }
	tmp->SetColor(sf::Color(255,255,255, 220));
	this->_app.Draw(*tmp);
	break;
      }
    }

  MyMusic * song = this->getMusic("StartMusic");
  if (song->GetMusicState() == sf::Music::Stopped ||
      song->GetMusicState() == sf::Music::Paused)
    song->PlayMusic();
}

void LibGraphic::StateStart::drawText()
{
  sf::String *tmp;
  int x = 170;
  int y = 300;

  if (this->_currentButton == BUTTON_PLAY)
    {
      if (language == ENGLISH)
	tmp = this->getStdToSfString("PLAY", this->getFont("StartFontF"));
      else
	tmp = this->getStdToSfString("JOUER", this->getFont("StartFontF"));
    }
  else
    {
      if (language == ENGLISH)
	tmp = this->getStdToSfString("PLAY", this->getFont("StartFontE"));
      else
	tmp = this->getStdToSfString("JOUER", this->getFont("StartFontE"));
    }
  tmp->SetColor(sf::Color(255,255,255, 255));
  tmp->SetPosition(320 + x, 455 + y);
  tmp->Scale(2.3, 2.3);
  this->_app.Draw(*tmp);

  if (this->_currentButton == BUTTON_OPTIONS)
    tmp = this->getStdToSfString("OPTIONS", this->getFont("StartFontF"));
  else
    tmp = this->getStdToSfString("OPTIONS", this->getFont("StartFontE"));
  tmp->SetColor(sf::Color(255,255,255, 255));
  tmp->SetPosition(740 + x, 462 + y);
  tmp->Scale(1.7, 2.2);
  this->_app.Draw(*tmp);

  if (this->_currentButton == BUTTON_CREDITS)
    tmp = this->getStdToSfString("CREDITS", this->getFont("StartFontF"));
  else
    tmp = this->getStdToSfString("CREDITS", this->getFont("StartFontE"));
  tmp->SetColor(sf::Color(255,255,255, 255));
  tmp->SetPosition(440 + x, 595 + y);
  this->_app.Draw(*tmp);

  if (this->_currentButton == BUTTON_EXIT)
    {
      if (language == ENGLISH)
	{
	  tmp = this->getStdToSfString("EXIT", this->getFont("StartFontF"));
	  tmp->SetPosition(810 + x, 595 + y);
	}
      else
	{
	  tmp = this->getStdToSfString("SORTIR", this->getFont("StartFontF"));
	  tmp->SetPosition(810 + x - 60, 595 + y);
	}
    }
  else
    {
      if (language == ENGLISH)
	{
	  tmp = this->getStdToSfString("EXIT", this->getFont("StartFontE"));
	  tmp->SetPosition(810 + x, 595 + y);
	}
      else
	{
	  tmp = this->getStdToSfString("SORTIR", this->getFont("StartFontE"));
	  tmp->SetPosition(810 + x - 60, 595 + y);
	}
    }
  tmp->SetColor(sf::Color(255,255,255, 255));
  //  tmp->SetPosition(810 + x, 595 + y);
  this->_app.Draw(*tmp);

  if (this->_currentButton == BUTTON_INTRO)
    tmp = this->getStdToSfString("INTRO", this->getFont("StartFontF"));
  else
    tmp = this->getStdToSfString("INTRO", this->getFont("StartFontE"));
  tmp->SetColor(sf::Color(255,255,255, 255));
  tmp->SetPosition(440 + x, 375 + y);
  this->_app.Draw(*tmp);

  if (this->_currentButton == BUTTON_RANKING)
    {
      if (language == ENGLISH)
	{
	  tmp = this->getStdToSfString("RANKING", this->getFont("StartFontF"));
	  tmp->SetPosition(725 + x, 375 + y);
	}
      else
	{
	  tmp = this->getStdToSfString("CLASSEMENT", this->getFont("StartFontF"));
	  tmp->SetPosition(725 + x - 60, 375 + y);
	}
    }
  else
    {
      if (language == ENGLISH)
	{
	  tmp = this->getStdToSfString("RANKING", this->getFont("StartFontE"));
	  tmp->SetPosition(725 + x, 375 + y);
	}
      else
	{
	  tmp = this->getStdToSfString("CLASSEMENT", this->getFont("StartFontE"));
	  tmp->SetPosition(725 + x - 60, 375 + y);
	}
    }
  tmp->SetColor(sf::Color(255,255,255, 255));
  this->_app.Draw(*tmp);
}

LibGraphic::Event LibGraphic::StateStart::gereEvent()
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
		if (errorToPrint)
		  errorToPrint = false;
		else
		  this->_currentButton = BUTTON_EXIT;
		break;
	      }
	    case sf::Key::H :
	      {
		if (helpToShow)
		  helpToShow = false;
		else
		  helpToShow = true;
		break;
	      }
	    case sf::Key::Return :
	      {
		if (this->_currentButton == BUTTON_OPTIONS)
		  {
		    this->playSound();
		    this->_nextState = OPTIONS;
		    return EVENT_CHANGE_STATE;
		  }
		else if (this->_currentButton == BUTTON_PLAY)
		  {
		    this->playSound();
		    this->_nextState = ROOMLIST;
		    // return EVENT_CHANGE_STATE;
		    return (EVENT_START_PLAY);
		  }
		else if (this->_currentButton == BUTTON_EXIT)
		  {
		    this->playSound();
		    this->_app.Close();
		    exit(EXIT_SUCCESS);
		  }
		else if (this->_currentButton == BUTTON_RANKING)
		  {
 		    // this->_nextState = RANKING;
		    // return EVENT_CHANGE_STATE;
		    this->playSound();
		    return (EVENT_START_RANK);
		  }
		else if (this->_currentButton == BUTTON_CREDITS)
		  {
		    this->playSound();
		    this->_nextState = CREDITS;
		    return EVENT_CHANGE_STATE;
		  }
		break;
	      }
	    default: break;
	    }
	}
      else if (Event.Type == sf::Event::JoyButtonReleased)
	{
	  switch (Event.JoyButton.Button)
	    {
	    case 0:
	      {
		if (this->_currentButton == BUTTON_OPTIONS)
		  {
		    this->playSound();
		    this->_nextState = OPTIONS;
		    return EVENT_CHANGE_STATE;
		  }
		else if (this->_currentButton == BUTTON_EXIT)
		  {
		    this->playSound();
		    this->_app.Close();
		    exit(EXIT_SUCCESS);
		  }
		else if (this->_currentButton == BUTTON_PLAY)
		  {
		    this->playSound();
		    this->_nextState = ROOMLIST;
		    // return EVENT_CHANGE_STATE;
		    return (EVENT_START_PLAY);
		  }
		else if (this->_currentButton == BUTTON_RANKING)
		  {
		    this->playSound();
		    // this->_nextState = RANKING;
		    // return EVENT_CHANGE_STATE;
		    return (EVENT_START_RANK);
		  }
		else if (this->_currentButton == BUTTON_CREDITS)
		  {
		    this->playSound();
		    this->_nextState = CREDITS;
		    return EVENT_CHANGE_STATE;
		  }
 		break;
	      }
	    case 1:
	      {
		this->playSound();
		this->_currentButton = BUTTON_EXIT;
		break;
	      }
	    default: break;
	    }
	}
      cursorMenuPos(Event);
    }
  return EVENT_NONE;
}

LibGraphic::eStates LibGraphic::StateStart::getNextState()
{
  return this->_nextState;
}

void LibGraphic::StateStart::cursorMenuPos(const sf::Event & Event)
{
  const sf::Input & Input = this->_app.GetInput();
  float JoystickPOV = Input.GetJoystickAxis(0, sf::Joy::AxisPOV);

  if ((JoystickPOV == -1 && Event.Type != sf::Event::KeyPressed) ||
      this->Clock.GetElapsedTime() < 0.1)
    return;
  switch (this->_currentButton)
    {
    case BUTTON_PLAY :
      {
	if ((JoystickPOV > 45 && JoystickPOV < 135) ||
	    Event.Key.Code == sf::Key::Right)
	  this->_currentButton = BUTTON_OPTIONS;
	else if ((JoystickPOV > 135 && JoystickPOV < 225) ||
		 Event.Key.Code == sf::Key::Down)
	  this->_currentButton = BUTTON_CREDITS;
	else if ((JoystickPOV > 315 || JoystickPOV < 45) ||
		 Event.Key.Code == sf::Key::Up)
	  this->_currentButton = BUTTON_INTRO;
	break;
      }
    case BUTTON_EXIT :
      {
	if ((JoystickPOV >= 225 && JoystickPOV < 315) ||
	    Event.Key.Code == sf::Key::Left)
	  this->_currentButton = BUTTON_CREDITS;
	else if ((JoystickPOV > 315 || (JoystickPOV < 45 && JoystickPOV != -1)) ||
		 Event.Key.Code == sf::Key::Up)
	  this->_currentButton = BUTTON_OPTIONS;
	break;
      }
    case BUTTON_CREDITS :
      {
	if ((JoystickPOV > 45 && JoystickPOV < 135) ||
	    Event.Key.Code == sf::Key::Right)
	  this->_currentButton = BUTTON_EXIT;
	else if ((JoystickPOV > 315 || (JoystickPOV < 45 && JoystickPOV != -1)) ||
		 Event.Key.Code == sf::Key::Up)
	  this->_currentButton = BUTTON_PLAY;
	break;
      }
    case BUTTON_OPTIONS :
      {
	if ((JoystickPOV > 225 && JoystickPOV < 315) ||
	    Event.Key.Code == sf::Key::Left)
	  this->_currentButton = BUTTON_PLAY;
	else if ((JoystickPOV > 135 && JoystickPOV < 225) ||
		 Event.Key.Code == sf::Key::Down)
	  this->_currentButton = BUTTON_EXIT;
	else if ((JoystickPOV > 315 || (JoystickPOV < 45 && JoystickPOV != -1)) ||
		 Event.Key.Code == sf::Key::Up)
	  this->_currentButton = BUTTON_RANKING;
	break;
      }
    case BUTTON_RANKING :
      {
	if ((JoystickPOV > 225 && JoystickPOV < 315) ||
	    Event.Key.Code == sf::Key::Left)
	  this->_currentButton = BUTTON_INTRO;
	else if ((JoystickPOV > 135 && JoystickPOV < 225) ||
		 Event.Key.Code == sf::Key::Down)
	  this->_currentButton = BUTTON_OPTIONS;
	break;
      }
    case BUTTON_INTRO :
      {
	if ((JoystickPOV > 45 && JoystickPOV < 135) ||
	    Event.Key.Code == sf::Key::Right)
	  this->_currentButton = BUTTON_RANKING;
	else if ((JoystickPOV > 135 && JoystickPOV < 225) ||
		 Event.Key.Code == sf::Key::Down)
	  this->_currentButton = BUTTON_PLAY;
	break;
      }
    }
  this->Clock.Reset();
}
