#ifndef PLAYERMOVEMENT_H
# define PLAYERMOVEMENT_H

#include "GraphicUtils.hpp"
#include "Sfml.hpp"
#include "SpriteInfo.hpp"

#define SHIPSPEED 8

namespace LibGraphic
{

  class PlayerMovement
  {

  public:
    PlayerMovement(sf::RenderWindow &, sf::Sprite &);
    ~PlayerMovement();

  public:
    void move(const sf::Event &);
    void draw();

  public:
    Coord const & getCoord() const;
    void setCoord(Coord const & coord);

    eShipColor getId() const;
    void setId(eShipColor id);

  private:
    void UpPlayer(bool LeftKeyDown, bool RightKeyDown, float JoystickX);
    void DownPlayer(bool LeftKeyDown, bool RightKeyDown, float JoystickX);

   private:
    sf::RenderWindow & _app;
    sf::Sprite & _sprite;
    sf::Clock _clock;
    Coord _coord;
    eShipRotation _rotate;
    eShipColor _id;
  };

}

#endif
