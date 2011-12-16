#include "GraphicClientState.hpp"

LibGraphic::GraphicClientState::GraphicClientState(std::string const & state,
		       std::map<std::string const, const GraphicRessource *> const & ressourcesSprite,
		       std::map<std::string const, MyMusic *> const & ressourcesPlayList,
		       std::map<std::string const, MySound *> const & ressourcesSounds):

  _name(state), _ressourcesSprite(ressourcesSprite), _ressourcesPlayList(ressourcesPlayList), _ressourcesSounds(ressourcesSounds)
{
}

LibGraphic::GraphicClientState::~GraphicClientState(void)
{
}

std::string const & LibGraphic::GraphicClientState::getName() const
{
  return this->_name;
}

sf::Sprite const & LibGraphic::GraphicClientState::getSprite(std::string const & spriteName) const
{
  return ((*this->_ressourcesSprite.find(spriteName)).second->_sprite);
}

LibGraphic::MyMusic * LibGraphic::GraphicClientState::getMusic(std::string const & musicName) const
{
  return ((*this->_ressourcesPlayList.find(musicName)).second);
}
