#ifndef  CLIENTNETWORK_H_
# define CLIENTNETWORK_H_

#include <iostream>
#include <string>

class		ClientNetwork
{
public:
  ClientNetwork(void);
  ~ClientNetwork(void);
  ClientNetwork(const ClientNetwork&);
  ClientNetwork&	operator=(const ClientNetwork&);

private:

  ATCPClientSocket *_tcp;
  ISocket	   *_udp;
  ISelector	   *_selector;
};

#endif	// CLIENTNETWORK_H_
