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
  this->_currentButton = PLAY;
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
    case PLAY :
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
    case OPTIONS :
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
    case CREDITS :
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
    case EXIT :
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
    case INTRO :
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
    case RANKING :
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
  const sf::Input & Input = this->_app.GetInput();

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
	    default: break;
	    }
	}
    }

  cursorMenuPos(Event);
  return EVENT_NONE;
}

void LibGraphic::StateStart::cursorMenuPos(const sf::Event & Event)
{
  const sf::Input & Input = this->_app.GetInput();
  float JoystickPOV = Input.GetJoystickAxis(0, sf::Joy::AxisPOV);

  std::cout << JoystickPOV << std::endl;
  if (JoystickPOV == -1 && Event.Type != sf::Event::KeyPressed)
    return;
  if (Event.Key.Code == sf::Key::Up)
    {
      std::cout << "UP" << std::endl;
    }
  switch (this->_currentButton)
    {
    case PLAY :
      {
	if ((JoystickPOV > 45 && JoystickPOV < 135) ||
	    Event.Key.Code == sf::Key::Right)
	  this->_currentButton = OPTIONS;
	else if ((JoystickPOV > 135 && JoystickPOV < 225) ||
		 Event.Key.Code == sf::Key::Down)
	  this->_currentButton = CREDITS;
	else if ((JoystickPOV > 315 || JoystickPOV < 45) ||
		 Event.Key.Code == sf::Key::Up)
	  this->_currentButton = INTRO;
	break;
      }
    case EXIT :
      {
	if ((JoystickPOV >= 225 && JoystickPOV < 315) ||
	    Event.Key.Code == sf::Key::Left)
	  this->_currentButton = CREDITS;
	else if ((JoystickPOV > 315 || JoystickPOV < 45) ||
		 Event.Key.Code == sf::Key::Up)
	  this->_currentButton = OPTIONS;
	break;
      }
    case CREDITS :
      {
	if ((JoystickPOV > 45 && JoystickPOV < 135) ||
	    Event.Key.Code == sf::Key::Right)
	  this->_currentButton = EXIT;
	else if ((JoystickPOV > 315 || JoystickPOV < 45) ||
		 Event.Key.Code == sf::Key::Up)
	  this->_currentButton = PLAY;
	break;
      }
    case OPTIONS :
      {
	if ((JoystickPOV > 225 && JoystickPOV < 315) ||
	    Event.Key.Code == sf::Key::Left)
	  this->_currentButton = PLAY;
	else if ((JoystickPOV > 135 && JoystickPOV < 225) ||
		 Event.Key.Code == sf::Key::Down)
	  this->_currentButton = EXIT;
	else if ((JoystickPOV > 315 || JoystickPOV < 45) ||
		 Event.Key.Code == sf::Key::Up)
	  this->_currentButton = RANKING;
	break;
      }
    case RANKING :
      {
	if ((JoystickPOV > 225 && JoystickPOV < 315) ||
	    Event.Key.Code == sf::Key::Left)
	  this->_currentButton = INTRO;
	else if ((JoystickPOV > 135 && JoystickPOV < 225) ||
		 Event.Key.Code == sf::Key::Down)
	  this->_currentButton = OPTIONS;
	break;
      }
    case INTRO :
      {
	if ((JoystickPOV > 45 && JoystickPOV < 135) ||
	    Event.Key.Code == sf::Key::Right)
	  this->_currentButton = RANKING;
	else if ((JoystickPOV > 135 && JoystickPOV < 225) ||
		 Event.Key.Code == sf::Key::Down)
	  this->_currentButton = PLAY;
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
