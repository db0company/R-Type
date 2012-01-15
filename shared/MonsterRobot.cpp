#ifdef _WIN32
# include "stdafx.h"
#endif
#include <iostream>
#include "DefineExportMonster.hpp"
#include "MonsterBase.hpp"

MonsterBase::MonsterBase()
{
  this->MType = 3;
  movFlag = 10;
  movDir = RIGHTMOV;
  this->launchFire = 0;
}

MonsterBase::~MonsterBase()
{

}

void		MonsterBase::moveNextPos()
{
  if (movDir == RIGHTMOV)
    {
      if (movFlag == 20)
	{
	  movDir = LEFTMOV;
	  return ;
	}
      pos.x -= 4;
      pos.y += 6;
      movFlag++;
    }
  else
    {
      if (movFlag == 0)
	{
	  movDir = RIGHTMOV;
	  return ;
	}
      pos.x -= 4;
      pos.y -= 6;
      movFlag--;
    }
}

bool		MonsterBase::wantFire()
{
  if (this->launchFire == 38)
    {
      this->launchFire = 0;
      return (true);
    }
  this->launchFire++;
  return (false);
}

extern "C"
{
#ifdef _WIN32
  LIBMONSTER_API IObject	 *getMonsterBase()
#else
   IObject	 *getMonsterBase()
#endif /* _WIN32 */
  {
    return (new MonsterBase);
  }
}
