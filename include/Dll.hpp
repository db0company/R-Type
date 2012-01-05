#ifndef		__DLL_HPP__
# define	__DLL_HPP__

#include <string>
#include "IExtension.hpp"


class  Dll
{
  IExtension *dll;
  std::string name;
public:
  Dll(IExtension *handl, const std::string &nameLib);
  Dll();
  Dll(const Dll& old);
  ~Dll();
  Dll&		operator=(const Dll& old);
  void		setDll(IExtension *handl, const std::string &nameLib);
  template <typename T>
  T *getSymbol(std::string const & nameFunc)const;
  void closeDll();
};

#endif		/*__DLL_HPP__*/
