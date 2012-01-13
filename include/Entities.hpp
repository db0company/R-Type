#ifndef		__ENTITIES_HPP__
# define	__ENTITIES_HPP__

#include "enum.h"
#include "AObject.hpp"
#include "DefineExportMonster.hpp"

# ifdef _WIN32
class		LIBMONSTER_API Entities : public AObject
# else
class		Entities : public AObject
#endif
{
protected:
  int		life;
  int		power;
  eGroup	group;
public:
  Entities();
  ~Entities();
  Entities(const Entities& old);
  Entities	&operator=(const Entities& old);
  void		changeLife(int);
  eGroup	getGroup()const;
};

#endif		/*__ENTITIES_HPP__*/
