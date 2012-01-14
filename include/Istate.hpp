#ifndef ISTATE_H
# define ISTATE_H

#include <string>
#include "MyMusic.hpp"
#include "IGraphic.hpp"
#include "GraphicUtils.hpp"
#include "EGraphicAction.hpp"

namespace LibGraphic
{

  class AState
  {
  public:
    AState(std::map<std::string const, GraphicRessource *>
	   const & ressourcesSprite,
	   std::map<std::string const, MyMusic *> const & ressourcesPlayList,
	   std::map<std::string const, MySound *> const & ressourcesSounds,
	   std::map<std::string const, sf::Font *> const & ressourcesFont,
	   sf::RenderWindow & app):
  _ressourcesSprite(ressourcesSprite), _ressourcesPlayList(ressourcesPlayList),
  _ressourcesSounds(ressourcesSounds), _ressourcesFont(ressourcesFont),
  _app(app){}
    virtual ~AState(){};
    virtual bool init() = 0;
    virtual void draw() = 0;
    virtual Event gereEvent() = 0;
    virtual eStates getNextState() = 0;

  public:
    virtual sf::Sprite & getSprite(std::string const &spriteName) const
    {
      return ((*this->_ressourcesSprite.find(spriteName)).second->_sprite);
    }
    virtual MyMusic * getMusic(std::string const &musicName) const
    {
      return ((*this->_ressourcesPlayList.find(musicName)).second);
    }
    virtual sf::Font * getFont(std::string const &fontName) const
    {
      return ((*this->_ressourcesFont.find(fontName)).second);
    }
    virtual sf::String * getStdToSfString(std::string const & s, sf::Font * daFont)
    {
      return (new sf::String(s, *daFont));
    }

  protected:
    std::map<std::string const, GraphicRessource *>
    const & _ressourcesSprite;
    std::map<std::string const, MyMusic *> const & _ressourcesPlayList;
    std::map<std::string const, MySound *> const & _ressourcesSounds;
    std::map<std::string const, sf::Font *> const & _ressourcesFont;
    sf::RenderWindow & _app;
  };

}

#endif //ISTATE_H
