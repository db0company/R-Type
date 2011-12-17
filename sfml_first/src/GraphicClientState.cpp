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
      }
    default: break;
    }
}
