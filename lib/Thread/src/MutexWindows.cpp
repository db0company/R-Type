#include <windows.h>
#include "MutexWindows.hpp"

MutexWindows::MutexWindows(void)
{
	InitializeCriticalSection(&(this->_section));
}

MutexWindows::~MutexWindows(void)
{
	DeleteCriticalSection(&(this->_section));
}

bool MutexWindows::Lock(void)
{
	// todo: can raise an exeption ?
	EnterCriticalSection(&(this->_section));
	return (true);
}

bool MutexWindows::Unlock(void)
{
	LeaveCriticalSection(&(this->_section));
	return (true);
}

bool MutexWindows::Try(void)
{
	if (TryEnterCriticalSection(&(this->_section)) == 0)
	{
		return (false);
	}
	return (true);
}