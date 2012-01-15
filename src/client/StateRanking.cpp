#include <sstream>
#include "StateRanking.hpp"
#include "Language.hpp"

extern LibGraphic::Volume gVolume;
extern LibGraphic::Language language;
extern bool errorToPrint;

std::string LibGraphic::StateRanking::stringOfInt(int v)
{
  std::stringstream ss;
  std::string s;

  ss << v;
  ss >> s;
  return s;
}

LibGraphic::StateRanking::StateRanking(std::map<std::string const, GraphicRessource *> const & ressourcesSprite,
				       std::map<std::string const, MyMusic *> const & ressourcesPlayList,
				       std::map<std::string const, MySound *> const & ressourcesSounds,
				       std::map<std::string const, sf::Font *> const & ressourcesFont,
				       sf::RenderWindow & app):
  AState(ressourcesSprite, ressourcesPlayList, ressourcesSounds,
	 ressourcesFont, app)
{
  this->_currentButton = BUTTON_RANKING_BACK;
  this->_nextState = START;
}

LibGraphic::StateRanking::~StateRanking()
{
}

bool LibGraphic::StateRanking::init()
{
  return true;
}

void LibGraphic::StateRanking::draw()
{
  sf::Sprite &back = this->getSprite("StartMenuBackground");
  sf::Sprite &menu = this->getSprite("OptionsMenu");
  sf::Sprite &menu_haut = this->getSprite("OptionsMenu-haut");
  sf::Sprite &menu_bas = this->getSprite("OptionsMenu-bas");
  sf::Sprite &menu_gauche = this->getSprite("OptionsMenu-gauche");
  sf::Sprite &menu_droite = this->getSprite("OptionsMenu-droite");
  sf::Sprite &menu_coins = this->getSprite("OptionsMenu-coins");
  sf::Sprite &menu_diago = this->getSprite("OptionsMenu-diago");

  sf::Sprite &Button = this->getSprite("BasicButton");

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

  Button.SetPosition(1100, 730);
  Button.SetRotation(180);
  this->_app.Draw(Button);
  Button.SetRotation(180);

  drawText();
  drawRank();
}

void LibGraphic::StateRanking::drawRank()
{
  sf::String *tmp;

  unsigned int nb = 0;
  for (std::list<std::string>::iterator it = this->_rank.begin();
       it != this->_rank.end() && nb < 5;
       ++it, ++nb)
    {
      tmp = this->getStdToSfString("#" + stringOfInt(nb) + " " + (*it),
      				   this->getFont("StartFontF"));
      tmp->SetPosition(550, 340 + (70 * nb));
      tmp->SetScale(0.6, 0.6);
      this->_app.Draw(*tmp);
    }
}

void LibGraphic::StateRanking::drawText()
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
  if (this->_currentButton != BUTTON_RANKING_BACK)
    tmp->SetColor(sf::Color(255,255,255, 205));
  this->_app.Draw(*tmp);
}

LibGraphic::Event LibGraphic::StateRanking::gereEvent()
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
	    case 0:
	      {
		this->_nextState = START;
		return EVENT_CHANGE_STATE;
	      }
	    }
	}
    }
  return EVENT_NONE;
}

LibGraphic::eStates LibGraphic::StateRanking::getNextState()
{
  return this->_nextState;
}

std::list<std::string> & LibGraphic::StateRanking::getRankingList()
{
  return this->_rank;
}
