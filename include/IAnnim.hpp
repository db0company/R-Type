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

    virtual Coord const &getCoord() const = 0;
    virtual void setCoord(Coord const &) = 0;
    virtual void setCoord(unsigned int, unsigned int) = 0;
    virtual void setScale(float, float) = 0;

    virtual float getTimer() const = 0;
    virtual void setTimer(float) = 0;
  };

}

#endif
