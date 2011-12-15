#include "Error.hpp"

CustomError::CustomError() throw()
{
  this->sms = "An error has occured";
}

CustomError::CustomError(std::string const& err) throw()
{
  this->sms = err;
}

const char	  *CustomError::what() throw()
{
  return (this->sms.c_str());
}

void		CustomError::setErrorMessage(std::string const& err)
{
  this->sms = err;
}
