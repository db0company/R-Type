#ifndef		PROTOCOLGAMEDETAILS_HPP_
#define		PROTOCOLGAMEDETAILS_HPP_

# include	<map>
# include	"IClientProtocolAction.hpp"
# include	"PacketData.hpp"
# include	"eProtocolPacketGameDetails.hpp"

class		ProtocolGameDetails : public IClientProtocolAction
{
private:
  typedef bool (ProtocolGameDetails::*ptr_funct)(PacketData &, Client &);
  std::map<eProtocolPacketGameDetails, ptr_funct>	actionmap;

public:

  ProtocolGameDetails(void);
  ProtocolGameDetails(ProtocolGameDetails const &);
  ProtocolGameDetails & operator=(ProtocolGameDetails const &);
  ~ProtocolGameDetails(void);
  virtual bool action(ushort instruction, PacketData &data,Client&);

private:
  bool		actionError(PacketData &data, Client &);
  bool		actionPlayerLogin(PacketData &data, Client &);
  bool		actionScore(PacketData &data, Client &);
  bool		actionGetMap(PacketData &data, Client &);
  bool		actionPlayerLife(PacketData &data, Client &);
  bool		actionPlayerKill(PacketData &, Client &);
  bool		actionMonsterKill(PacketData &, Client &);
};

#endif			//PROTOCOLGAMEDETAILS_HPP_

