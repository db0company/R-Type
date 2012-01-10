#ifdef _WIN32
# include "stdafx.h"
#endif
#include "DefineExportMonster.hpp"
#include "MonsterBase.hpp"

MonsterBase::MonsterBase()
{

}

MonsterBase::~MonsterBase()
{

}

extern "C"
{
#ifdef _WIN32
  LIBMONSTER_API IObject	 *getMonsterBase()
#else
    Monster	 *getMonsterBase()
#endif /* _WIN32 */
  {
    return (new MonsterBase);
  }
}
