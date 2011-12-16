
#ifndef			PROTOCOLMAP_H_
# define		PROTOCOLMAP_H_

# include		<map>
# include		"protocol/iProtocolAction.hpp"
# include		"protocol/PacketData.hpp"
# include		"eProtocolPacketMap.hpp"

class			ProtocolMap
  : public iProtocolAction
{
private:
  typedef bool	(ProtocolMap::*ptr_func)(PacketData &);
  std::map<eProtocolPacketMap, ptr_func>	actionmap;

public:
  ProtocolMap();
  ProtocolMap(ProtocolMap const &);
  ProtocolMap &		operator=(ProtocolMap const &);
  ~ProtocolMap(void);

public:
  virtual void		action(ushort instruction,
			       PacketData & data);
private:
  bool			actionError(PacketData & data);

  bool			actionGet(PacketData & data);
};

#endif			// !PROTOCOLMAP_H_

