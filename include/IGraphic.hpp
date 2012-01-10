#ifndef IGRAPH_H_
# define IGRAPH_H_

#include <list>

namespace LibGraphic
{
  enum Event
    {
      EVENT_CHANGE_STATE,
      EVENT_START_PLAY,
      EVENT_ROOMLIST_REFRESH,
      EVENT_ROOMLIST_JOIN,
      EVENT_ROOMLIST_SPECTATE,
      EVENT_CREATE_CREATE,
      EVENT_ROOM_CHAT,
      EVENT_ROOM_START,
      EVENT_ROOM_QUIT,
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
