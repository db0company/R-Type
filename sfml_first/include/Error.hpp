#ifndef __ERROR_HPP__
# define __ERROR_HPP__

#include <exception>
#include <stdexcept>
#include <string>

class	CustomError : public std::exception
{
  std::string	sms;

public:
  CustomError() throw();
  ~CustomError() throw() {}
  CustomError(std::string const&) throw();
  const char 	*what() throw();
  void		setErrorMessage(std::string const&);
};

#endif
