#include <Windows.h>
#include <stdio.h>

#include "DirectoryManagerWindows.hpp"

DirectoryManagerWindows::DirectoryManagerWindows()
{
  this->firstfile = false;
  memset(this->szDir, '\0', MAX_PATH);
  this->hFind = INVALID_HANDLE_VALUE;
  this->dwError = 0;
}

DirectoryManagerWindows::~DirectoryManagerWindows()
{
}

void    DirectoryManagerWindows::openDirectory(const std::string & namedir)
{
    this->dirname = namedir;
    LPCSTR error = "[WINDOWS]: Error ";
    StringCchLength(namedir.c_str(), MAX_PATH, &length_of_arg);
    if (length_of_arg > (MAX_PATH - 3))
    {
 //       MessageBox(NULL, error, TEXT("FileName is too long\n"), MB_OK);
	this->err.setErrorMessage("FileName is too long");
	throw (this->err);
        return ;
    }
    StringCchCopy(this->szDir, MAX_PATH, namedir.c_str());
    StringCchCat(this->szDir, MAX_PATH, TEXT("\\*"));
    this->hFind = FindFirstFile(this->szDir, &this->ffd);
    if (this->hFind == INVALID_HANDLE_VALUE)
    {
 //       MessageBox(NULL, error, TEXT("Could not find ddlfile\n"), MB_OK);
	this->err.setErrorMessage("Could not find dllFile");
	throw (this->err);
    }
    this->firstfile = true;
}

std::string const   DirectoryManagerWindows::readNameFile()
{
    std::string filename = this->dirname;
    std::string retvalue;

    if (this->hFind == INVALID_HANDLE_VALUE)
            return ("");
    if (this->firstfile == true)
    {
        this->firstfile = false;
        retvalue = this->ffd.cFileName;
        return (retvalue);
    }
    if (FindNextFile(this->hFind, &this->ffd) != 0)
    retvalue = this->ffd.cFileName;
    else
    {
        this->dwError = GetLastError();
        if (this->dwError != ERROR_NO_MORE_FILES)
        return ("");
    }
    return (retvalue);
}

void        DirectoryManagerWindows::closeDirectory()
{
    LPCSTR error = "[WINDOWS]: Error ";

   if (FindClose(this->hFind) == false)
   {
       MessageBox(NULL, error, TEXT("CloseDirectory failed\n"), MB_OK);
   }
}
