#ifndef _ITHREAD_HPP__
#define _ITHREAD_HPP__

typedef void generic;

enum eThreadState
{
	ON,
	OFF,
	DEAD
};

// class IWork
// {
// public:
//   virtual void Run() = 0;
// };

// class PrintToto : public IWork
// {
// private:
//   std::string _arg;

// public:
//   PrintToto(std::string arg) : _arg(arg) {}
//   virtual void Run()
//   {
//     std::cout << "toto" << arg << std::endl;
//   }
// };

class IThread
{
public:
        virtual ~IThread(void){}
	virtual bool Create(generic *(*pfonct)(generic *), generic *t) = 0;
	virtual bool operator()(generic *(*pfonct)(generic *), generic *t) = 0;
	// virtual bool operator()(IWork *work) = 0;
	virtual bool Destroy(void) = 0;
	virtual bool Wait(void) = 0;
	virtual eThreadState getState(void) const = 0;
};


#endif // _ITHREAD_HPP__
