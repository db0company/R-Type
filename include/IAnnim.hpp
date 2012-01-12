#ifndef IANNIM_H
# define IANNIM_H

namespace LibGraphic
{

  class IAnnim
  {
  public:
    virtual ~IAnnim() {};
    virtual void play() = 0;
    virtual void pause() = 0;
    virtual void stop() = 0;
  };

}

#endif
