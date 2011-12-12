#include <Windows.h>
#include "ThreadWindows.hpp"

ThreadWindows::ThreadWindows(void): _state(OFF)
{
}

ThreadWindows::~ThreadWindows(void)
{
}

bool ThreadWindows::Create(void *(*pfonct)(void *), void *data)
{
	this->_handle = CreateThread(NULL, 0, reinterpret_cast<LPTHREAD_START_ROUTINE>(pfonct), data, 0, &(this->_threadId));
	if (this->_handle == NULL)
		{
			return (false);
		}
	this->_state = ON;
	return (true);
}

bool ThreadWindows::operator()(void *(*pfonct)(void *), void *data)
{
	this->_handle = CreateThread(NULL, 0, reinterpret_cast<LPTHREAD_START_ROUTINE>(pfonct), data, 0, &(this->_threadId));
	if (this->_handle == NULL)
		{
			return (false);
		}
	this->_state = ON;
	return (true);
}

bool ThreadWindows::Destroy(void)
{
	if (CloseHandle(this->_handle) == 0)
	{
		return (false);
	}
	return (true);
}

bool ThreadWindows::Wait(void)
{
	if (WaitForMultipleObjects(1, &(this->_handle), TRUE, INFINITE) == WAIT_FAILED)
	{
		return (false);
	}
	this->_state = DEAD;
	return (true);
}

eThreadState ThreadWindows::getState() const
{
	return (this->_state);
}