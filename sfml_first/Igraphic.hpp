#ifndef IGRAPH_H_
#define IGRAPH_H_

#include <list>
#include "Case.hh"

namespace LibGraphic
{
  enum Event
    {
      __EVENT_NONE,
      __EVENT_UP,
      __EVENT_DOWN,
      __EVENT_LEFT,
      __EVENT_RIGHT,
      __EVENT_MOUSE_LEFT,
      __EVENT_MOUSE_RIGHT,
      __EVENT_BOOST,
      __EVENT_SHOOT1,
      __EVENT_SHOOT2,
      __EVENT_KEYN,
      __EVENT_QUIT
    };

  class IGraphic
  {
  public:
    virtual ~IGraphic() {};
    virtual bool init() = 0;
    virtual Event getEvent() = 0;
    virtual void quit() = 0;
    virtual void clean() = 0;
    virtual void draw() = 0;
  };
}

#endif // !IGRAPH
