#ifndef REDEVIL_H_
# define REDEVIL_H_

#define REDEVIL_SIZE_X 33
#define REDEVIL_SIZE_Y 35
#define REDEVIL_NB_SPRITE 8

#include "AMonsterMovement.hpp"

namespace LibGraphic
{
  class	RedEvil : public AMonsterMovement
  {
  private:
    RedEvil();
  public:
    RedEvil(sf::RenderWindow &, sf::Sprite &);
    virtual ~RedEvil(void);

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
    virtual ~MasterShip(void);

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
    virtual ~GreenEyes(void);

  private:

  };
}

#endif	// REDEVIL_H_
