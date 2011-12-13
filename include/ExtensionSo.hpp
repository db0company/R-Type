#ifndef __EXTENSION_SO_HPP
# define __EXTENSION_SO_HPP

#include <string>
#include "IExtension.hpp"

class		ExtensionSo : public IExtension
{
  void	*handle;

public:
  ExtensionSo();
  ExtensionSo(const ExtensionSo&);
  virtual ~ExtensionSo();
  ExtensionSo&	operator=(const ExtensionSo& old);

  void		openExt(const std::string &name);
  void		*getSymbolInLib(std::string const&);
  void		close();
};

#endif
