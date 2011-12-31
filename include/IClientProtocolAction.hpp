#ifndef			CLIENTPROTOCOLACTION_H_
# define		CLIENTPROTOCOLACTION_H_

# include "types.h"
# include "PacketData.hpp"
// # include "Client.hpp"

class Client;
class			iClientProtocolAction
{
 public:
  virtual ~iClientProtocolAction(void) {}

 public:
  virtual void		action(ushort instruction, PacketData &data, Client&) = 0;
};

#endif			// !CLIENTPROTOCOLACTION_H_
