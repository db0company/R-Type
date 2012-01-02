#ifndef		__MONSTER_HPP__
# define	__MONSTER_HPP__

#include "Entities.hpp"

class		Monster : public Entities
{
public:
  Monster();
  ~Monster();
  void		moveNextPos();
private:

};

#endif		/*__MONSTER_HPP__*/
