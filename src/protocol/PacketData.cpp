
#include		<cctype>
#include		<iostream>
#include		"PacketData.hpp"

/* ************************************************************************* */
/*                             Coplien Form                                  */
/* ************************************************************************* */

PacketData::PacketData(void)
  : data(), it(data.begin())
{}

PacketData::PacketData(DataRawType const * raw, ushort size)
  : data(raw, (raw + size * sizeof(DataRawType))), it(data.begin())
{}

PacketData::PacketData(PacketData const & other)
  : data(other.data), it(other.it)
{}

PacketData &		PacketData::operator=(PacketData const & other)
{
  if (&other != this)
    {
      this->data = other.data;
      this->it = other.it;

      // If there is a pointer to something allocated, do this :
      // if (this->SomeThingAllocated)
      //   delete this->SomeThingAllocated;
      // this->SomeThingAllocated = CopyFunc(other.SomeThingAllocated);
    }
  return (*this);
}

PacketData::~PacketData(void)
{}

/* ************************************************************************* */
/*                            Member Functions                               */
/* ************************************************************************* */

static void		prettyPrinter(DataRawType c)
{
  if (isprint(c))
    std::cout << '[' << (char)c << ']';
  else
    std::cout << '[' << (int)c << ']';
}

void			PacketData::prettyPrint(void) const
{
  std::cout << "{<(* ~~ PrettyPrint ~~ *)>}" << std::endl;
  for_each(this->data.begin(), this->data.end(), prettyPrinter);
  std::cout << std::endl;
}

/* ************************************************************************* */

DataRawType const *	PacketData::getData(void) const
{
  return (NULL);
}

ushort			PacketData::getDataSize(void) const
{
  return (this->data.size());
}


/* ************************************************************************* */

std::string		PacketData::getNextString(void)
{
  // todo
  return ("");
}

std::string		PacketData::getRestString(void)
{
  // todo
  return ("");
}

char			PacketData::getNextChar(void)
{
  // todo
  return (0);
}

uchar			PacketData::getNextUChar(void)
{
  // todo
  return (0);
}

short			PacketData::getNextShort(void)
{
  // todo
  return (0);
}

ushort			PacketData::getNextUShort(void)
{
  // todo
  return (0);
}

UInt32			PacketData::getNextUint32(void)
{
  // todo
  return (0);
}

/* ************************************************************************* */

void			PacketData::addString(char const *)
{
  // todo
}

void			PacketData::addString(std::string const & str)
{
  this->addString(str.c_str());
}

void			PacketData::addChar(char )
{
  // todo
}

void			PacketData::addUChar(uchar )
{
  // todo
}

void			PacketData::addShort(short )
{
  // todo
}

void			PacketData::addUShort(ushort )
{
  // todo
}

void			PacketData::addUint32(UInt32 )
{
  // todo
}

