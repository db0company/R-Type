#ifndef __MUTEX_WINDOWS_HPP__
#define __MUTEX_WINDOWS_HPP__

#include <windows.h>
#include "IMutex.hpp"

class MutexWindows : public IMutex
{
public:
	MutexWindows(void);
	~MutexWindows(void);
	virtual bool Lock(void);
	virtual bool Unlock(void);
	virtual bool Try(void);
private:
	CRITICAL_SECTION _section;
};

#endif // __MUTEX_WINDOWS_HPP__
