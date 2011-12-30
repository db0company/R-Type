#ifndef IGRAPH_H_
# define IGRAPH_H_

#include <list>

namespace LibGraphic
{
  enum Event
    {
      EVENT_CHANGE_STATE,
      EVENT_NONE,
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
