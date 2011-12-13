#include "DirectoryManagerUnix.hpp"

DirectoryManagerUnix::DirectoryManagerUnix()
{
}

DirectoryManagerUnix::~DirectoryManagerUnix()
{

}

void	DirectoryManagerUnix::openDirectory(const std::string& name)
{
  this->directory = opendir(name.c_str());
  this->dirName = name;
  if (this->directory == NULL)
    {
      this->err.setErrorMessage("[UNIX]DirectoryManagerError: No such file or directory");
      throw (this->err);
    }
}

const std::string	DirectoryManagerUnix::readNameFile()
{
  std::string	fileName;

  this->rVal = readdir(this->directory);
  if (!this->rVal)
    return ("");
  fileName += this->dirName;
  fileName += this->rVal->d_name;
  return (fileName);
}

void	DirectoryManagerUnix::closeDirectory()
{
  closedir(this->directory);
}

// std::string		DirectoryManagerUnix::getPlatChar() const
// {
//   return ("\\");
// }
