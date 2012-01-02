#ifndef		__AOBJECT_HPP__
# define	__AOBJECT_HPP__

#include <string>
#include "Position.hpp"

class		AObject
{
protected:
  Position	pos;
  std::string	name;
  std::string	type;
public:
  AObject();
  AObject(const AObject& old);
  ~AObject();
  const std::string &getName()const;
  void		setPos(const Position& newPos);
  const Position&	getPos()const;
  AObject	&operator=(const AObject& old);
};

#endif		/*__AOBJECT_HPP__*/
