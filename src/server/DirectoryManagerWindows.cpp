#include <Windows.h>
#include <iostream>
#include <string>

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
	//(STRSAFE_PCNZWCH)
    StringCchLength(namedir.c_str(), MAX_PATH, &length_of_arg);

    if (length_of_arg > (MAX_PATH - 3))
    {
 //     MessageBox(NULL, (LPCWSTR)error, TEXT("FileName is too long\n"), MB_OK);
	this->err.setErrorMessage("FileName is too long");

	throw (this->err);
        return ;
    }
	//(STRSAFE_LPCWSTR)
    StringCchCopy(this->szDir, MAX_PATH, namedir.c_str());
    StringCchCat(this->szDir, MAX_PATH, TEXT("\\*"));
	std::cout << this->szDir << std::endl;
    this->hFind = FindFirstFile(this->szDir, &this->ffd);
    if (this->hFind == INVALID_HANDLE_VALUE)
    {
		std::cout << "LANCEMENT ERROR " << std::endl; 
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
		retvalue = this->dirname + "\\";
        retvalue += (char *)this->ffd.cFileName;
        return (retvalue);
    }
    if (FindNextFile(this->hFind, &this->ffd) != 0)
	{
		retvalue = this->dirname + "\\";
        retvalue += (char *)this->ffd.cFileName;
		return (retvalue);
	}
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
    LPCWSTR error = (L"[WINDOWS]: Error ");

   if (FindClose(this->hFind) == false)
   {
//       MessageBox(NULL, error, TEXT("CloseDirectory failed\n"), MB_OK);
   }
}
