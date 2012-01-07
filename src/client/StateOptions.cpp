#include <iostream>
#include "StateOptions.hpp"
#include "Language.hpp"

extern LibGraphic::Volume gVolume;
extern LibGraphic::Language language;

LibGraphic::StateOptions::StateOptions(std::map<std::string const, GraphicRessource *> const & ressourcesSprite,
						   std::map<std::string const, MyMusic *> const & ressourcesPlayList,
						   std::map<std::string const, MySound *> const & ressourcesSounds,
						   std::map<std::string const, sf::Font *> const & ressourcesFont,
						   sf::RenderWindow & app):
  _ressourcesSprite(ressourcesSprite), _ressourcesPlayList(ressourcesPlayList),
  _ressourcesSounds(ressourcesSounds), _ressourcesFont(ressourcesFont),
  _app(app), _action(UNKNOWN)
{
  this->_currentButton = BUTTON_OPTIONS_NAME;
  this->_nextState = UNKNOWN_STATE;

  if (language == ENGLISH)
    this->_name = "Player";
  else
    this->_name = "Joueur";
  // this->_ip = "xxx.xxx.xxx.xxx";
  // this->_port = "xxxxx";
  this->_ip = "127.0.0.1";
  this->_port = "12348";
  this->_isDefaultName = true;
  this->_isDefaultIp = true;
  this->_isDefaultPort = true;
}

LibGraphic::StateOptions::~StateOptions()
{
}

bool LibGraphic::StateOptions::init()
{
  return true;
}

