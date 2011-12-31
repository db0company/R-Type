#include "StateOptions.hpp"

LibGraphic::StateOptions::StateOptions(std::map<std::string const, GraphicRessource *> const & ressourcesSprite,
						   std::map<std::string const, MyMusic *> const & ressourcesPlayList,
						   std::map<std::string const, MySound *> const & ressourcesSounds,
						   std::map<std::string const, sf::Font *> const & ressourcesFont,
						   sf::RenderWindow & app):
  _ressourcesSprite(ressourcesSprite), _ressourcesPlayList(ressourcesPlayList),
  _ressourcesSounds(ressourcesSounds), _ressourcesFont(ressourcesFont),
  _app(app)
{
  this->_currentButton = BUTTON_OPTIONS_NAME;
  this->_nextState = UNKNOWN_STATE;
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
  sf::String *Back = this->getStdToSfString("Back", this->getFont("StartFontF"));
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
  sf::Sprite &testBoxE = this->getSprite("BoxEmpty");
  sf::Sprite &testBoxC = this->getSprite("BoxChecked");

  sf::Sprite &English = this->getSprite("English");
  sf::Sprite &Francais = this->getSprite("Francais");

  sf::Sprite &VolumeMusicBar = this->getSprite("VolumeBar");
  sf::Sprite &VolumeMusicButton = this->getSprite("VolumeButton");

  sf::Sprite &VolumeEffectBar = this->getSprite("VolumeBar");
  sf::Sprite &VolumeEffectButton = this->getSprite("VolumeButton");

  menu.SetPosition(500, 290);
  menu_bas.SetPosition(500, 290 + 443);
  menu_haut.SetPosition(500 + 62, 290);
  menu_droite.SetPosition(500 + 592, 290);
  menu_gauche.SetPosition(500, 290 + 57);
  menu_diago.SetPosition(500, 290);
  menu_coins.SetPosition(399, 213);
  menu.SetColor(sf::Color(255, 255, 255, 210));
  this->_app.Draw(back);
  this->_app.Draw(menu);
  this->_app.Draw(menu_diago);
  this->_app.Draw(menu_gauche);
  this->_app.Draw(menu_droite);
  this->_app.Draw(menu_bas);
  this->_app.Draw(menu_haut);
  this->_app.Draw(menu_coins);

  //  tmp = this->getStdToSfString(this->test, this->getFont("StartFontF"));
  //  tmp->SetText(this->test);
  //  tmp->SetPosition(750, 360);
  //  tmp->SetColor(sf::Color(0, 0, 0, 255));

  NameArea.SetPosition(770, 340);
  this->_app.Draw(NameArea);
  //  this->_app.Draw(*tmp);
  IpArea.SetPosition(770, 390);
  this->_app.Draw(IpArea);
  PortArea.SetPosition(770, 440);
  this->_app.Draw(PortArea);

  VolumeMusicBar.SetPosition(758, 510);
  VolumeMusicBar.SetScale(0.8, 1);
  this->_app.Draw(VolumeMusicBar);
  VolumeMusicButton.SetPosition(780, 503);
  VolumeMusicButton.SetScale(0.8, 0.8);
  this->_app.Draw(VolumeMusicButton);

  VolumeEffectBar.SetPosition(758, 560);
  VolumeEffectBar.SetScale(0.8, 1);
  this->_app.Draw(VolumeEffectBar);
  VolumeEffectButton.SetPosition(780, 553);
  VolumeEffectButton.SetScale(0.8, 0.8);
  this->_app.Draw(VolumeEffectButton);

  English.SetPosition(900, 600);
  Francais.SetPosition(1000, 600);
    English.SetColor(sf::Color(255,255,255, 255));
  Francais.SetColor(sf::Color(255,255,255, 255));
  if (this->_currentButton != BUTTON_OPTIONS_LANG_EN)
    English.SetColor(sf::Color(255,255,255, 120));
  if (this->_currentButton != BUTTON_OPTIONS_LANG_FR)
    Francais.SetColor(sf::Color(255,255,255, 120));
  this->_app.Draw(Francais);
  this->_app.Draw(English);

  ButtonBack.SetPosition(720, 730);
  ButtonBack.SetRotation(180);
  this->_app.Draw(ButtonBack);
  Back->SetPosition(565, 694);
  Back->SetText("Back");
  Back->SetScale(1, 0.8);
  Back->SetColor(sf::Color(255,255,0, 255));
  if (this->_currentButton != BUTTON_OPTIONS_BACK)
    Back->SetColor(sf::Color(255,255,255, 205));
  this->_app.Draw(*Back);

  Ok->SetPosition(965, 694);
  Ok->SetText("Ok");
  Ok->SetScale(1, 0.8);
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

  tmp = this->getStdToSfString("Name", this->getFont("StartFontF"));
  tmp->SetColor(sf::Color(255,255,0, 255));
  if (this->_currentButton != BUTTON_OPTIONS_NAME)
    tmp->SetColor(sf::Color(255,255,255, 205));
  tmp->SetPosition(550, 335);
  this->_app.Draw(*tmp);

  tmp = this->getStdToSfString("Ip", this->getFont("StartFontF"));
  tmp->SetColor(sf::Color(255,255,0, 255));
  if (this->_currentButton != BUTTON_OPTIONS_IP)
    tmp->SetColor(sf::Color(255,255,255, 205));
  tmp->SetPosition(550, 385);
  this->_app.Draw(*tmp);

  tmp = this->getStdToSfString("Port", this->getFont("StartFontF"));
  tmp->SetColor(sf::Color(255,255,0, 255));
  if (this->_currentButton != BUTTON_OPTIONS_PORT)
    tmp->SetColor(sf::Color(255,255,255, 205));
  tmp->SetPosition(550, 435);
  this->_app.Draw(*tmp);

  tmp = this->getStdToSfString("Musics", this->getFont("StartFontF"));
  tmp->SetColor(sf::Color(255,255,0, 255));
  if (this->_currentButton != BUTTON_OPTIONS_VOL_MUSICS)
    tmp->SetColor(sf::Color(255,255,255, 205));
  tmp->SetPosition(550, 495);
  this->_app.Draw(*tmp);

  tmp = this->getStdToSfString("Effects", this->getFont("StartFontF"));
  tmp->SetColor(sf::Color(255,255,0, 255));
  if (this->_currentButton != BUTTON_OPTIONS_VOL_EFFECTS)
    tmp->SetColor(sf::Color(255,255,255, 205));
  tmp->SetPosition(550, 550);
  this->_app.Draw(*tmp);
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
		//		this->test = this->test.substr(0, this->test.length() - 1);
		break;
	      }
	    default: break;
	    }
	}
      else if (Event.Type == sf::Event::TextEntered)
	{
	  if (Event.Text.Unicode > 20 && Event.Text.Unicode < 128)
	    {
	      // if (test.size() <= 10)
	      // 	this->test += static_cast<char>(Event.Text.Unicode);
	    }
	}
    }
  cursorMenuPos(Event);
  return EVENT_NONE;
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
	    (Event.Key.Code == sf::Key::Down))
	  this->_currentButton = BUTTON_OPTIONS_IP;
	else if ((JoystickPOV > 315 || JoystickPOV < 45) ||
		 (Event.Key.Code == sf::Key::Up))
	  this->_currentButton = BUTTON_OPTIONS_BACK;
	break;
      }
    case BUTTON_OPTIONS_IP :
      {
	if ((JoystickPOV > 135 && JoystickPOV < 225) ||
	    (Event.Key.Code == sf::Key::Down))
	  this->_currentButton = BUTTON_OPTIONS_PORT;
	else if ((JoystickPOV > 315 || JoystickPOV < 45) ||
		 Event.Key.Code == sf::Key::Up)
	  this->_currentButton = BUTTON_OPTIONS_NAME;
	break;
      }
    case BUTTON_OPTIONS_PORT :
      {
	if ((JoystickPOV > 135 && JoystickPOV < 225) ||
	    (Event.Key.Code == sf::Key::Down))
	  this->_currentButton = BUTTON_OPTIONS_VOL_MUSICS;
	else if ((JoystickPOV > 315 || JoystickPOV < 45) ||
		 Event.Key.Code == sf::Key::Up)
	  this->_currentButton = BUTTON_OPTIONS_IP;
	break;
      }
    case BUTTON_OPTIONS_VOL_MUSICS :
      {
	if ((JoystickPOV > 135 && JoystickPOV < 225) ||
	    (Event.Key.Code == sf::Key::Down))
	  this->_currentButton = BUTTON_OPTIONS_VOL_EFFECTS;
	else if ((JoystickPOV > 315 || JoystickPOV < 45) ||
		 Event.Key.Code == sf::Key::Up)
	  this->_currentButton = BUTTON_OPTIONS_PORT;
	break;
      }
    case BUTTON_OPTIONS_VOL_EFFECTS :
      {
	if ((JoystickPOV > 135 && JoystickPOV < 225) ||
	    (Event.Key.Code == sf::Key::Down))
	  this->_currentButton = BUTTON_OPTIONS_LANG_EN;
	else if ((JoystickPOV > 315 || JoystickPOV < 45) ||
		 Event.Key.Code == sf::Key::Up)
	  this->_currentButton = BUTTON_OPTIONS_VOL_MUSICS;
	break;
      }
    case BUTTON_OPTIONS_LANG_EN :
      {
	if ((JoystickPOV > 45 && JoystickPOV < 135) ||
	    Event.Key.Code == sf::Key::Right)
	  this->_currentButton = BUTTON_OPTIONS_LANG_FR;
	else if ((JoystickPOV > 135 && JoystickPOV < 225) ||
	    (Event.Key.Code == sf::Key::Down))
	  this->_currentButton = BUTTON_OPTIONS_VALIDATE;
	else if ((JoystickPOV > 315 || JoystickPOV < 45) ||
		 Event.Key.Code == sf::Key::Up)
	  this->_currentButton = BUTTON_OPTIONS_VOL_EFFECTS;
	break;
      }
    case BUTTON_OPTIONS_LANG_FR :
      {
	if ((JoystickPOV > 45 && JoystickPOV < 135) ||
	    Event.Key.Code == sf::Key::Left)
	  this->_currentButton = BUTTON_OPTIONS_LANG_EN;
	else if ((JoystickPOV > 135 && JoystickPOV < 225) ||
		 (Event.Key.Code == sf::Key::Down))
	  this->_currentButton = BUTTON_OPTIONS_VALIDATE;
	else if ((JoystickPOV > 315 || JoystickPOV < 45) ||
		 Event.Key.Code == sf::Key::Up)
	  this->_currentButton = BUTTON_OPTIONS_VOL_EFFECTS;
	break;
      }
    case BUTTON_OPTIONS_BACK :
      {
	if ((JoystickPOV > 45 && JoystickPOV < 135) ||
	    Event.Key.Code == sf::Key::Right)
	    this->_currentButton = BUTTON_OPTIONS_VALIDATE;
	else if ((JoystickPOV > 135 && JoystickPOV < 225) ||
		 (Event.Key.Code == sf::Key::Down))
	  this->_currentButton = BUTTON_OPTIONS_NAME;
	else if ((JoystickPOV > 315 || JoystickPOV < 45) ||
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
		 (Event.Key.Code == sf::Key::Down))
	  this->_currentButton = BUTTON_OPTIONS_NAME;
	else if ((JoystickPOV > 315 || JoystickPOV < 45) ||
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


