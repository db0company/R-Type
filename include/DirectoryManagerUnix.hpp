#ifndef		__DIRECTORYMANAGERUNIX_HPP__
# define	__DIRECTORYMANAGERUNIX_HPP__

#include <iostream>
#include <string>
#include <sys/types.h>
#include <dirent.h>
#include "IDirectoryManager.hpp"
#include "Error.hpp"

class		DirectoryManagerUnix : public IDirectoryManager
{
  CustomError	err;

private:
  DIR		*directory;
  struct dirent	*rVal;
  std::string	dirName;
  public:
  DirectoryManagerUnix();
  virtual ~DirectoryManagerUnix();
  virtual void	openDirectory(const std::string& name);
  virtual const std::string	readNameFile();
  virtual void	closeDirectory();
};

#endif		/*__DIRECTORYMANAGERUNIX_HPP__*/
