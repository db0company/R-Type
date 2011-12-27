#ifndef IGRAPH_H_
# define IGRAPH_H_

#include <list>

namespace LibGraphic
{
  enum Event
    {
      EVENT_NONE,
      EVENT_UP,
      EVENT_DOWN,
      EVENT_LEFT,
      EVENT_RIGHT,
      EVENT_MOUSE_LEFT,
      EVENT_MOUSE_RIGHT,
      EVENT_BOOST,
      EVENT_SHOOT1,
      EVENT_SHOOT2,
      EVENT_KEYN,
      EVENT_QUIT
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
