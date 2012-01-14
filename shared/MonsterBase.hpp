#ifndef __MONSTERBASE_HPP__
# define __MONSTERBASE_HPP__

# include "DefineExportMonster.hpp"
# include "AObject.hpp"

enum eMovDir
  {
    LEFTMOV,
    RIGHTMOV
  };

# ifdef _WIN32
class	LIBMONSTER_API MonsterBase : public AObject
# else
class	MonsterBase : public AObject
# endif // _WIN32
{
 private:
  int	movFlag;
  int	movDir;
 public:
  MonsterBase();
  virtual ~MonsterBase();
  void	moveNextPos();
};
#endif
