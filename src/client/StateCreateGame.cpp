#include <iostream>
#include "StateCreateGame.hpp"
#include "Language.hpp"

extern LibGraphic::Volume gVolume;
extern LibGraphic::Language language;

LibGraphic::StateCreateGame::StateCreateGame(std::map<std::string const, GraphicRessource *> const & ressourcesSprite,
						   std::map<std::string const, MyMusic *> const & ressourcesPlayList,
						   std::map<std::string const, MySound *> const & ressourcesSounds,
						   std::map<std::string const, sf::Font *> const & ressourcesFont,
						   sf::RenderWindow & app):
  _ressourcesSprite(ressourcesSprite), _ressourcesPlayList(ressourcesPlayList),
  _ressourcesSounds(ressourcesSounds), _ressourcesFont(ressourcesFont),
  _app(app)
{
  this->_nextState = UNKNOWN_STATE;
  this->_currentButton = BUTTON_CREATE_SPECTATOR;
  this->_isSpectatorChecked = false;
}

LibGraphic::StateCreateGame::~StateCreateGame()
{
}

bool LibGraphic::StateCreateGame::init()
{
  return true;
}

void LibGraphic::StateCreateGame::draw()
{
  sf::Sprite &back = this->getSprite("StartMenuBackground");
  this->_app.Draw(back);

  sf::Sprite &menu = this->getSprite("OptionsMenu");
  sf::Sprite &menu_haut = this->getSprite("OptionsMenu-haut");
  sf::Sprite &menu_bas = this->getSprite("OptionsMenu-bas");
  sf::Sprite &menu_gauche = this->getSprite("OptionsMenu-gauche");
  sf::Sprite &menu_droite = this->getSprite("OptionsMenu-droite");
  sf::Sprite &menu_coins = this->getSprite("OptionsMenu-coins");
  sf::Sprite &menu_diago = this->getSprite("OptionsMenu-diago");

  sf::Sprite &Button = this->getSprite("BasicButton");

  sf::Sprite &ButtonBox = this->getSprite("BoxEmpty");
  sf::Sprite &ButtonBox_s = this->getSprite("BoxEmpty-s");
  sf::Sprite &ButtonBoxChecked = this->getSprite("BoxChecked");
  sf::Sprite &ButtonBoxChecked_s = this->getSprite("BoxChecked-s");

  sf::Sprite &TextArea = this->getSprite("TextArea");

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

  Button.SetPosition(1100, 730);
  this->_app.Draw(Button);

  Button.SetPosition(730, 730);
  this->_app.Draw(Button);

  TextArea.SetPosition(770, 480);
  this->_app.Draw(TextArea);

  ButtonBox.SetPosition(770, 340);
  ButtonBox_s.SetPosition(770, 340);
  this->_app.Draw(ButtonBox);
  if (this->_currentButton == BUTTON_CREATE_SPECTATOR)
    this->_app.Draw(ButtonBox_s);

  sf::String *tmp;

  ButtonBox.SetPosition(770, 410);
  this->_app.Draw(ButtonBox);
  tmp = this->getStdToSfString("1", this->getFont("StartFontF"));
  tmp->SetColor(sf::Color(0,0,0,255));
  tmp->SetScale(0.6, 0.6);
  tmp->SetPosition(783, 411);
  this->_app.Draw(*tmp);

  ButtonBox.SetPosition(820, 410);
  this->_app.Draw(ButtonBox);
  tmp = this->getStdToSfString("2", this->getFont("StartFontF"));
  tmp->SetColor(sf::Color(0,0,0,255));
  tmp->SetScale(0.6, 0.6);
  tmp->SetPosition(828, 411);
  this->_app.Draw(*tmp);

  ButtonBox.SetPosition(870, 410);
  this->_app.Draw(ButtonBox);
  tmp = this->getStdToSfString("3", this->getFont("StartFontF"));
  tmp->SetColor(sf::Color(0,0,0,255));
  tmp->SetScale(0.6, 0.6);
  tmp->SetPosition(878, 411);
  this->_app.Draw(*tmp);

  ButtonBox.SetPosition(920, 410);
  this->_app.Draw(ButtonBox);
  tmp = this->getStdToSfString("4", this->getFont("StartFontE"));
  tmp->SetColor(sf::Color(0,0,0,255));
  tmp->SetScale(0.6, 0.6);
  tmp->SetPosition(928, 411);
  this->_app.Draw(*tmp);

  this->drawText();
}

