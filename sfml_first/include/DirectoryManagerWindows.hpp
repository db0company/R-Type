#ifndef __DIRECTORYMANAGERWINDOWS_HPP__
# define __DIRECTORYMANAGERWINDOWS_HPP__

#include <windows.h>
#include <tchar.h> 
#include <strsafe.h>
#include "IDirectoryManager.hpp"
#include "Error.hpp"

class   DirectoryManagerWindows : public IDirectoryManager
{
    bool firstfile;
    WIN32_FIND_DATA ffd;
   LARGE_INTEGER filesize;
   TCHAR szDir[MAX_PATH];
   size_t length_of_arg;
   HANDLE hFind;
   DWORD dwError;
    std::string     dirname;
  CustomError	err;

public:
    DirectoryManagerWindows();
    virtual ~DirectoryManagerWindows();
    virtual void openDirectory(const std::string&);
    virtual std::string const   readNameFile();
    virtual void closeDirectory();
};

#endif /* __DIRECTORYMANAGERWINDOWS_HPP__ */
