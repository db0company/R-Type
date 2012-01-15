#ifndef		__BULLET_HPP__
# define	__BULLET_HPP__

# include "Position.hpp"
# include "enum.h"
# include "AObject.hpp"

class		Bullet : public AObject
{
private:
  eGroup	group;
  bool		toDestroy;
public:
  Bullet(Position p, eGroup g);
  ~Bullet();
  eGroup		getGroup()const;
  void	setDestroy();
  bool	getDestroy();
};

#endif		/*__BULLET_HPP__*/
