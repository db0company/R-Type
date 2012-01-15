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
  std::string	owner;
public:
  Bullet(Position p, eGroup g, const std::string& ow);
  ~Bullet();
  eGroup		getGroup()const;
  void	setDestroy();
  bool	getDestroy();
  void	setOwner(const std::string& ow);
  const std::string& getOwner()const;
};

#endif		/*__BULLET_HPP__*/
