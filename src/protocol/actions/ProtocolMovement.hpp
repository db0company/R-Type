#ifndef PROTOCOLMOVEMENT_H_
# define PROTOCOLMOVEMENT_H_

# include	<map>
# include	"protocol/iProtocolAction.hpp"
# include	"protocol/PacketData.hpp"
# include	"eProtocolPacketMovement.hpp"

class		ProtocolMovement : public iProtocolAction
{
private:
  typedef bool (ProtocolMovement::*ptr_funct)(PacketData &);
  std::map<eProtocolPacketMovement, ptr_funct>	actionmap;

public:

  ProtocolMovement(void);
  ~ProtocolMovement(void);
  ProtocolMovement(const ProtocolMovement&);
  ProtocolMovement&	operator=(const ProtocolMovement&);
  virtual void action(ushort instruction, PacketData &data);

private:

  bool		actionError(PacketData &data);
  bool		actionMove(PacketData &data);
  bool		actionUpdatePlayer(PacketData &data);
  bool		actionUpdateEnemy(PacketData &data);
  bool		actionUpdateBullet(PacketData &data);
  bool		actionNewBullet(PacketData &data);
};

#endif	// PROTOCOLMOVEMENT_H_
