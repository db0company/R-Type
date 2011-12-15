
#include	"Server.hpp"
#include	"rtype_server.h"

bool		rtype_server(void)
{
  Server	server;

  if (!server.init())
    return (false);
  return (server.run());
}
