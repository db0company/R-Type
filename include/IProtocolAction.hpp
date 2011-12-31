#ifndef			PROTOCOLACTION_H_
# define		PROTOCOLACTION_H_

# include		"types.h"
# include		"PacketData.hpp"
class User;
class Server;
class			IProtocolAction
{
 public:
  virtual ~IProtocolAction(void) {};

 public:
  virtual void		action(ushort instruction, PacketData & data, User *, Server&) = 0;
};

#endif			// !PROTOCOLACTION_H_