void LibGraphic::StateOptions::draw()
{
  sf::String *Back;
  if (language == ENGLISH)
    Back = this->getStdToSfString("Back", this->getFont("StartFontF"));
  else
    Back = this->getStdToSfString("Retour", this->getFont("StartFontF"));
  sf::String *Ok = this->getStdToSfString("Ok", this->getFont("StartFontF"));

  sf::Sprite &back = this->getSprite("StartMenuBackground");
  sf::Sprite &menu = this->getSprite("OptionsMenu");
  sf::Sprite &menu_haut = this->getSprite("OptionsMenu-haut");
  sf::Sprite &menu_bas = this->getSprite("OptionsMenu-bas");
  sf::Sprite &menu_gauche = this->getSprite("OptionsMenu-gauche");
  sf::Sprite &menu_droite = this->getSprite("OptionsMenu-droite");
  sf::Sprite &menu_coins = this->getSprite("OptionsMenu-coins");
  sf::Sprite &menu_diago = this->getSprite("OptionsMenu-diago");

  sf::Sprite &NameArea = this->getSprite("TextArea");
  sf::Sprite &IpArea = this->getSprite("TextArea");
  sf::Sprite &PortArea = this->getSprite("TextArea");

  sf::Sprite &ButtonBack = this->getSprite("BasicButton");
  sf::Sprite &ButtonOk = this->getSprite("BasicButton");

  sf::Sprite &English = this->getSprite("English");
  sf::Sprite &Francais = this->getSprite("Francais");

  sf::Sprite &VolumeMusicBar = this->getSprite("VolumeBar");
  sf::Sprite &VolumeMusicButton = this->getSprite("VolumeButton");

  sf::Sprite &VolumeEffectBar = this->getSprite("VolumeBar");
  sf::Sprite &VolumeEffectButton = this->getSprite("VolumeButton");


  this->_app.Draw(back);

  menu.SetPosition(500, 290);
  menu_bas.SetPosition(500, 290 + 443);
  menu_haut.SetPosition(500 + 62, 290);
  menu_droite.SetPosition(500 + 592, 290);
  menu_gauche.SetPosition(500, 290 + 57);
  menu_diago.SetPosition(500, 290);
  menu_coins.SetPosition(399, 213);
  menu.SetColor(sf::Color(255, 255, 255, 210));
  this->_app.Draw(menu);
  this->_app.Draw(menu_diago);
  this->_app.Draw(menu_gauche);
  this->_app.Draw(menu_droite);
  this->_app.Draw(menu_bas);
  this->_app.Draw(menu_haut);
  this->_app.Draw(menu_coins);

  NameArea.SetPosition(770, 340);
  this->_app.Draw(NameArea);
  IpArea.SetPosition(770, 390);
  this->_app.Draw(IpArea);
  PortArea.SetPosition(770, 440);
  this->_app.Draw(PortArea);

  VolumeMusicBar.SetPosition(758, 510);
  VolumeMusicBar.SetScale(0.8, 1);
  this->_app.Draw(VolumeMusicBar);
  VolumeMusicButton.SetPosition(780 + (gVolume.musicVolume * 2.6), 503);
  VolumeMusicButton.SetScale(0.8, 0.8);
  this->_app.Draw(VolumeMusicButton);

  VolumeEffectBar.SetPosition(758, 560);
  VolumeEffectBar.SetScale(0.8, 1);
  this->_app.Draw(VolumeEffectBar);
  VolumeEffectButton.SetPosition(780 + (gVolume.soundVolume * 2.6), 553);
  VolumeEffectButton.SetScale(0.8, 0.8);
  this->_app.Draw(VolumeEffectButton);

  English.SetPosition(900, 600);
  Francais.SetPosition(1000, 600);
  English.SetColor(sf::Color(255,255,255, 255));
  Francais.SetColor(sf::Color(255,255,255, 255));
  if (this->_currentButton != BUTTON_OPTIONS_LANG_EN && language != ENGLISH)
    English.SetColor(sf::Color(255,255,255, 120));
  if (this->_currentButton != BUTTON_OPTIONS_LANG_FR && language != FRANCAIS)
    Francais.SetColor(sf::Color(255,255,255, 120));
  this->_app.Draw(Francais);
  this->_app.Draw(English);

  ButtonBack.SetPosition(720, 730);
  ButtonBack.SetRotation(180);
  this->_app.Draw(ButtonBack);
  if (language == ENGLISH)
    Back->SetPosition(575, 697);
  else
    Back->SetPosition(555, 697);
  Back->SetScale(0.7, 0.7);
  Back->SetColor(sf::Color(255,255,0, 255));
  if (this->_currentButton != BUTTON_OPTIONS_BACK)
    Back->SetColor(sf::Color(255,255,255, 205));
  this->_app.Draw(*Back);

  Ok->SetPosition(975, 697);
  Ok->SetScale(0.7, 0.7);
  ButtonOk.SetPosition(1100, 730);
  this->_app.Draw(ButtonOk);
  Ok->SetColor(sf::Color(255,255,0, 255));
  if (this->_currentButton != BUTTON_OPTIONS_VALIDATE)
    Ok->SetColor(sf::Color(255,255,255, 205));
  this->_app.Draw(*Ok);
  this->drawText();
}

