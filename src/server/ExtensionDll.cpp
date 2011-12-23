#include <Windows.h>
#include <strsafe.h>
#include <string>
#include <iostream>
#include "IExtension.hpp"
#include "ExtensionDll.hpp"
#include "Error.hpp"
#include "OS.hpp"


ExtensionDll::ExtensionDll()
{
}


ExtensionDll::~ExtensionDll()
{
}

ExtensionDll::ExtensionDll(const ExtensionDll& old)
{
  this->handle = old.handle;
}

ExtensionDll&		ExtensionDll::operator=(const ExtensionDll& old)
{
  this->handle = old.handle;
  return (*this);
}

void ErrorExit(LPTSTR lpszFunction) 
{ 
    // Retrieve the system error message for the last-error code

    LPVOID lpMsgBuf;
    LPVOID lpDisplayBuf;
    DWORD dw = GetLastError(); 

    FormatMessage(
        FORMAT_MESSAGE_ALLOCATE_BUFFER | 
        FORMAT_MESSAGE_FROM_SYSTEM |
        FORMAT_MESSAGE_IGNORE_INSERTS,
        NULL,
        dw,
        MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
        (LPTSTR) &lpMsgBuf,
        0, NULL );

    // Display the error message and exit the process

    lpDisplayBuf = (LPVOID)LocalAlloc(LMEM_ZEROINIT, 
        (lstrlen((LPCTSTR)lpMsgBuf) + lstrlen((LPCTSTR)lpszFunction) + 40) * sizeof(TCHAR)); 
    StringCchPrintf((LPTSTR)lpDisplayBuf, 
        LocalSize(lpDisplayBuf) / sizeof(TCHAR),
        TEXT("%s failed with error %d: %s"), 
        lpszFunction, dw, lpMsgBuf); 
    MessageBox(NULL, (LPCTSTR)lpDisplayBuf, TEXT("Error"), MB_OK); 

    LocalFree(lpMsgBuf);
    LocalFree(lpDisplayBuf);
    ExitProcess(dw); 
}

void            ExtensionDll::openExt(const std::string &name)
{
	if ((this->handle = LoadLibrary(name.c_str())) == NULL)
  {
	ErrorExit("LoadLibrary");
      CustomError err(name + " not found");
      throw err;
  }
}

void		*ExtensionDll::getSymbolInLib(std::string const& funcname)
{
LPCSTR str = funcname.c_str();

  FARPROC	ptr = GetProcAddress(this->handle, str);
  if (ptr == NULL)
    {
         CustomError err(funcname + " symbol not found");
         throw err;
  }
  return (ptr);
}

void		ExtensionDll::close()
{
  FreeLibrary(this->handle);
}
