#ifndef __MONSTERBASE_HPP__
# define __MONSTERBASE_HPP__

# include "DefineExportMonster.hpp"
# include "Monster.hpp"

# ifdef _WIN32
class	LIBMONSTER_API MonsterBase : public MonsterBase
# else
class	MonsterBase : public Monster
# endif // _WIN32
{
 private:
 public:
  MonsterBase();
  virtual ~MonsterBase();
};
#endif
