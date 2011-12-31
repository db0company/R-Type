#ifndef PROTOCOLMOVEMENT_H_
# define PROTOCOLMOVEMENT_H_

# include	<map>
# include	"iClientProtocolAction.hpp"
# include	"PacketData.hpp"
# include	"eProtocolPacketMovement.hpp"

class		ProtocolMovement : public iClientProtocolAction
{
private:
  typedef bool (ProtocolMovement::*ptr_funct)(PacketData &, Client &);
  std::map<eProtocolPacketMovement, ptr_funct>	actionmap;

public:

  ProtocolMovement(void);
  ~ProtocolMovement(void);
  ProtocolMovement(const ProtocolMovement&);
  ProtocolMovement&	operator=(const ProtocolMovement&);
  virtual void		action(ushort instruction, PacketData & data, Client&);
private:

  bool		actionError(PacketData &data, Client &);
  bool		actionMove(PacketData &data, Client &);
  bool		actionUpdatePlayer(PacketData &data, Client &);
  bool		actionUpdateEnemy(PacketData &data, Client &);
  bool		actionUpdateBullet(PacketData &data, Client &);
  bool		actionNewBullet(PacketData &data, Client &);
};

#endif	// PROTOCOLMOVEMENT_H_
