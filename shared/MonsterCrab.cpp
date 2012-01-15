#ifdef _WIN32
# include "stdafx.h"
#endif
#include <iostream>
#include "DefineExportMonster.hpp"
#include "MonsterBase.hpp"

MonsterBase::MonsterBase()
{
  this->MType = 4;
  movFlag = 7;
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
      if (movFlag == 15)
	{
	  movDir = LEFTMOV;
	  return ;
	}
      pos.x -= 3;
      pos.y += 5;
      movFlag++;
    }
  else
    {
      if (movFlag == 0)
	{
	  movDir = RIGHTMOV;
	  return ;
	}
      pos.x -= 7;
      pos.y -= 5;
      movFlag--;
    }
}

bool		MonsterBase::wantFire()
{
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