void LibGraphic::StateOptions::drawText()
{
  sf::String *tmp;


  if (language == ENGLISH)
    tmp = this->getStdToSfString("Name", this->getFont("StartFontF"));
  else
    tmp = this->getStdToSfString("Nom", this->getFont("StartFontF"));
  tmp->SetColor(sf::Color(255,255,0, 255));
  if (this->_currentButton != BUTTON_OPTIONS_NAME)
    tmp->SetColor(sf::Color(255,255,255, 205));
  tmp->SetPosition(550, 340);
  tmp->SetScale(0.8, 0.8);
  this->_app.Draw(*tmp);

  tmp = this->getStdToSfString("Ip", this->getFont("StartFontF"));
  tmp->SetColor(sf::Color(255,255,0, 255));
  if (this->_currentButton != BUTTON_OPTIONS_IP)
    tmp->SetColor(sf::Color(255,255,255, 205));
  tmp->SetPosition(550, 390);
  tmp->SetScale(0.8, 0.8);
  this->_app.Draw(*tmp);

  tmp = this->getStdToSfString("Port", this->getFont("StartFontF"));
  tmp->SetColor(sf::Color(255,255,0, 255));
  if (this->_currentButton != BUTTON_OPTIONS_PORT)
    tmp->SetColor(sf::Color(255,255,255, 205));
  tmp->SetPosition(550, 440);
  tmp->SetScale(0.8, 0.8);
  this->_app.Draw(*tmp);

  if (language == ENGLISH)
    tmp = this->getStdToSfString("Music", this->getFont("StartFontF"));
  else
    tmp = this->getStdToSfString("Musique", this->getFont("StartFontF"));
  tmp->SetColor(sf::Color(255,255,0, 255));
  if (this->_currentButton != BUTTON_OPTIONS_VOL_MUSICS)
    tmp->SetColor(sf::Color(255,255,255, 205));
  tmp->SetPosition(550, 500);
  tmp->SetScale(0.8, 0.8);
  this->_app.Draw(*tmp);

  if (language == ENGLISH)
    tmp = this->getStdToSfString("Effect", this->getFont("StartFontF"));
  else
    tmp = this->getStdToSfString("Son", this->getFont("StartFontF"));
  tmp->SetColor(sf::Color(255,255,0, 255));
  if (this->_currentButton != BUTTON_OPTIONS_VOL_EFFECTS)
    tmp->SetColor(sf::Color(255,255,255, 205));
  tmp->SetPosition(550, 555);
  tmp->SetScale(0.8, 0.8);
  this->_app.Draw(*tmp);

  if (language == ENGLISH)
    tmp = this->getStdToSfString("Language", this->getFont("StartFontF"));
  else
    tmp = this->getStdToSfString("Langue", this->getFont("StartFontF"));
  tmp->SetColor(sf::Color(255,255,0, 255));
  if (this->_currentButton != BUTTON_OPTIONS_LANG_FR
      && this->_currentButton != BUTTON_OPTIONS_LANG_EN)
    tmp->SetColor(sf::Color(255,255,255, 205));
  tmp->SetPosition(550, 625);
  tmp->SetScale(0.8, 0.8);
  this->_app.Draw(*tmp);

  tmp = this->getStdToSfString(this->_name, this->getFont("StartFontF"));
  tmp->SetText(this->_name);
  tmp->SetPosition(785, 347);
  tmp->SetScale(0.6, 0.6);
  tmp->SetColor(sf::Color(0, 0, 0, 255));
   if (this->_currentButton != BUTTON_OPTIONS_NAME)
    tmp->SetColor(sf::Color(0, 0, 0, 155));
 this->_app.Draw(*tmp);

  tmp = this->getStdToSfString(this->_ip, this->getFont("StartFontF"));
  tmp->SetText(this->_ip);
  tmp->SetPosition(785, 397);
  tmp->SetScale(0.6, 0.6);
  tmp->SetColor(sf::Color(0, 0, 0, 255));
  if (this->_currentButton != BUTTON_OPTIONS_IP)
    tmp->SetColor(sf::Color(0, 0, 0, 155));
  this->_app.Draw(*tmp);

  tmp = this->getStdToSfString(this->_port, this->getFont("StartFontF"));
  tmp->SetText(this->_port);
  tmp->SetPosition(785, 447);
  tmp->SetScale(0.6, 0.6);
  tmp->SetColor(sf::Color(0, 0, 0, 255));
  if (this->_currentButton != BUTTON_OPTIONS_PORT)
    tmp->SetColor(sf::Color(0, 0, 0, 155));
  this->_app.Draw(*tmp);

  MyMusic * song = this->getMusic("StartMusic");
  if (song->GetMusicState() == sf::Music::Stopped ||
      song->GetMusicState() == sf::Music::Paused)
    song->PlayMusic();
  song->UpdateVolume();
}

