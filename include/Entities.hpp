#ifndef		__ENTITIES_HPP__
# define	__ENTITIES_HPP__

#include "AObject.hpp"

class		Entities : public AObject
{
protected:
  int		life;
  int		power;
public:
  Entities();
  ~Entities();
  Entities(const Entities& old);
  Entities	&operator=(const Entities& old);
  void		changeLife(int);
};

#endif		/*__ENTITIES_HPP__*/
