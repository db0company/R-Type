#ifndef		__BULLET_HPP__
# define	__BULLET_HPP__

# include "Position.hpp"
# include "enum.h"

class		Bullet
{
private:
  Position	pos;
  eGroup	group;
public:
  Bullet(Position p, eGroup g);
  ~Bullet();
  const Position&	getPos()const;
  void			setPos(const Position& p);
  eGroup		getGroup()const;
};

#endif		/*__BULLET_HPP__*/
