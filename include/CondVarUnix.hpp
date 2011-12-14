#ifndef _CONDVAR_HPP_
# define _CONDVAR_HPP_

#include <pthread.h>
#include "IMutex.hpp"
#include "ICondVar.hpp"

class CondVarUnix : public ICondVar
{
  pthread_cond_t	_Cond;
  IMutex		*_m;

public:
  CondVarUnix(IMutex *m);
  virtual ~CondVarUnix();

  virtual bool wait();
  virtual void signal();
  virtual void broadcast();
};


#endif
