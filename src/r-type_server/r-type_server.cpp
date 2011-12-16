
#include	"Server.hpp"
#include	"rtype_server.h"

uint		v = 1;
// todo: parameters to set verbose mode

bool		rtype_server(void)
{
  Server	server;

  if (!server.init())
    return (false);
  return (server.run());
}
