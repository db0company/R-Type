#include "RedEvil.hpp"

namespace LibGraphic
{
  RedEvil::RedEvil(sf::RenderWindow &app, sf::Sprite &sprite) :
    AMonsterMovement(app, sprite, REDEVIL_SIZE_X, REDEVIL_SIZE_Y, REDEVIL_NB_SPRITE)
  {
  }

  RedEvil::~RedEvil()
  {
  }
}
