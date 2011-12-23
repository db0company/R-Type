
#include	<cstdlib>
#include	"Server.hpp"

uint		v = 1;
// todo: parameters to set verbose mode

bool		rtype_server(void)
{
  Server	server;

  if (!server.init())
    return (false);
  return (server.run());
}

int		main(void)
{
  return (rtype_server() ? EXIT_SUCCESS : EXIT_FAILURE);
}
