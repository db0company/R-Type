#include "StateRoomList.hpp"
#include "Language.hpp"

extern LibGraphic::Volume gVolume;
extern LibGraphic::Language language;

LibGraphic::StateRoomList::StateRoomList(std::map<std::string const, GraphicRessource *> const & ressourcesSprite,
						   std::map<std::string const, MyMusic *> const & ressourcesPlayList,
						   std::map<std::string const, MySound *> const & ressourcesSounds,
						   std::map<std::string const, sf::Font *> const & ressourcesFont,
						   sf::RenderWindow & app):
  _ressourcesSprite(ressourcesSprite), _ressourcesPlayList(ressourcesPlayList),
  _ressourcesSounds(ressourcesSounds), _ressourcesFont(ressourcesFont),
  _app(app)
{
  this->_currentButton = BUTTON_JOINCREATE_JOIN;
  this->_nextState = UNKNOWN_STATE;
}

LibGraphic::StateRoomList::~StateRoomList()
{
}

bool LibGraphic::StateRoomList::init()
{
  return true;
}

void LibGraphic::StateRoomList::draw()
{
  sf::String *Back;
  sf::String *Join;
  sf::String *Create;

  sf::Sprite &ButtonBack = this->getSprite("BasicButton");
  sf::Sprite &ButtonJoin = this->getSprite("BasicButton");
  sf::Sprite &ButtonCreate = this->getSprite("BasicButton");

  sf::Sprite &background = this->getSprite("StartMenuBackground");
  sf::Sprite &menu = this->getSprite("RoomListMenu");
  sf::Sprite &menu_haut = this->getSprite("RoomList-haut");
  sf::Sprite &menu_bas = this->getSprite("RoomList-bas");
  sf::Sprite &menu_gauche = this->getSprite("RoomList-gauche");
  sf::Sprite &menu_droite = this->getSprite("RoomList-droite");
  sf::Sprite &menu_coins = this->getSprite("RoomList-coins");
  sf::Sprite &menu_diago = this->getSprite("OptionsMenu-diago");

  sf::Sprite &Cursor = this->getSprite("RoomListCursor");
  sf::Sprite &SelectedGame = this->getSprite("RoomListSelectedGame");

  if (language == ENGLISH)
    Back = this->getStdToSfString("Back", this->getFont("StartFontF"));
  else
    Back = this->getStdToSfString("Retour", this->getFont("StartFontF"));
  if (language == ENGLISH)
    Join = this->getStdToSfString("Join", this->getFont("StartFontF"));
  else
    Join = this->getStdToSfString("Rejoindre", this->getFont("StartFontF"));
  if (language == ENGLISH)
    Create = this->getStdToSfString("Create", this->getFont("StartFontF"));
  else
    Create = this->getStdToSfString("Creer", this->getFont("StartFontF"));

  menu.SetPosition(245, 210);
  menu_bas.SetPosition(245, 875);
  menu_haut.SetPosition(245 + 61, 210);
  menu_droite.SetPosition(245 + 1188, 210);
  menu_gauche.SetPosition(245, 210 + 52);
  menu_diago.SetPosition(245, 210);
  menu_coins.SetPosition(192, 145);
  menu.SetColor(sf::Color(255, 255, 255, 210));
  this->_app.Draw(background);
  this->_app.Draw(menu);
  this->_app.Draw(menu_diago);
  this->_app.Draw(menu_bas);
  this->_app.Draw(menu_gauche);
  this->_app.Draw(menu_droite);
  this->_app.Draw(menu_haut);
  this->_app.Draw(menu_coins);
  this->_app.Draw(menu_diago);

  Cursor.SetPosition(293, 335);
  this->_app.Draw(Cursor);

  // ButtonBack.SetPosition(720, 730);
  // ButtonBack.SetRotation(180);
  // this->_app.Draw(ButtonBack);
  // if (language == ENGLISH)
  //   Back->SetPosition(565, 694);
  // else
  //   Back->SetPosition(540, 694);
  // Back->SetScale(1, 0.8);
  // Back->SetColor(sf::Color(255,255,0, 255));
  // if (this->_currentButton != BUTTON_JOINCREATE_BACK)
  //   Back->SetColor(sf::Color(255,255,255, 205));
  // this->_app.Draw(*Back);
}

LibGraphic::Event LibGraphic::StateRoomList::gereEvent()
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

LibGraphic::eStates LibGraphic::StateRoomList::getNextState()
{
  return this->_nextState;
}

void LibGraphic::StateRoomList::cursorMenuPos(const sf::Event & Event)
{
}

sf::Sprite & LibGraphic::StateRoomList::getSprite(std::string const & spriteName) const
{
  return ((*this->_ressourcesSprite.find(spriteName)).second->_sprite);
}

LibGraphic::MyMusic * LibGraphic::StateRoomList::getMusic(std::string const & musicName) const
{
  return ((*this->_ressourcesPlayList.find(musicName)).second);
}

sf::Font * LibGraphic::StateRoomList::getFont(std::string const & fontName) const
{
  return ((*this->_ressourcesFont.find(fontName)).second);
}

inline sf::String * LibGraphic::StateRoomList::getStdToSfString(std::string const & s, sf::Font * daFont)
{
  return (new sf::String(s, *daFont));
}

