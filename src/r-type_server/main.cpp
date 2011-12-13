
// #include	<cstdlib>
// #include	"rtype_server.h"

// int		main(void)
// {
//   return (rtype_server() ? EXIT_SUCCESS : EXIT_FAILURE);
// }

#include	"Server.hpp"

int		main(void)
{
  Server	server;

  if (server.init())
    {
      return (server.run());
    }
  return (0);
}
