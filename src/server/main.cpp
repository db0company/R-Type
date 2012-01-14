#include	<cstdlib>
#include	"Server.hpp"
#include	"RecupMap.hpp"
#include	"Error.hpp"
// uint		v = 1;
// todo: parameters to set verbose mode

bool		rtype_server(void)
{
  Server	server;
  bool		ret;


  if (!server.init(12348))
    return (false);
  try
    {
      ret = server.run();
      return (ret);
    }
  catch (CustomError& e)
    {
      std::cout << e.what() << std::endl;
      return false;
    }
  return (false);
}

int		main(int , char **)
{
  return (rtype_server() ? EXIT_SUCCESS : EXIT_FAILURE);
}
