#include "StateRoom.hpp"
#include "Language.hpp"

extern LibGraphic::Volume gVolume;
extern LibGraphic::Language language;

LibGraphic::StateRoom::StateRoom(std::map<std::string const, GraphicRessource *> const & ressourcesSprite,
						   std::map<std::string const, MyMusic *> const & ressourcesPlayList,
						   std::map<std::string const, MySound *> const & ressourcesSounds,
						   std::map<std::string const, sf::Font *> const & ressourcesFont,
						   sf::RenderWindow & app):
  _ressourcesSprite(ressourcesSprite), _ressourcesPlayList(ressourcesPlayList),
  _ressourcesSounds(ressourcesSounds), _ressourcesFont(ressourcesFont),
  _app(app)
{
  this->_currentButton = BUTTON_ROOM_CHAT;
  this->_nextState = UNKNOWN_STATE;
}

LibGraphic::StateRoom::~StateRoom()
{
}

bool LibGraphic::StateRoom::init()
{
  return true;
}

void LibGraphic::StateRoom::draw()
{
  sf::Sprite &back = this->getSprite("StartMenuBackground");

  this->_app.Draw(back);

  this->drawText();
}

void LibGraphic::StateRoom::drawText()
{
}

LibGraphic::Event LibGraphic::StateRoom::gereEvent()
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
		if (this->_currentButton == BUTTON_ROOM_QUIT)
		  {
		    this->_nextState = ROOM;
		    return EVENT_CHANGE_STATE;
		  }
		break;
	      }
	    default : break;
	    }
	}
      cursorMenuPos(Event);
    }
  return EVENT_NONE;
}

LibGraphic::eStates LibGraphic::StateRoom::getNextState()
{
  return this->_nextState;
}

void LibGraphic::StateRoom::cursorMenuPos(const sf::Event & Event)
{
  const sf::Input & Input = this->_app.GetInput();
  float JoystickPOV = Input.GetJoystickAxis(0, sf::Joy::AxisPOV);

  if ((JoystickPOV == -1 && Event.Type != sf::Event::KeyPressed) ||
      this->Clock.GetElapsedTime() < 0.1)
    return;
  switch (this->_currentButton)
    {
    default : break;
    }
  this->Clock.Reset();
}

sf::Sprite & LibGraphic::StateRoom::getSprite(std::string const & spriteName) const
{
  return ((*this->_ressourcesSprite.find(spriteName)).second->_sprite);
}

LibGraphic::MyMusic * LibGraphic::StateRoom::getMusic(std::string const & musicName) const
{
  return ((*this->_ressourcesPlayList.find(musicName)).second);
}

sf::Font * LibGraphic::StateRoom::getFont(std::string const & fontName) const
{
  return ((*this->_ressourcesFont.find(fontName)).second);
}

inline sf::String * LibGraphic::StateRoom::getStdToSfString(std::string const & s, sf::Font * daFont)
{
  return (new sf::String(s, *daFont));
}
