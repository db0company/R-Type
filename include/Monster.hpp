#ifndef		__MONSTER_HPP__
# define	__MONSTER_HPP__

# include "Entities.hpp"
# include "DefineExportMonster.hpp"

# ifdef _WIN32
class		LIBMONSTER_API Monster : public Entities
# else
class		Monster : public Entities
# endif
{
public:
  Monster();
  ~Monster();
  void		moveNextPos();
private:

};

#endif		/*__MONSTER_HPP__*/
