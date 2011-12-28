#ifndef		PROTOCOLGAMEDETAILS_HPP_
#define		PROTOCOLGAMEDETAILS_HPP_

# include	<map>
# include	"iProtocolAction.hpp"
# include	"PacketData.hpp"
# include	"eProtocolPacketGameDetails.hpp"

class		ProtocolGameDetails : public iProtocolAction
{
private:
  typedef bool (ProtocolGameDetails::*ptr_funct)(PacketData &);
  std::map<eProtocolPacketGameDetails, ptr_funct>	actionmap;

public:

  ProtocolGameDetails(void);
  ProtocolGameDetails(ProtocolGameDetails const &);
  ProtocolGameDetails & operator=(ProtocolGameDetails const &);
  ~ProtocolGameDetails(void);
  virtual void action(ushort instruction, PacketData &data);

private:
  bool		actionError(PacketData &data);
  bool		actionPlayerLogin(PacketData &data);
  bool		actionScore(PacketData &data);
  bool		actionGetMap(PacketData &data);
  bool		actionPlayerLife(PacketData &data);
};

#endif			//PROTOCOLGAMEDETAILS_HPP_

