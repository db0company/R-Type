#include "RedEvil.hpp"

namespace LibGraphic
{
  RedEvil::RedEvil(sf::RenderWindow &app, sf::Sprite &sprite) :
    AMonsterMovement(app, sprite, REDEVIL_SIZE_X, REDEVIL_SIZE_Y, REDEVIL_NB_SPRITE)
  {
  }
}

namespace LibGraphic
{
  MasterShip::MasterShip(sf::RenderWindow &app, sf::Sprite &sprite) :
    AMonsterMovement(app, sprite, MASTER_SHIP_X, MASTER_SHIP_Y, MASTER_SHIP_NB_SPRITE)
  {
  }
}

namespace LibGraphic
{
  GreenEyes::GreenEyes(sf::RenderWindow &app, sf::Sprite &sprite) :
    AMonsterMovement(app, sprite, GREEN_EYES_X, GREEN_EYES_Y, GREEN_EYES_NB_SPRITE)
  {
  }
}

namespace LibGraphic
{
  EvilRobot::EvilRobot(sf::RenderWindow &app, sf::Sprite &sprite) :
    AMonsterMovement(app, sprite, EVILROBOT_X, EVILROBOT_Y, EVILROBOT_NB_SPRITE)
  {
  }
}

namespace LibGraphic
{
  SpaceCrab::SpaceCrab(sf::RenderWindow &app, sf::Sprite &sprite) :
    AMonsterMovement(app, sprite, SPACECRAB_X, SPACECRAB_Y, SPACECRAB_NB_SPRITE)
  {
  }
}
