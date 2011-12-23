#include <iostream>
#include <string>
#include "Error.hpp"
#include "DlLoader.hpp"
#include "Dll.hpp"
#include "IExtension.hpp"
#include "IAudio.hpp"
#include "OS.hpp"
#include "IGraph.hpp"

Dll::Dll(IExtension *handl, const std::string &nameLib)
{
  this->dll = handl;
  this->name = nameLib;
}

Dll::Dll()
{
  this->dll = NULL;
}

Dll::Dll(const Dll& old)
{
  this->dll = old.dll;
  this->name = old.name;
}

Dll&            Dll::operator=(const Dll& old)
{
  this->dll = old.dll;
  this->name = old.name;
  return (*this);
}


void		Dll::setDll(IExtension *handl, const std::string &nameLib)
{
  this->dll = handl;
  this->name = nameLib;
}

Dll::~Dll()
{

}

template <typename T>
T *Dll::getSymbol(std::string const & nameFunc) const
{
  CustomError	err("DllError: could not get Symbol " + nameFunc);
  T *(*createLib)() = NULL;

  if ((createLib = reinterpret_cast<T *(*)() >(dll->getSymbolInLib(nameFunc))) == NULL)
    {
      throw (err);
    }
  return (createLib());
}

void Dll::closeDll()
{
  this->dll->close();
}

template IAudio *Dll::getSymbol<IAudio>(std::string const & nameFunc) const;

template IEncoder *Dll::getSymbol<IEncoder>(std::string const & nameFunc) const;
