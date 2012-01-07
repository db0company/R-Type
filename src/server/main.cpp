#include	<cstdlib>
#include	"Server.hpp"
#include	"RecupMap.hpp"

uint		v = 1;
// todo: parameters to set verbose mode

bool		rtype_server(void)
{
  Server	server;

  if (!server.init(12348))
    return (false);
  return (server.run());
}

int		main(int ac, char **av)
{
  return (rtype_server() ? EXIT_SUCCESS : EXIT_FAILURE);
}
