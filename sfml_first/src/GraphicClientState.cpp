#include "GraphicClientState.hpp"

LibGraphic::GraphicClientState::GraphicClientState(std::map<std::string const, const GraphicRessource *> const & ressourcesSprite,
						   std::map<std::string const, MyMusic *> const & ressourcesPlayList,
						   std::map<std::string const, MySound *> const & ressourcesSounds,
						   sf::RenderWindow & app):
  _ressourcesSprite(ressourcesSprite), _ressourcesPlayList(ressourcesPlayList), _ressourcesSounds(ressourcesSounds), _app(app)
{
}

LibGraphic::GraphicClientState::~GraphicClientState(void)
{
}

sf::Sprite const & LibGraphic::GraphicClientState::getSprite(std::string const & spriteName) const
{
  return ((*this->_ressourcesSprite.find(spriteName)).second->_sprite);
}

LibGraphic::MyMusic * LibGraphic::GraphicClientState::getMusic(std::string const & musicName) const
{
  return ((*this->_ressourcesPlayList.find(musicName)).second);
}

void LibGraphic::GraphicClientState::draw(eStates scene)
{
  switch (scene)
    {
    case START:
      {
	this->_app.Draw(this->getSprite("StartBackground"));
	MyMusic * song = this->getMusic("StartMusic");
	if (song->GetMusicState() == sf::Music::Stopped ||
	    song->GetMusicState() == sf::Music::Paused)
	  song->PlayMusic();
	break;
      }
    case ROOMLIST:
      {
	this->_app.Draw(this->getSprite("StartMenu"));
	MyMusic * song = this->getMusic("StartMusic");
	if (song->GetMusicState() == sf::Music::Stopped ||
	    song->GetMusicState() == sf::Music::Paused)
	  song->PlayMusic();
	break;
      }
    default: break;
    }
}

LibGraphic::Event LibGraphic::GraphicClientState::eventStart(eStates & scene)
{
  sf::Event Event;

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
		scene = ROOMLIST;
		break;
	      }
	    default:
	      break;
	    }
	}
    }
  return LibGraphic::EVENT_NONE;
}

LibGraphic::Event LibGraphic::GraphicClientState::getEventFromState(__attribute__((unused)) eStates & scene)
{
  switch (scene)
    {
    case START: return this->eventStart(scene);
    case ROOMLIST: return this->eventStart(scene);
    default: break;
    }
  return LibGraphic::EVENT_NONE;
}
