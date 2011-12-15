
#include		<cctype>
#include		<iostream>
#include		"ProtocolPacketData.hpp"

/* ************************************************************************* */
/*                             Coplien Form                                  */
/* ************************************************************************* */

ProtocolPacketData::ProtocolPacketData(void)
  : data(), it(data.begin())
{}

ProtocolPacketData::ProtocolPacketData(DataRawType const * raw, ushort size)
  : data(raw, (raw + size * sizeof(DataRawType))), it(data.begin())
{}

ProtocolPacketData::ProtocolPacketData(ProtocolPacketData const & other)
  : data(other.data), it(other.it)
{}

ProtocolPacketData &		ProtocolPacketData::operator=(ProtocolPacketData const & other)
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

ProtocolPacketData::~ProtocolPacketData(void)
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

void			ProtocolPacketData::prettyPrint(void) const
{
  std::cout << "{<(* ~~ PrettyPrint ~~ *)>}" << std::endl;
  for_each(this->data.begin(), this->data.end(), prettyPrinter);
  std::cout << std::endl;
}

/* ************************************************************************* */

DataRawType const *	ProtocolPacketData::getData(void) const
{
  return (NULL);
}

ushort			ProtocolPacketData::getDataSize(void) const
{
  return (this->data.size());
}


/* ************************************************************************* */

std::string		ProtocolPacketData::getNextString(void)
{
  // todo
  return ("");
}

std::string		ProtocolPacketData::getRestString(void)
{
  // todo
  return ("");
}

char			ProtocolPacketData::getNextChar(void)
{
  // todo
  return (0);
}

uchar			ProtocolPacketData::getNextUChar(void)
{
  // todo
  return (0);
}

short			ProtocolPacketData::getNextShort(void)
{
  // todo
  return (0);
}

ushort			ProtocolPacketData::getNextUShort(void)
{
  // todo
  return (0);
}

UInt32			ProtocolPacketData::getNextUint32(void)
{
  // todo
  return (0);
}

/* ************************************************************************* */

void			ProtocolPacketData::addString(char const *)
{
  // todo
}

void			ProtocolPacketData::addString(std::string const & str)
{
  this->addString(str.c_str());
}

void			ProtocolPacketData::addChar(char )
{
  // todo
}

void			ProtocolPacketData::addUChar(uchar )
{
  // todo
}

void			ProtocolPacketData::addShort(short )
{
  // todo
}

void			ProtocolPacketData::addUShort(ushort )
{
  // todo
}

void			ProtocolPacketData::addUint32(UInt32 )
{
  // todo
}

