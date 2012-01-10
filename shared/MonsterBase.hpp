#ifndef __MONSTERBASE_HPP__
# define __MONSTERBASE_HPP__

# include "DefineExportMonster.hpp"
# include "AObject.hpp"

# ifdef _WIN32
class	LIBMONSTER_API MonsterBase : public IObject
# else
class	MonsterBase : public IObject
# endif // _WIN32
{
 private:
 public:
  MonsterBase();
  virtual ~MonsterBase();
};
#endif
