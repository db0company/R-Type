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
  menu.SetSubRect(sf::IntRect(841, 311, 841 *2, 311 * 2));
  this->_app.Draw(menu);
  menu.SetColor(sf::Color(255, 255, 255, 110));
  menu.SetSubRect(sf::IntRect(0, 311, 841, 311 * 2));
  this->_app.Draw(menu);
  tmp = this->getStdToSfString("PLAY", this->getFont("StartFontF"));
  tmp->SetPosition(320, 455);
  tmp->Scale(2.3, 2.3);
  tmp->SetColor(sf::Color(255,255,255, 220));
  this->_app.Draw(*tmp);
  MyMusic * song = this->getMusic("StartMusic");
  if (song->GetMusicState() == sf::Music::Stopped ||
      song->GetMusicState() == sf::Music::Paused)
    song->PlayMusic();
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
	    case sf::Key::Escape:
	      //return LibGraphic::__EVENT_QUIT;
	      {
		this->_app.Close();
		exit(EXIT_SUCCESS);
	      }
	    case sf::Key::P:
	      {
		break;
	      }
	    default: break;
	    }
	}
    }
  bool Apressed = Input.IsJoystickButtonDown(0, 0);
  if (Apressed)
  {
    this->_app.Close();
    exit(EXIT_SUCCESS);
  }
  bool Bpressed = Input.IsJoystickButtonDown(0, 1);
  bool Xpressed = Input.IsJoystickButtonDown(0, 2);
  bool Ypressed = Input.IsJoystickButtonDown(0, 3);

  return EVENT_NONE;
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
