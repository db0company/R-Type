
#ifndef			PROTOCOLGAME_H_
# define		PROTOCOLGAME_H_

# include		<map>
# include		"iProtocolAction.hpp"
# include		"PacketData.hpp"
# include		"eProtocolPacketGame.hpp"

class			ProtocolGame
  : public iProtocolAction
{
private:
  typedef bool	(ProtocolGame::*ptr_func)(PacketData &);
  std::map<eProtocolPacketGame, ptr_func>	actionmap;

public:
  ProtocolGame(void);
  ProtocolGame(ProtocolGame const &);
  ProtocolGame &		operator=(ProtocolGame const &);
  ~ProtocolGame(void);

public:
  virtual void		action(ushort instruction,
			       PacketData & data);
private:
  bool			actionError(PacketData & data);
  bool			actionGet(PacketData & data);
  bool			actionGetLevel(PacketData & data);
  bool			actionCreate(PacketData & data);
  bool			actionJoin(PacketData & data);
  bool			actionQuit(PacketData & data);
  bool			actionEnd(PacketData & data);
  bool			actionStart(PacketData & data);
};

#endif			// !PROTOCOLGAME_H_

