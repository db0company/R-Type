#ifndef _ITHREAD_HPP__
#define _ITHREAD_HPP__

typedef void generic;

enum eThreadState
{
	ON,
	OFF,
	DEAD
};

class IThread
{
public:
	virtual bool Create(generic *(*pfonct)(generic *), generic *t) = 0;
	virtual bool operator()(generic *(*pfonct)(generic *), generic *t) = 0;
	virtual bool Destroy(void) = 0;
	virtual bool Wait(void) = 0;
	virtual eThreadState getState(void) const = 0;
};


#endif // _ITHREAD_HPP__
