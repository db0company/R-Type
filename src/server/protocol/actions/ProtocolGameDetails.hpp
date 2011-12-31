#ifndef		PROTOCOLGAMEDETAILS_HPP_
#define		PROTOCOLGAMEDETAILS_HPP_

# include	<map>
# include	"IProtocolAction.hpp"
# include	"PacketData.hpp"
# include	"eProtocolPacketGameDetails.hpp"

class		ProtocolGameDetails : public IProtocolAction
{
private:
  typedef bool (ProtocolGameDetails::*ptr_funct)(PacketData &, User *, Server &);
  std::map<eProtocolPacketGameDetails, ptr_funct>	actionmap;

public:

  ProtocolGameDetails(void);
  ProtocolGameDetails(ProtocolGameDetails const &);
  ProtocolGameDetails & operator=(ProtocolGameDetails const &);
  ~ProtocolGameDetails(void);
  virtual void action(ushort instruction, PacketData &data, User *, Server &);

private:
  bool		actionError(PacketData &data, User *, Server &);
  bool		actionPlayerLogin(PacketData &data, User *, Server &);
  bool		actionScore(PacketData &data, User *, Server &);
  bool		actionGetMap(PacketData &data, User *, Server &);
  bool		actionPlayerLife(PacketData &data, User *, Server &);
};

#endif			//PROTOCOLGAMEDETAILS_HPP_

