#include <iostream>
#include <dlfcn.h>
#include <string.h>
#include "Error.hpp"
#include "ExtensionSo.hpp"

ExtensionSo::ExtensionSo()
{
}

ExtensionSo::ExtensionSo(const ExtensionSo& old)
{
  this->handle = old.handle;
}

ExtensionSo::~ExtensionSo()
{
}

ExtensionSo&		ExtensionSo::operator=(const ExtensionSo &old)
{
  this->handle = old.handle;
  return (*this);
}

void		ExtensionSo::openExt(const std::string &name)
{
  if ((this->handle = dlopen(name.c_str(), RTLD_NOW)) == NULL)
    {
      char *error = dlerror();
      if (error != NULL)
	{
	  CustomError	err(error);
	  throw (err);
	}
    }
}

void		*ExtensionSo::getSymbolInLib(std::string const & funcname)
{
  char		*error;

  void *ptr = dlsym(this->handle, funcname.c_str());
  if ((error = dlerror()) != NULL)
    {
      CustomError	err(error);
      throw (err);
    }
  return (ptr);
}


void		ExtensionSo::close()
{
  dlclose(this->handle);
}
