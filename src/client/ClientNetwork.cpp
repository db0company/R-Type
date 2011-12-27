#include "ISocket.h"
#include "ISelector.h"
#include "ATCPClientSocket.h"
#include "ATCPServerSocket.h"
#include "Selector.hpp"
#ifdef _WIN32
# include "TCPClientSocketWindows.h"
# include "TCPServerSocketWindows.h"
# include "UDPServerSocketWindows.h"
# include "UDPClientSocketWindows.h"
# include "DirectoryManagerWindows.hpp"
#else
# include "TCPClientSocketUnix.h"
# include "TCPServerSocketUnix.h"
# include "UDPServerSocketUnix.h"
# include "UDPClientSocketUnix.h"
# include "DirectoryManagerUnix.hpp"
# include <cstring>
#endif
#include "ClientNetwork.hpp"
