
#ifndef			USERNETWORK_H_
# define		USERNETWORK_H_

# include		"ISocket.h"
# include		"ProtocolPacket.h"

class			UserSocket
{
/* ************************************************************************* */
/*                             Attributes                                    */
/* ************************************************************************* */
 private:
  bool					haveHeader;
  ProtocolPacketHeader			header;
  ISocket *				socket;

/* ************************************************************************* */
/*                             Coplien Form                                  */
/* ************************************************************************* */
 public:
  UserSocket(ISocket * socket);
  UserSocket(UserSocket const &);
  UserSocket &		operator=(UserSocket const &);
  ~UserSocket(void);

/* ************************************************************************* */
/*                             Getters/Setters                               */
/* ************************************************************************* */
 public:
  bool				getHaveHeader(void) const;
  void				setHaveHeader(bool);
  ProtocolPacketHeader &	getHeader(void);
  ISocket *			getSocket(void) const;
  void				setSocket(ISocket *);
  bool				isConnected(void) const;
};

#endif			// !USERNETWORK_H_

