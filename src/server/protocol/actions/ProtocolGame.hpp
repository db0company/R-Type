
#ifndef			PROTOCOLGAME_H_
# define		PROTOCOLGAME_H_

# include		<map>
# include		"IProtocolAction.hpp"
# include		"PacketData.hpp"
# include		"eProtocolPacketGame.hpp"

class			ProtocolGame
  : public IProtocolAction
{
private:
  typedef bool	(ProtocolGame::*ptr_func)(PacketData &, User *, Server &);
  std::map<eProtocolPacketGame, ptr_func>	actionmap;

public:
  ProtocolGame(void);
  ProtocolGame(ProtocolGame const &);
  ProtocolGame &		operator=(ProtocolGame const &);
  ~ProtocolGame(void);

public:
  virtual void		action(ushort instruction,
			       PacketData & data, User *, Server &);
private:
  bool			actionError(PacketData & data, User *, Server &);
  bool			actionGet(PacketData & data, User *, Server &);
  bool			actionGetLevel(PacketData & data, User *, Server &);
  bool			actionCreate(PacketData & data, User *, Server &);
  bool			actionJoin(PacketData & data, User *, Server &);
  bool			actionQuit(PacketData & data, User *, Server &);
  // bool			actionEnd(PacketData & data, User *, Server &);
  bool			actionStart(PacketData & data, User *, Server &);
};

#endif			// !PROTOCOLGAME_H_

