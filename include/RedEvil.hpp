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
#endif	// REDEVIL_H_