LibGraphic::Event LibGraphic::StateOptions::gereEvent()
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
	    case sf::Key::Back :
	      {
		if (this->_currentButton == BUTTON_OPTIONS_NAME)
		  this->_name = this->_name.substr(0, this->_name.length() - 1);
		else if (this->_currentButton == BUTTON_OPTIONS_IP)
		  this->_ip = this->_ip.substr(0, this->_ip.length() - 1);
		else if (this->_currentButton == BUTTON_OPTIONS_PORT)
		  this->_port = this->_port.substr(0, this->_port.length() - 1);
		break;
	      }
	    case sf::Key::Return :
	      {
		if (this->_currentButton == BUTTON_OPTIONS_BACK ||
		    this->_currentButton == BUTTON_OPTIONS_VALIDATE)
		  {
		    this->_nextState = START;
		    return EVENT_CHANGE_STATE;
		  }
		else if (this->_currentButton == BUTTON_OPTIONS_LANG_FR)
		  language = FRANCAIS;
		else if (this->_currentButton == BUTTON_OPTIONS_LANG_EN)
		  language = ENGLISH;
	      }
	    default: break;
	    }
	}
      else if (Event.Type == sf::Event::TextEntered &&
	       (Event.Text.Unicode > 20 && Event.Text.Unicode < 128))
	readText(Event);
      else if (Event.Type == sf::Event::JoyButtonReleased)
	{
	  switch (Event.JoyButton.Button)
	    {
	    case 0:
	      {
		if (this->_currentButton == BUTTON_OPTIONS_BACK ||
		    this->_currentButton == BUTTON_OPTIONS_VALIDATE)
		  {
		    this->_nextState = START;
		    return EVENT_CHANGE_STATE;
		  }
		else if (this->_currentButton == BUTTON_OPTIONS_LANG_FR)
		  language = FRANCAIS;
		else if (this->_currentButton == BUTTON_OPTIONS_LANG_EN)
		  language = ENGLISH;
	      }
	    case 1:
	      {
		if (this->_currentButton == BUTTON_OPTIONS_BACK)
		  {
		    this->_nextState = START;
		    return EVENT_CHANGE_STATE;
		  }
		this->_currentButton = BUTTON_OPTIONS_BACK;
		break;
	      }
	    }
	}
      cursorMenuPos(Event);
    }
  return EVENT_NONE;
}

void LibGraphic::StateOptions::readText(const sf::Event & Event)
{
  if (this->_currentButton == BUTTON_OPTIONS_NAME && this->_isDefaultName)
    {
      this->_isDefaultName = !this->_isDefaultName;
      this->_name = "";
    }
  else if (this->_currentButton == BUTTON_OPTIONS_IP && this->_isDefaultIp)
    {
      this->_isDefaultIp = !this->_isDefaultIp;
      this->_ip = "";
    }
  else if (this->_currentButton == BUTTON_OPTIONS_PORT && this->_isDefaultPort)
    {
      this->_isDefaultPort = !this->_isDefaultPort;
      this->_port = "";
    }

  if (this->_currentButton == BUTTON_OPTIONS_NAME && this->_name.size() <= 12)
    this->_name += static_cast<char>(Event.Text.Unicode);
  else if (this->_currentButton == BUTTON_OPTIONS_IP && this->_ip.size() < 15
	   && Event.Text.Unicode >= 46 && Event.Text.Unicode <= 57)
    this->_ip += static_cast<char>(Event.Text.Unicode);
  else if (this->_currentButton == BUTTON_OPTIONS_PORT && this->_port.size() < 16
	   && Event.Text.Unicode >= 48 && Event.Text.Unicode <= 57)
    this->_port += static_cast<char>(Event.Text.Unicode);
}

LibGraphic::eStates LibGraphic::StateOptions::getNextState()
{
  return this->_nextState;
}

