#include <Windows.h>
#include "MutexWindows.hpp"
#include "CondVarWindows.hpp"

CondVarWindows::CondVarWindows(MutexWindows *m) : _m(m)
{
	InitializeConditionVariable(&this->_condvar);
}

CondVarWindows::~CondVarWindows()
{
}

CondVarWindows::CondVarWindows(CondVarWindows const &o)
{
	this->_m = o._m;
}

CondVarWindows &CondVarWindows::operator=(CondVarWindows const &o)
{
	this->_m = o._m;
	return (*this);
}

bool	CondVarWindows::wait()
{
	if (SleepConditionVariableCS(&this->_condvar, (_m)->getCS(), 0) != 0)
	{
		return (true);
	}
	return (false);
}

void	CondVarWindows::signal()
{
	WakeConditionVariable(&this->_condvar);
}

void	CondVarWindows::broadcast()
{
	WakeAllConditionVariable(&this->_condvar);
}