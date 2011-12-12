#ifndef		__IDIRECTORYMANAGER_HPP__
# define	__IDIRECTORYMANAGER_HPP__

#include <string>

class		IDirectoryManager
{
public:
  ~IDirectoryManager() {}
  virtual void	openDirectory(const std::string& name) = 0;
  virtual const std::string	readNameFile() = 0;
  virtual void	closeDirectory() = 0;
  virtual std::string getPlatChar()const = 0;
};

#endif		/*__IDIRECTORYMANAGER_HPP__*/
