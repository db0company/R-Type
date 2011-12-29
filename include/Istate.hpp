#ifndef ISTATE_H
# define ISTATE_H

#include "IGraphic.hpp"

namespace LibGraphic
{

  class IState
  {
  public:
    virtual ~IState(){};
    virtual bool init() = 0;
    virtual void draw() = 0;
    virtual Event gereEvent() = 0;
  };

}

#endif //ISTATE_H
