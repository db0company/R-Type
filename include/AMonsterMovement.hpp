#ifndef AMONSTERMOVEMENT_H_
# define AMONSTERMOVEMENT_H_

#include "GraphicUtils.hpp"
#include "Sfml.hpp"
#include "IAnnim.hpp"

namespace LibGraphic
{

  class	AMonsterMovement
  {
    AMonsterMovement(void);
  public:
    AMonsterMovement(sf::RenderWindow &, sf::Sprite &, unsigned int w,
		     unsigned int h, unsigned int nbSprite,
		     unsigned int nbPlay = 0);
    virtual ~AMonsterMovement(void);

    virtual void play(void);
    virtual void pause(void);
    virtual void stop(void);

  public:
    virtual Coord const &getCoord(void) const;
    virtual void setCoord(unsigned int, unsigned int);
    virtual void setScale(float, float);

    virtual float getTimet(void) const;
    virtual void setTimer(float);

  private:
    sf::RenderWindow &_app;
    Coord _coord;
    sf::Clock _clock;
    float _clockVal;
    sf::Sprite &_sprite;
    unsigned int _width;
    unsigned int _height;
    unsigned int _nbSprite;
    unsigned int _nbPlay;
    unsigned int _currentSprite;
  };

}
#endif	// AMONSTERMOVEMENT_H_