void LibGraphic::StateOptions::cursorMenuPos(const sf::Event & Event)
{
  const sf::Input & Input = this->_app.GetInput();
  float JoystickPOV = Input.GetJoystickAxis(0, sf::Joy::AxisPOV);

  if ((JoystickPOV == -1 && Event.Type != sf::Event::KeyPressed) ||
      this->Clock.GetElapsedTime() < 0.1)
    return;

  switch (this->_currentButton)
    {
    case BUTTON_OPTIONS_NAME :
      {
	if ((JoystickPOV > 135 && JoystickPOV < 225) ||
	    Event.Key.Code == sf::Key::Down || Event.Key.Code == sf::Key::Tab)
	  this->_currentButton = BUTTON_OPTIONS_IP;
	else if ((JoystickPOV > 315 || (JoystickPOV < 45 && JoystickPOV != -1))||
		 (Event.Key.Code == sf::Key::Up))
	  this->_currentButton = BUTTON_OPTIONS_BACK;
	break;
      }
    case BUTTON_OPTIONS_IP :
      {
	if ((JoystickPOV > 135 && JoystickPOV < 225) ||
	    (Event.Key.Code == sf::Key::Down || Event.Key.Code == sf::Key::Tab))
	  this->_currentButton = BUTTON_OPTIONS_PORT;
	else if ((JoystickPOV > 315 || (JoystickPOV < 45 && JoystickPOV != -1))||
		 Event.Key.Code == sf::Key::Up)
	  this->_currentButton = BUTTON_OPTIONS_NAME;
	break;
      }
    case BUTTON_OPTIONS_PORT :
      {
	if ((JoystickPOV > 135 && JoystickPOV < 225) ||
	    (Event.Key.Code == sf::Key::Down || Event.Key.Code == sf::Key::Tab))
	  this->_currentButton = BUTTON_OPTIONS_VOL_MUSICS;
	else if ((JoystickPOV > 315 || (JoystickPOV < 45 && JoystickPOV != -1))||
		 Event.Key.Code == sf::Key::Up)
	  this->_currentButton = BUTTON_OPTIONS_IP;
	break;
      }
    case BUTTON_OPTIONS_VOL_MUSICS :
      {
	if ((JoystickPOV > 135 && JoystickPOV < 225) ||
	    (Event.Key.Code == sf::Key::Down || Event.Key.Code == sf::Key::Tab))
	  this->_currentButton = BUTTON_OPTIONS_VOL_EFFECTS;
	else if ((JoystickPOV > 315 || (JoystickPOV < 45 && JoystickPOV != -1))||
		 Event.Key.Code == sf::Key::Up)
	  this->_currentButton = BUTTON_OPTIONS_PORT;
	else if (((JoystickPOV > 45 && JoystickPOV < 135) ||
		  Event.Key.Code == sf::Key::Right) && gVolume.musicVolume < 100)
	  ++gVolume.musicVolume;
	else if (((JoystickPOV > 225 && JoystickPOV < 315) ||
		 Event.Key.Code == sf::Key::Left) && gVolume.musicVolume > 0)
	  --gVolume.musicVolume;
	break;
      }
    case BUTTON_OPTIONS_VOL_EFFECTS :
      {
	if ((JoystickPOV > 135 && JoystickPOV < 225) ||
	    (Event.Key.Code == sf::Key::Down || Event.Key.Code == sf::Key::Tab))
	  this->_currentButton = BUTTON_OPTIONS_LANG_EN;
	else if ((JoystickPOV > 315 || (JoystickPOV < 45 && JoystickPOV != -1))||
		 Event.Key.Code == sf::Key::Up)
	  this->_currentButton = BUTTON_OPTIONS_VOL_MUSICS;
	else if (((JoystickPOV > 45 && JoystickPOV < 135) ||
		  Event.Key.Code == sf::Key::Right) && gVolume.soundVolume < 100)
	  ++gVolume.soundVolume;
	else if (((JoystickPOV > 225 && JoystickPOV < 315) ||
		 Event.Key.Code == sf::Key::Left) && gVolume.soundVolume > 0)
	  --gVolume.soundVolume;
	break;
      }
    case BUTTON_OPTIONS_LANG_EN :
      {
	if ((JoystickPOV > 45 && JoystickPOV < 135)  ||
	    Event.Key.Code == sf::Key::Right)
	  this->_currentButton = BUTTON_OPTIONS_LANG_FR;
	else if ((JoystickPOV > 135 && JoystickPOV < 225) ||
	    (Event.Key.Code == sf::Key::Down || Event.Key.Code == sf::Key::Tab))
	  this->_currentButton = BUTTON_OPTIONS_VALIDATE;
	else if ((JoystickPOV > 315 || (JoystickPOV < 45 && JoystickPOV != -1))||
		 Event.Key.Code == sf::Key::Up)
	  this->_currentButton = BUTTON_OPTIONS_VOL_EFFECTS;
	else if (Event.Key.Code == sf::Key::Return)
	  language = ENGLISH;
	break;
      }
    case BUTTON_OPTIONS_LANG_FR :
      {
	if ((JoystickPOV > 255 && JoystickPOV < 315) ||
	    Event.Key.Code == sf::Key::Left)
	  this->_currentButton = BUTTON_OPTIONS_LANG_EN;
	else if ((JoystickPOV > 135 && JoystickPOV < 225) ||
		 (Event.Key.Code == sf::Key::Down || Event.Key.Code == sf::Key::Tab))
	  this->_currentButton = BUTTON_OPTIONS_VALIDATE;
	else if ((JoystickPOV > 315 || (JoystickPOV < 45 && JoystickPOV != -1))||
		 Event.Key.Code == sf::Key::Up)
	  this->_currentButton = BUTTON_OPTIONS_VOL_EFFECTS;
	else if (Event.Key.Code == sf::Key::Return)
	  language = FRANCAIS;
	break;
      }
    case BUTTON_OPTIONS_BACK :
      {
	if ((JoystickPOV > 45 && JoystickPOV < 135) ||
	    Event.Key.Code == sf::Key::Right)
	    this->_currentButton = BUTTON_OPTIONS_VALIDATE;
	else if ((JoystickPOV > 135 && JoystickPOV < 225) ||
		 (Event.Key.Code == sf::Key::Down || Event.Key.Code == sf::Key::Tab))
	  this->_currentButton = BUTTON_OPTIONS_NAME;
	else if ((JoystickPOV > 315 || (JoystickPOV < 45 && JoystickPOV != -1))||
		 Event.Key.Code == sf::Key::Up)
	  this->_currentButton = BUTTON_OPTIONS_LANG_EN;
	break;
      }
    case BUTTON_OPTIONS_VALIDATE :
      {
	if ((JoystickPOV > 225 && JoystickPOV < 315) ||
	    Event.Key.Code == sf::Key::Left)
	  this->_currentButton = BUTTON_OPTIONS_BACK;
	else if ((JoystickPOV > 135 && JoystickPOV < 225) ||
		 (Event.Key.Code == sf::Key::Down || Event.Key.Code == sf::Key::Tab))
	  this->_currentButton = BUTTON_OPTIONS_NAME;
	else if ((JoystickPOV > 315 || (JoystickPOV < 45 && JoystickPOV != -1))||
		 Event.Key.Code == sf::Key::Up)
	  this->_currentButton = BUTTON_OPTIONS_LANG_EN;
	break;
      }
    default : break;
    }
  this->Clock.Reset();
}

