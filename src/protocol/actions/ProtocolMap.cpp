
#include		"ProtocolMap.hpp"

ProtocolMap::ProtocolMap()
{
  this->actionmap[MAP_ERROR] = &ProtocolMap::actionError;
  this->actionmap[GETMAP] = &ProtocolMap::actionGet;
}

ProtocolMap::ProtocolMap(ProtocolMap const & other)
{
}

ProtocolMap &		ProtocolMap::operator=(ProtocolMap const & other)
{
  if (&other != this)
    {
    }
  return (*this);
}

ProtocolMap::~ProtocolMap(void)
{
}

void			ProtocolMap::action(ushort instruction,
					    PacketData & data)
{
  std::map<eProtocolPacketMap, ptr_func>::iterator it;
  ptr_func		ptr;

  if (instruction >= MAP_MAX)
    (void)this->actionError(data);
  if ((it = this->actionmap.find(static_cast<eProtocolPacketMap>(instruction))) == this->actionmap.end())
    (void)this->actionError(data);
  ptr = it->second;
  (this->*ptr)(data);
  //  (void)((this->*actionmap[static_cast<eProtocolContact>(instruction)]) //oldx
}

bool			ProtocolMap::actionError(PacketData &)
{
  return (true);
}

bool			ProtocolMap::actionGet(PacketData & data)
{
  return (true);
}

