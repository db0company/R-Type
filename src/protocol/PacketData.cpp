#include		<cctype>
#include		<cstring>
#include		<iostream>
#include		"PacketData.hpp"
#include		"Position.hpp"

/* ************************************************************************* */
/*                             Coplien Form                                  */
/* ************************************************************************* */

PacketData::PacketData(void)
  : data(), it(0)
{}

PacketData::PacketData(DataRawType const * raw, ushort size)
  : data(raw, (raw + size * sizeof(DataRawType))), it(0)
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

void			uglyPrinter(char *str, int size)
{
  int		i;

  i = 0;
  while (i < size)
    {
      if (isprint(str[i]))
	std::cout << '[' << (char)str[i] << ']';
      else
	std::cout << '[' << (int)str[i] << ']';
      ++i;
    }
  std::cout << std::endl;
}

void			PacketData::prettyPrint(void) const
{
  //  std::cout << "{<(* ~~ PrettyPrint ~~ *)>}" << std::endl;
  for_each(this->data.begin(), this->data.end(), prettyPrinter);
  std::cout << std::endl;
}

/* ************************************************************************* */

DataRawType const *		PacketData::getData(void) const
{
  // It works because vector containers have their elements stored in
  // contiguous storage locations, which means that their elements can be
  // accessed not only using iterators but also using offsets on regular
  // pointers to elements.
  return (&data[0]);
}

ushort			PacketData::getDataSize(void) const
{
  return (this->data.size());
}


/* ************************************************************************* */

std::string		PacketData::getNextString(void)
{
  ushort len = this->getNextUShort();
  if ((this->data.size() - this->it) < len)
    return ("");
  char * c_str = new char[len + 1];
  for (uint i = 0 ; i < len ; ++i, ++(this->it))
    c_str[i] = this->data[this->it];
  c_str[len] = '\0';
  std::string str(c_str);
  delete[] c_str;
  return (str);
}

char			PacketData::getNextChar(void)
{
  if ((this->data.size() - this->it) < sizeof(char))
    return (0);
  char c = 0;
  // DataRawType tmp[sizeof(char)];
  // for (uint i = 0 ; i < sizeof(char) ; ++i, ++(this->it))
  //   tmp[i] = this->data[this->it];
  // memcpy(&c, tmp, sizeof(char));
  c = this->data[this->it];
  ++(this->it);
  return (c);
}

uchar			PacketData::getNextUChar(void)
{
  if ((this->data.size() - this->it) < sizeof(uchar))
    return (0);
  uchar c = 0;
  DataRawType tmp[sizeof(uchar)];
  for (uint i = 0 ; i < sizeof(uchar) ; ++i, ++(this->it))
    tmp[i] = this->data[this->it];
  memcpy(&c, tmp, sizeof(uchar));
  return (c);
}

short			PacketData::getNextShort(void)
{
  if ((this->data.size() - this->it) < sizeof(short))
    return (0);
  short s = 0;
  DataRawType tmp[sizeof(short)];
  for (uint i = 0 ; i < sizeof(short) ; ++i, ++(this->it))
    tmp[i] = this->data[this->it];
  memcpy(&s, tmp, sizeof(short));
  return (s);
}

ushort			PacketData::getNextUShort(void)
{
  if ((this->data.size() - this->it) < sizeof(ushort))
    return (0);
  ushort s = 0;
  DataRawType tmp[sizeof(ushort)];
  for (uint i = 0 ; i < sizeof(ushort) ; ++i, ++(this->it))
    tmp[i] = this->data[this->it];
  memcpy(&s, tmp, sizeof(ushort));
  return (s);
}

unsigned int			PacketData::getNextUint32(void)
{
  if ((this->data.size() - this->it) < sizeof(unsigned int))
    return (0);
  short s = 0;
  DataRawType tmp[sizeof(unsigned int)];
  for (uint i = 0 ; i < sizeof(unsigned int) ; ++i, ++(this->it))
    tmp[i] = this->data[this->it];
  memcpy(&s, tmp, sizeof(unsigned int));
  return (s);
}

template <typename T>
T			PacketData::getData(void)
{
  T s;
  if ((this->data.size() - this->it) < sizeof(T))
    std::cerr << "getData ERROR " << std::endl;
  DataRawType tmp[sizeof(T)];
  for (uint i = 0 ; i < sizeof(T) ; ++i, ++(this->it))
    tmp[i] = this->data[this->it];
  memcpy(&s, tmp, sizeof(T));
  return (s);
}

/* ************************************************************************* */

void			PacketData::addString(char const * str, ushort len)
{
  this->addUShort(len);
//  DataRawType tmp[len];
  DataRawType *tmp;
  tmp = new DataRawType[len];
  memcpy(tmp, str, len);
  for (uint i = 0 ; i < len ; ++i)
    this->data.push_back(tmp[i]);
}

void			PacketData::addString(std::string const & str)
{
  this->addString(str.c_str(), str.size());
}

void			PacketData::addChar(char c)
{
  this->data.push_back(c);
  // DataRawType tmp[sizeof(char)];
  // memcpy(tmp, &c, sizeof(char));
  // for (uint i = 0 ; i < sizeof(char) ; ++i)
  //   this->data.push_back(tmp[i]);
}

void			PacketData::addUChar(uchar u)
{
  DataRawType tmp[sizeof(uchar)];
  memcpy(tmp, &u, sizeof(uchar));
  for (uint i = 0 ; i < sizeof(uchar) ; ++i)
    this->data.push_back(tmp[i]);
}

void			PacketData::addShort(short s)
{
  DataRawType tmp[sizeof(short)];
  memcpy(tmp, &s, sizeof(short));
  for (uint i = 0 ; i < sizeof(short) ; ++i)
    this->data.push_back(tmp[i]);
}

void			PacketData::addUShort(ushort u)
{
  DataRawType tmp[sizeof(ushort)];
  memcpy(tmp, &u, sizeof(ushort));
  for (uint i = 0 ; i < sizeof(ushort) ; ++i)
    this->data.push_back(tmp[i]);
}

void			PacketData::addUint32(short u)
{
  DataRawType tmp[sizeof(short)];
  memcpy(tmp, &u, sizeof(short));
  for (uint i = 0 ; i < sizeof(short) ; ++i)
    this->data.push_back(tmp[i]);
}

template <typename T>
void			PacketData::addData(T u)
{
  DataRawType tmp[sizeof(T)];
  memcpy(tmp, &u, sizeof(T));
  for (uint i = 0 ; i < sizeof(T) ; ++i)
    this->data.push_back(tmp[i]);  
}

template void PacketData::addData(Position u);
template Position PacketData::getData(void);
