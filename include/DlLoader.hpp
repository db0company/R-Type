#ifndef		__DLLOADER_HPP__
# define	__DLLOADER_HPP__

#include <map>
#include <string>
#include "Dll.hpp"
#include "IMutex.hpp"
#include "IDirectoryManager.hpp"

class DlLoader
{
  std::map<std::string, Dll> mapDll;
  DlLoader();
  virtual ~DlLoader();
  IMutex	*_mut;
public:
  static DlLoader *getInstance();
  Dll& getDll();
  Dll& getDll(const std::string& name);
  template <typename T>
  void openDll(const std::string &nameLib);
  template <typename T>
  void openDllFromDirectory(const std::string &nameDirectory, IDirectoryManager *dm);
  void closeDll();
  const std::string		replaceDelim(const std::string& s);
  void		activMut();
  void		desactivMut();
};

#endif		/*__DLLOADER_HPP__*/
