#ifndef PROTOCOLMOVEMENT_H_
# define PROTOCOLMOVEMENT_H_

# include	<map>
# include	"IProtocolAction.hpp"
# include	"PacketData.hpp"
# include	"eProtocolPacketMovement.hpp"

class		ProtocolMovement : public IProtocolAction
{
private:
  typedef bool (ProtocolMovement::*ptr_funct)(PacketData &, User *, Server &);
  std::map<eProtocolPacketMovement, ptr_funct>	actionmap;

public:

  ProtocolMovement(void);
  ~ProtocolMovement(void);
  ProtocolMovement(const ProtocolMovement&);
  ProtocolMovement&	operator=(const ProtocolMovement&);
  virtual void action(ushort instruction, PacketData &data, User *, Server &);

private:
  bool		actionError(PacketData &data, User *, Server &);
  bool		actionMove(PacketData &data, User *, Server &);
  bool		actionUpdatePlayer(PacketData &data, User *, Server &);
  bool		actionUpdateEnemy(PacketData &data, User *, Server &);
  bool		actionUpdateBullet(PacketData &data, User *, Server &);
  bool		actionNewBullet(PacketData &data, User *, Server &);
};

#endif	// PROTOCOLMOVEMENT_H_