sf::Sprite & LibGraphic::StateOptions::getSprite(std::string const & spriteName) const
{
  return ((*this->_ressourcesSprite.find(spriteName)).second->_sprite);
}

LibGraphic::MyMusic * LibGraphic::StateOptions::getMusic(std::string const & musicName) const
{
  return ((*this->_ressourcesPlayList.find(musicName)).second);
}

sf::Font * LibGraphic::StateOptions::getFont(std::string const & fontName) const
{
  return ((*this->_ressourcesFont.find(fontName)).second);
}

inline sf::String * LibGraphic::StateOptions::getStdToSfString(std::string const & s, sf::Font * daFont)
{
  return (new sf::String(s, *daFont));
}

std::string const & LibGraphic::StateOptions::getName() const
{
  return this->_name;
}

std::string const & LibGraphic::StateOptions::getIp() const
{
  return this->_ip;
}

std::string const & LibGraphic::StateOptions::getPort() const
{
  return this->_port;
}

bool LibGraphic::StateOptions::isDefaultName() const
{
  return this->_isDefaultName;
}

bool LibGraphic::StateOptions::isDefaultIp() const
{
  return this->_isDefaultIp;
}

bool LibGraphic::StateOptions::isDefaultPort() const
{
  return this->_isDefaultPort;
}

eGraphicAction LibGraphic::StateOptions::getAction()
{
  return (this->_action);
}

void LibGraphic::StateOptions::setAction(eGraphicAction g)
{
  this->_action = g;
}

void LibGraphic::StateOptions::setNextState(eStates e)
{
  this->_nextState = e;
}
