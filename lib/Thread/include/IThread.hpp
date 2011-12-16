#ifndef _ITHREAD_HPP__
#define _ITHREAD_HPP__

enum eThreadState
{
	ON,
	OFF,
	DEAD
};

class IThread
{
public:
	virtual bool Create(void *(*pfonct)(void *), void *t) = 0;
	virtual bool operator()(void *(*pfonct)(void *), void *t) = 0;
	virtual bool Destroy(void) = 0;
	virtual bool Wait(void) = 0;
	virtual eThreadState getState(void) const = 0;
};


#endif // _ITHREAD_HPP__
