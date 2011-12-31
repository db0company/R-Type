#ifndef			PROTOCOLACTION_H_
# define		PROTOCOLACTION_H_

# include		"types.h"
# include		"PacketData.hpp"

class			iProtocolAction
{
 public:
  virtual ~iProtocolAction(void) {};

 public:
  virtual void		action(ushort instruction, PacketData & data) = 0;
};

#endif			// !PROTOCOLACTION_H_
