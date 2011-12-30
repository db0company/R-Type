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
  sf::String *tmp;
  sf::String *Back = this->getStdToSfString("Back", this->getFont("StartFontF"));
  sf::String *Ok = this->getStdToSfString("Ok", this->getFont("StartFontF"));

  sf::Sprite &back = this->getSprite("StartMenuBackground");
  // sf::Sprite &back = this->getSprite("OptionsBackground");
  sf::Sprite &menu = this->getSprite("OptionsMenu");
  sf::Sprite &menu_haut = this->getSprite("OptionsMenu-haut");
  sf::Sprite &menu_bas = this->getSprite("OptionsMenu-bas");
  sf::Sprite &menu_gauche = this->getSprite("OptionsMenu-gauche");
  sf::Sprite &menu_droite = this->getSprite("OptionsMenu-droite");
  sf::Sprite &menu_coins = this->getSprite("OptionsMenu-coins");
  sf::Sprite &menu_diago = this->getSprite("OptionsMenu-diago");

  sf::Sprite &NameArea = this->getSprite("TextArea");

  sf::Sprite &ButtonBack = this->getSprite("BasicButton");
  sf::Sprite &ButtonOk = this->getSprite("BasicButton");
  sf::Sprite &testBoxE = this->getSprite("BoxEmpty");
  sf::Sprite &testBoxC = this->getSprite("BoxChecked");

  sf::Sprite &English = this->getSprite("English");
  sf::Sprite &Francais = this->getSprite("Francais");

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

  NameArea.SetPosition(740, 360);
  tmp = this->getStdToSfString(this->test, this->getFont("StartFontF"));
  //  tmp->SetText(this->test);
  tmp->SetPosition(750, 360);
  tmp->SetColor(sf::Color(0, 0, 0, 255));
  this->_app.Draw(NameArea);
  this->_app.Draw(*tmp);

  English.SetPosition(900, 600);
  Francais.SetPosition(1000, 600);
  this->_app.Draw(Francais);
  this->_app.Draw(English);


  ButtonBack.SetPosition(720, 730);
  ButtonBack.SetRotation(180);
  this->_app.Draw(ButtonBack);
  Back->SetPosition(565, 694);
  Back->SetColor(sf::Color(0, 0, 0, 255));
  Back->SetText("Back");
  Back->SetScale(1, 0.8);
  this->_app.Draw(*Back);
  Ok->SetPosition(965, 694);
  Ok->SetColor(sf::Color(0, 0, 0, 255));
  Ok->SetText("Ok");
  Ok->SetScale(1, 0.8);
  ButtonOk.SetPosition(1100, 730);
  this->_app.Draw(ButtonOk);
  this->_app.Draw(*Ok);
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
		this->test = this->test.substr(0, this->test.length() - 1);
		break;
	      }
	    default: break;
	    }
	}
      else if (Event.Type == sf::Event::TextEntered)
	{
	  if (Event.Text.Unicode > 20 && Event.Text.Unicode < 128)
	    {
	      if (test.size() <= 10)
		this->test += static_cast<char>(Event.Text.Unicode);
	    }
	}
    }
  return EVENT_NONE;
}

LibGraphic::eStates LibGraphic::StateOptions::getNextState()
{
  return this->_nextState;
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


