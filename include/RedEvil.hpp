#ifndef REDEVIL_H_
# define REDEVIL_H_

#define REDEVIL_SIZE_X 33
#define REDEVIL_SIZE_Y 35
#define REDEVIL_NB_SPRITE 8

#include "AMonsterMovement.hpp"


// Les Monstres :

// RedEvil 0
// MasterShip 1
// GreenEyes 2
//// EvilRobot 3
// SpaceCrab 4


// Autre : RedEvil

namespace LibGraphic
{
  class	RedEvil : public AMonsterMovement
  {
  private:
    RedEvil();
  public:
    RedEvil(sf::RenderWindow &, sf::Sprite &);
    virtual ~RedEvil(void){}

  private:

  };
}

#define MASTER_SHIP_NB_SPRITE 8 // 0 a 7
#define MASTER_SHIP_X 33
#define MASTER_SHIP_Y 32

namespace LibGraphic
{
  class	MasterShip : public AMonsterMovement
  {
  private:
    MasterShip();
  public:
    MasterShip(sf::RenderWindow &, sf::Sprite &);
    virtual ~MasterShip(void){}

  private:

  };
}


#define GREEN_EYES_NB_SPRITE  6 // 0 a 5
#define GREEN_EYES_X 17
#define GREEN_EYES_Y 16

namespace LibGraphic
{
  class	GreenEyes : public AMonsterMovement
  {
  private:
    GreenEyes();
  public:
    GreenEyes(sf::RenderWindow &, sf::Sprite &);
    virtual ~GreenEyes(void){}

  private:

  };
}

#define EVILROBOT_X 33
#define EVILROBOT_Y 34
#define EVILROBOT_NB_SPRITE 4

namespace LibGraphic
{
  class	EvilRobot : public AMonsterMovement
  {
  private:
    EvilRobot();
  public:
    EvilRobot(sf::RenderWindow &, sf::Sprite &);
    virtual ~EvilRobot(void){}

  private:

  };
}

#define SPACECRAB_X 33
#define SPACECRAB_Y 34
#define SPACECRAB_NB_SPRITE 4

namespace LibGraphic
{
  class	SpaceCrab : public AMonsterMovement
  {
  private:
    SpaceCrab();
  public:
    SpaceCrab(sf::RenderWindow &, sf::Sprite &);
    virtual ~SpaceCrab(void){}

  private:

  };
}

#endif	// REDEVIL_H_
