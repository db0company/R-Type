
#ifndef			PROTOCOLACTION_H_
# define		PROTOCOLACTION_H_

# include		"types.h"
# include		"PacketData.hpp"

class			iProtocolAction
{
/* ************************************************************************* */
/*                             Virtual Destructor                            */
/* ************************************************************************* */
 public:
  virtual ~iProtocolAction(void) {};

/* ************************************************************************* */
/*                             Interface Methods                             */
/* ************************************************************************* */
 public:
  virtual void		action(ushort instruction, PacketData & data);
  // todo: add informations about the socket.
};

#endif			// !PROTOCOLACTION_H_

