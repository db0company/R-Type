//
// Dll.hpp for  in /home/bideau_s//babel/src/babel
//
// Made by sofia bideaux
// Login   <bideau_s@epitech.net>
//
// Started on  Sat Nov 19 18:34:50 2011 sofia bideaux
// Last update Wed Nov 30 23:46:37 2011 sofia bideaux
//

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
