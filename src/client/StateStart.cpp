#include "StateStart.hpp"

LibGraphic::StateStart::StateStart(std::map<std::string const, GraphicRessource *> const & ressourcesSprite,
						   std::map<std::string const, MyMusic *> const & ressourcesPlayList,
						   std::map<std::string const, MySound *> const & ressourcesSounds,
						   std::map<std::string const, sf::Font *> const & ressourcesFont,
						   sf::RenderWindow & app):
  _ressourcesSprite(ressourcesSprite), _ressourcesPlayList(ressourcesPlayList),
  _ressourcesSounds(ressourcesSounds), _ressourcesFont(ressourcesFont),
  _app(app)
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

  menu.SetPosition(250, 350);
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
	tmp = this->getStdToSfString("PLAY", this->getFont("StartFontF"));
	tmp->SetPosition(320, 455);
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
	tmp->SetPosition(740, 462);
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
	tmp->SetPosition(440, 595);
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
	tmp = this->getStdToSfString("EXIT", this->getFont("StartFontF"));
	tmp->SetPosition(810, 595);
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
	tmp->SetPosition(440, 375);
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
	tmp = this->getStdToSfString("RANKING", this->getFont("StartFontF"));
	tmp->SetPosition(725, 375);
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

  tmp = this->getStdToSfString("PLAY", this->getFont("StartFontF"));
  tmp->SetColor(sf::Color(255,255,255, 180));
  tmp->SetPosition(320, 455);
  tmp->Scale(2.3, 2.3);
  this->_app.Draw(*tmp);

  tmp = this->getStdToSfString("OPTIONS", this->getFont("StartFontF"));
  tmp->SetColor(sf::Color(255,255,255, 180));
  tmp->SetPosition(740, 462);
  tmp->Scale(1.7, 2.2);
  this->_app.Draw(*tmp);

  tmp = this->getStdToSfString("CREDITS", this->getFont("StartFontF"));
  tmp->SetColor(sf::Color(255,255,255, 180));
  tmp->SetPosition(440, 595);
  this->_app.Draw(*tmp);

  tmp = this->getStdToSfString("EXIT", this->getFont("StartFontF"));
  tmp->SetColor(sf::Color(255,255,255, 180));
  tmp->SetPosition(810, 595);
  this->_app.Draw(*tmp);

  tmp = this->getStdToSfString("INTRO", this->getFont("StartFontF"));
  tmp->SetColor(sf::Color(255,255,255, 180));
  tmp->SetPosition(440, 375);
  this->_app.Draw(*tmp);

  tmp = this->getStdToSfString("RANKING", this->getFont("StartFontF"));
  tmp->SetColor(sf::Color(255,255,255, 180));
  tmp->SetPosition(725, 375);
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
		this->_app.Close();
		exit(EXIT_SUCCESS);
	      }
	    case sf::Key::Return :
	      {
		if (this->_currentButton == BUTTON_OPTIONS)
		  {
		    this->_nextState = OPTIONS;
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
		    this->_nextState = OPTIONS;
		    return EVENT_CHANGE_STATE;
		  }
 		break;
	      }
	    case 1:
	      {
		std::cout << "button 1" << std::endl;
		break;
	      }
	    default: break;
	    }
	}
    }

  cursorMenuPos(Event);
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

  if (JoystickPOV == -1 && Event.Type != sf::Event::KeyPressed)
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
	else if ((JoystickPOV > 315 || JoystickPOV < 45) ||
		 Event.Key.Code == sf::Key::Up)
	  this->_currentButton = BUTTON_OPTIONS;
	break;
      }
    case BUTTON_CREDITS :
      {
	if ((JoystickPOV > 45 && JoystickPOV < 135) ||
	    Event.Key.Code == sf::Key::Right)
	  this->_currentButton = BUTTON_EXIT;
	else if ((JoystickPOV > 315 || JoystickPOV < 45) ||
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
	else if ((JoystickPOV > 315 || JoystickPOV < 45) ||
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
}

sf::Sprite & LibGraphic::StateStart::getSprite(std::string const & spriteName) const
{
  return ((*this->_ressourcesSprite.find(spriteName)).second->_sprite);}

LibGraphic::MyMusic * LibGraphic::StateStart::getMusic(std::string const & musicName) const
{
  return ((*this->_ressourcesPlayList.find(musicName)).second);
}

sf::Font * LibGraphic::StateStart::getFont(std::string const & fontName) const
{
  return ((*this->_ressourcesFont.find(fontName)).second);
}

inline sf::String * LibGraphic::StateStart::getStdToSfString(std::string const & s, sf::Font * daFont)
{
  return (new sf::String(s, *daFont));
}
