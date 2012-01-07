#ifndef ISTATE_H
# define ISTATE_H

#include <string>
#include "MyMusic.hpp"
#include "IGraphic.hpp"
#include "GraphicUtils.hpp"
#include "EGraphicAction.hpp"

namespace LibGraphic
{

  class IState
  {
  public:
    virtual ~IState(){};
    virtual bool init() = 0;
    virtual void draw() = 0;
    virtual Event gereEvent() = 0;
    virtual eStates getNextState() = 0;
    virtual void setNextState(eStates e) = 0;
    virtual eGraphicAction getAction() = 0;
    virtual void setAction(eGraphicAction gAction) = 0;
  public:
    virtual sf::Sprite & getSprite(std::string const &) const = 0;
    virtual MyMusic * getMusic(std::string const &) const = 0;
    virtual sf::Font * getFont(std::string const &) const = 0;
  };

}

#endif //ISTATE_H
