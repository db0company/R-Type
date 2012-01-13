#ifndef PROTOCOLMOVEMENT_H_
# define PROTOCOLMOVEMENT_H_

# include	<map>
# include	"IClientProtocolAction.hpp"
# include	"PacketData.hpp"
# include	"eProtocolPacketMovement.hpp"

class		ProtocolMovement : public IClientProtocolAction
{
private:
  typedef bool (ProtocolMovement::*ptr_funct)(PacketData &, Client &);
  std::map<eProtocolPacketMovement, ptr_funct>	actionmap;

public:

  ProtocolMovement(void);
  ~ProtocolMovement(void);
  ProtocolMovement(const ProtocolMovement&);
  ProtocolMovement&	operator=(const ProtocolMovement&);
  virtual bool		action(ushort instruction, PacketData & data, Client&);
private:

  bool		actionError(PacketData &data, Client &);
  bool		actionMove(PacketData &data, Client &);
  bool		actionUpdatePlayer(PacketData &data, Client &);
  bool		actionUpdateEnemy(PacketData &data, Client &);
  bool		actionUpdateBullet(PacketData &data, Client &);
  bool		actionCollision(PacketData &data, Client &);
  bool		actionNewBullet(PacketData &data, Client &);
};

#endif	// PROTOCOLMOVEMENT_H_
