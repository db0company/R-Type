#ifndef		__AOBJECT_HPP__
# define	__AOBJECT_HPP__

#include <string>
#include "Position.hpp"

class		AObject
{
private:
  Position	pos;
  std::string	name;
  std::string	type;
public:
  AObject();
  AObject(const AObject& old);
  ~AObject();
  AObject	&operator=(const AObject& old);
};

#endif		/*__AOBJECT_HPP__*/
