#include <iostream>
#include <string>
#include <sys/types.h>
#include <string.h>
#include "Error.hpp"
#include "OS.hpp"
#include "Dll.hpp"
#include "DlLoader.hpp"
#include "IDirectoryManager.hpp"


DlLoader::DlLoader()
{

}

DlLoader::~DlLoader()
{
}


template <typename T>
void	DlLoader::openDll(std::string const& name)
{
  T ext;
  ext.openExt(name);
  if (mapDll.find(name) != mapDll.end())
    {
      CustomError	err("DlLoaderError: could not open " + name);

      throw (err);
    }
  this->mapDll.insert(std::pair<std::string , Dll>(name , Dll(dynamic_cast<IExtension *>(new T(ext)), name)));
}

template <typename T>
void DlLoader::openDllFromDirectory(const std::string &nameDirectory, IDirectoryManager *dm)
{
  std::string nameDll;
  size_t i;

  dm->openDirectory(replaceDelim(nameDirectory));

  nameDll = dm->readNameFile();

  while (nameDll != "")
    {
      if ((i = nameDll.find(EXTENSION)) != std::string::npos && i == nameDll.size() - strlen(EXTENSION))
	this->openDll<T>(nameDll);
     nameDll = dm->readNameFile();
    }
}

Dll& DlLoader::getDll(std::string &name)
{
  CustomError	err("DlLoaderError: " + name + " No such shared library");
  std::map<std::string, Dll>::iterator it;
  std::string	dirfilename;

  (void)dm;
  dirfilename = replaceDelim(name);
  if (this->mapDll.empty())
  {
    throw (err);
  }
  if ((it = this->mapDll.find(dirfilename)) == mapDll.end())
  {
    throw (err);
  }
  return (it->second);
}

void	 DlLoader::closeDll()
{
  std::map<std::string, Dll>::iterator it;

  it = this->mapDll.begin();
  while (it != this->mapDll.end())
    {
      it->second.closeDll();
      ++it;
    }
}

DlLoader	*DlLoader::getInstance(void)
{
  static DlLoader *DlLoaderInstance = NULL;

  if (!DlLoaderInstance)
  DlLoaderInstance = new DlLoader();
  return (DlLoaderInstance);
}

void		DlLoader::replaceDelim(const std::string& s)
{
  size_t	c;
  std::string	good = s;
  int		i = 0;

  while ((c = good.find("/"), i) != std::string::npos)
    {
      good.replace(c, 1, DELIM);
      i = c + 1;
    }
}

#ifdef _WIN32
template void   DlLoader::openDll<ExtensionDll>(std::string const& name);
template void DlLoader::openDllFromDirectory<ExtensionDll>(const std::string &nameDirectory, IDirectoryManager *dm);
#else
template void   DlLoader::openDll<ExtensionSo>(std::string const& name);
template void DlLoader::openDllFromDirectory<ExtensionSo>(const std::string &nameDirectory, IDirectoryManager *dm);
#endif
