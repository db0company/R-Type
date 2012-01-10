#ifndef		__AOBJECT_HPP__
# define	__AOBJECT_HPP__

# include <string>
# include "Position.hpp"
# include "DefineExportMonster.hpp"

# ifdef _WIN32
class		 IObject
# else
class		IObject
# endif
{
public:
	virtual ~IObject() {}
};



# ifdef _WIN32
class		 AObject : public IObject
# else
class		 AObject : public IObject
# endif
{
protected:
  Position	pos;
  std::string	name;
  std::string	type;
public:
  AObject();
  AObject(const AObject& old);
  virtual ~AObject();
  const std::string &getName()const;
  void		setPos(const Position& newPos);
  const Position&	getPos()const;
  AObject	&operator=(const AObject& old);
};

#endif		/*__AOBJECT_HPP__*/
