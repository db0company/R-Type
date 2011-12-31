#ifndef			CLIENTPROTOCOLACTION_H_
# define		CLIENTPROTOCOLACTION_H_

# include "types.h"
# include "PacketData.hpp"

class Client;
class			IClientProtocolAction
{
 public:
  virtual ~IClientProtocolAction(void) {}

 public:
  virtual void		action(ushort instruction, PacketData &data, Client&) = 0;
};

#endif			// !CLIENTPROTOCOLACTION_H_
