#ifdef _WIN32
# include "stdafx.h"
#endif
#include <iostream>
#include "DefineExportMonster.hpp"
#include "MonsterBase.hpp"

MonsterBase::MonsterBase()
{
  movFlag = 15;
  movDir = RIGHTMOV;
}

MonsterBase::~MonsterBase()
{

}

void		MonsterBase::moveNextPos()
{
  if (movDir == RIGHTMOV)
    {
      if (movFlag == 30)
	{
	  movDir = LEFTMOV;
	  return ;
	}
      pos.x -= 5;
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
      pos.x -= 5;
      pos.y -= 5;
      movFlag--;
    }
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
