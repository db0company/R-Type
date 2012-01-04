#include <Windows.h>
#include <strsafe.h>
#include <string>
#include <iostream>
#include "IExtension.hpp"
#include "ExtensionDll.hpp"
#include "Error.hpp"
#include "OS.hpp"


ExtensionDll::ExtensionDll()
{
}


ExtensionDll::~ExtensionDll()
{
}

ExtensionDll::ExtensionDll(const ExtensionDll& old)
{
  this->handle = old.handle;
}

ExtensionDll&		ExtensionDll::operator=(const ExtensionDll& old)
{
  this->handle = old.handle;
  return (*this);
}


void            ExtensionDll::openExt(const std::string &name)
{
	if ((this->handle = LoadLibrary(name.c_str())) == NULL)
  {
	ErrorExit("LoadLibrary");
      CustomError err(name + " not found");
      throw err;
  }
}

void		*ExtensionDll::getSymbolInLib(std::string const& funcname)
{
LPCSTR str = funcname.c_str();

  FARPROC	ptr = GetProcAddress(this->handle, str);
  if (ptr == NULL)
    {
         CustomError err(funcname + " symbol not found");
         throw err;
  }
  return (ptr);
}

void		ExtensionDll::close()
{
  FreeLibrary(this->handle);
}
