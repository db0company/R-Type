#ifndef __EXTENSION_DLL_HPP
# define __EXTENSION_DLL_HPP

#include <Windows.h>
#include "IExtension.hpp"

class		ExtensionDll : public IExtension
{
  HMODULE	handle;

public:
  ExtensionDll();
  virtual ~ExtensionDll();
  ExtensionDll(const ExtensionDll& old);
  ExtensionDll&		operator=(const ExtensionDll& old);
  void		openExt(const std::string &name);
  void		*getSymbolInLib(std::string const&);
  void      close();
};
#endif
