#ifndef __MONSTERBASE_HPP__
# define __MONSTERBASE_HPP__

# include "DefineExportMonster.hpp"
# include "AObject.hpp"
# include "Monster.hpp"

enum eMovDir
  {
    LEFTMOV,
    RIGHTMOV
  };

# ifdef _WIN32
class	LIBMONSTER_API MonsterBase : public AObject
# else
class	MonsterBase : public Monster
# endif // _WIN32
{
 private:
  int	movFlag;
  int	movDir;
 public:
  MonsterBase();
  virtual ~MonsterBase();
  virtual void	moveNextPos();
};
#endif