void LibGraphic::StateCreateGame::drawText()
{
  sf::String *tmp;

  if (language == ENGLISH)
    {
      tmp = this->getStdToSfString("Back", this->getFont("StartFontF"));
      tmp->SetPosition(590, 700);
    }
  else
    {
      tmp = this->getStdToSfString("Retour", this->getFont("StartFontF"));
      tmp->SetPosition(570, 700);
    }
  tmp->SetScale(0.6, 0.6);
  tmp->SetColor(sf::Color(255,255,0, 255));
  if (this->_currentButton != BUTTON_CREATE_BACK)
    tmp->SetColor(sf::Color(255,255,255, 205));
  this->_app.Draw(*tmp);

  if (language == ENGLISH)
    {
      tmp = this->getStdToSfString("Create", this->getFont("StartFontF"));
      tmp->SetPosition(950, 700);
    }
  else
    {
      tmp = this->getStdToSfString("Lancer", this->getFont("StartFontF"));
      tmp->SetPosition(950, 700);
    }
  tmp->SetScale(0.6, 0.6);
  tmp->SetColor(sf::Color(255,255,0, 255));
  if (this->_currentButton != BUTTON_CREATE_CREATE)
    tmp->SetColor(sf::Color(255,255,255, 205));
  this->_app.Draw(*tmp);

  if (language == ENGLISH)
    {
      tmp = this->getStdToSfString("Spectators", this->getFont("StartFontF"));
      tmp->SetPosition(550, 340);
    }
  else
    {
      tmp = this->getStdToSfString("Spectateurs", this->getFont("StartFontF"));
      tmp->SetPosition(550, 340);
    }
  tmp->SetScale(0.6, 0.6);
  tmp->SetColor(sf::Color(255,255,0, 255));
  if (this->_currentButton != BUTTON_CREATE_SPECTATOR)
    tmp->SetColor(sf::Color(255,255,255, 205));
  this->_app.Draw(*tmp);

  if (language == ENGLISH)
    {
      tmp = this->getStdToSfString("Team size", this->getFont("StartFontF"));
      tmp->SetPosition(550, 410);
    }
  else
    {
      tmp = this->getStdToSfString("Taille de l'equipe", this->getFont("StartFontF"));
      tmp->SetPosition(550, 410);
    }
  tmp->SetScale(0.6, 0.6);
  tmp->SetColor(sf::Color(255,255,0, 255));
  if (this->_currentButton != BUTTON_CREATE_TEAMSIZE)
    tmp->SetColor(sf::Color(255,255,255, 205));
  this->_app.Draw(*tmp);

  if (language == ENGLISH)
    {
      tmp = this->getStdToSfString("Game name", this->getFont("StartFontF"));
      tmp->SetPosition(550, 490);
    }
  else
    {
      tmp = this->getStdToSfString("Nom de la partie", this->getFont("StartFontF"));
      tmp->SetPosition(550, 490);
    }
  tmp->SetScale(0.6, 0.6);
  tmp->SetColor(sf::Color(255,255,0, 255));
  if (this->_currentButton != BUTTON_CREATE_NAME)
    tmp->SetColor(sf::Color(255,255,255, 205));
  this->_app.Draw(*tmp);
}

LibGraphic::Event LibGraphic::StateCreateGame::gereEvent()
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
	    default : break;
	    }
	}
      cursorMenuPos(Event);
    }
  return EVENT_NONE;
}

void LibGraphic::StateCreateGame::readText(const sf::Event & Event)
{
}

LibGraphic::eStates LibGraphic::StateCreateGame::getNextState()
{
  return this->_nextState;
}

void LibGraphic::StateCreateGame::cursorMenuPos(const sf::Event & Event)
{
}

sf::Sprite & LibGraphic::StateCreateGame::getSprite(std::string const & spriteName) const
{
  return ((*this->_ressourcesSprite.find(spriteName)).second->_sprite);
}

LibGraphic::MyMusic * LibGraphic::StateCreateGame::getMusic(std::string const & musicName) const
{
  return ((*this->_ressourcesPlayList.find(musicName)).second);
}

sf::Font * LibGraphic::StateCreateGame::getFont(std::string const & fontName) const
{
  return ((*this->_ressourcesFont.find(fontName)).second);
}

inline sf::String * LibGraphic::StateCreateGame::getStdToSfString(std::string const & s, sf::Font * daFont)
{
  return (new sf::String(s, *daFont));
}

