#ifndef __IEXTENSION_DLL_HPP__
# define __IEXTENSION_DLL_HPP__

#include <string>
#include <iostream>

class			IExtension
{
public:
  virtual		~IExtension() {}

  virtual void		*getSymbolInLib(std::string const &funcame) = 0;
  virtual void		close() = 0;
  virtual void		openExt(const std::string &name) = 0;
};

#endif
