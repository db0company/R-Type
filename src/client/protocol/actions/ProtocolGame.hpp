
#ifndef			PROTOCOLGAME_H_
# define		PROTOCOLGAME_H_

# include		<map>
# include		"IClientProtocolAction.hpp"
# include		"PacketData.hpp"
# include		"eProtocolPacketGame.hpp"

class			ProtocolGame: public IClientProtocolAction
{
private:
  typedef bool	(ProtocolGame::*ptr_func)(PacketData &, Client &);
  std::map<eProtocolPacketGame, ptr_func>	actionmap;

public:
  ProtocolGame(void);
  ProtocolGame(ProtocolGame const &);
  ProtocolGame &		operator=(ProtocolGame const &);
  ~ProtocolGame(void);

public:
  virtual bool		action(ushort instruction, PacketData & data, Client&);
private:
  bool			actionError(PacketData & data, Client &);
  bool			actionGet(PacketData & data, Client &);
  bool			actionGetLevel(PacketData & data, Client &);
  bool			actionCreate(PacketData & data, Client &);
  bool			actionJoin(PacketData & data, Client &);
  bool			actionQuit(PacketData & data, Client &);
  bool			actionEnd(PacketData & data, Client &);
  bool			actionStart(PacketData & data, Client &);
};

#endif			// !PROTOCOLGAME_H_

