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
  virtual void		moveNextPos() = 0;
  void		setMType(int type);
  int		getMType()const;
  void		setMId(int id);
  int		getMId()const;
private:
  int		MType;
  int		MId;
};

#endif		/*__MONSTER_HPP__*/
