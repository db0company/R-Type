
#ifndef			PROTOCOLPOSITION_H_
# define		PROTOCOLPOSITION_H_

# include		<map>
# include		"protocol/iProtocolAction.hpp"
# include		"protocol/PacketData.hpp"
# include		"eProtocolPacketPosition.hpp"

class			ProtocolPosition
  : public iProtocolAction
{
private:
  typedef bool	(ProtocolPosition::*ptr_func)(PacketData &);
  std::map<eProtocolPacketPosition, ptr_func>	actionmap;

public:
  ProtocolPosition();
  ProtocolPosition(ProtocolPosition const &);
  ProtocolPosition &		operator=(ProtocolPosition const &);
  ~ProtocolPosition(void);

public:
  virtual void		action(ushort instruction,
			       PacketData & data);
private:
  bool			actionError(PacketData & data);
  bool			actionMovePlayer(PacketData & data);
  bool			actionUpdatePlayer(PacketData & data);
  bool			actionUpdateEnemy(PacketData & data);
  bool			actionUpdateBullets(PacketData & data);
  bool			actionNewBullets(PacketData & data);
};

#endif			// !PROTOCOLPOSITION_H_

