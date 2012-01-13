#ifndef PLAYERMOVEMENT_H
# define PLAYERMOVEMENT_H

#include "GraphicUtils.hpp"
#include "Sfml.hpp"
#include "SpriteInfo.hpp"

namespace LibGraphic
{

  class PlayerMovement
  {

  public:
    PlayerMovement(sf::RenderWindow &, sf::Sprite &, eShipColor id = BLUESHIP);
    ~PlayerMovement();

  public:
    void move(const sf::Event &);
    void draw();

  public:
    Coord const & getCoord() const;
    void setCoord(Coord const & coord);
    int getX(void) const;
    int getY(void) const;

    eShipColor getId() const;
    void setId(eShipColor id);

    eMovement getLastMove() const;

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
    eMovement _lastMove;

  };

}

#endif
