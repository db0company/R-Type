//
// DlLoader.hpp for  in /home/bideau_s//babel/src/babel
//
// Made by sofia bideaux
// Login   <bideau_s@epitech.net>
//
// Started on  Sat Nov 19 17:45:35 2011 sofia bideaux
// Last update Tue Nov 29 01:14:31 2011 cedric anceau
//

#ifndef		__DLLOADER_HPP__
# define	__DLLOADER_HPP__

#include <map>
#include <string>
#include "Dll.hpp"
#include "IDirectoryManager.hpp"

class DlLoader
{
  std::map<std::string, Dll> mapDll;
  DlLoader();
  virtual ~DlLoader();

public:
  static DlLoader *getInstance();
  Dll& getDll();
  Dll& getDll(std::string dirname, std::string &name, const IDirectoryManager& dm);
  template <typename T>
  void openDll(const std::string &nameLib);
  template <typename T>
  void openDllFromDirectory(const std::string &nameDirectory, IDirectoryManager *dm);
  void closeDll();
};

#endif		/*__DLLOADER_HPP__*/
