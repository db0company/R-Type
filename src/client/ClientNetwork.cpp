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

ClientNetwork::ClientNetwork(void) : _ip(""), _port(0)
{
#ifndef _WIN32
  this->_selector = new Selector<int>;
  this->_tcp = new TCPClientSocketUnix(this->_selector);
  this->_udp = new UDPClientSocketUnix(this->_selector);
#else
  this->_selector = new Selector<SOCKET>;
  this->_tcp = new TCPClientSocketWindows(this->_selector);
  this->_udp = new UDPClientSocketWindows(this->_selector);
#endif
}


ClientNetwork::ClientNetwork(std::string const &ip, int port) : _ip(ip), _port(port)
{
#ifndef _WIN32
  this->_selector = new Selector<int>;
  this->_tcp = new TCPClientSocketUnix(this->_selector);
  this->_udp = new UDPClientSocketUnix(this->_selector);
#else
  this->_selector = new Selector<SOCKET>;
  this->_tcp = new TCPClientSocketWindows(this->_selector);
  this->_udp = new UDPClientSocketWindows(this->_selector);
#endif
}

void ClientNetwork::init(std::string const &ip, int port)
{
  this->_ip = ip;
  this->_port = port;
}

ClientNetwork::~ClientNetwork(void)
{
}

ClientNetwork::ClientNetwork(const ClientNetwork&other)
{
  this->_tcp = other._tcp;
  this->_udp = other._udp;
  this->_selector = other._selector;
}

ClientNetwork&	ClientNetwork::operator=(const ClientNetwork&other)
{
  this->_tcp = other._tcp;
  this->_udp = other._udp;
  this->_selector = other._selector;
  return (*this);
}

bool ClientNetwork::connect(std::string const &ip, int port)
{
  if (!this->_tcp->SNCreate(ip, port))
    {
      std::cerr << "Error: Can't create socket" << std::endl;
      return (false);
    }
  if (!this->_tcp->SNConnect())
    {
      std::cerr << "Error: Can't connect to server " << ip
		<< " on port " << port << std::endl;
      return (false);
    }
  this->_tcp->SNAddRead();
  return (true);
}

bool ClientNetwork::connect(void)
{
  if (!this->_tcp->SNCreate(this->_ip, this->_port))
    {
      std::cerr << "Error: Can't create socket" << std::endl;
      return (false);
    }
  if (!this->_tcp->SNConnect())
    {
      std::cerr << "Error: Can't connect to server " << this->_ip
		<< " on port " << this->_port << std::endl;
      return (false);
    }
  this->_tcp->SNAddRead();
  return (true);
}

bool ClientNetwork::select(void)
{
  if (this->_selector)
    return (this->_selector->SNSelect());
  return (false);
}

bool ClientNetwork::feedPacketAggregator(void)
{
  int size;
  char buffer[1024] = {0};

  if (this->_tcp->SNGetRead())
    {
      if ((size = this->_tcp->SNRead(buffer, 1024)) <= 0)
	{
	  return (false);
	}
      else
	this->paRead.concat(buffer, size);
    }
  //idem udp.
  return (true);
}

bool ClientNetwork::process(void)
{
  int				nb_packet;
  ProtocolPacket		*packet;

  nb_packet = this->paRead.aggregateCharToPackets();
  if (this->paRead.empty())
    return (false);
  while (!this->paRead.empty())
    {
      packet = this->paRead.front();
      // ici on a le packet a executer!
      // serai parfait : packetManager->Process(packet);
      this->paRead.pop();
    }
  return (true);
}

bool ClientNetwork::sendPackettoServer(void)
{
  unsigned int size;
  unsigned char	*msg;
  int nb;

  if (this->_tcp->SNGetWrite())
    {
      nb = this->paWrite.aggregatePacketToChar();
      if (nb > 0)
	{
	  size = this->paWrite.getSize();
	  msg = this->paWrite.getMsg();
	  this->_tcp->SNWrite(msg, size);
	  this->paWrite.erase(); //done ? todo
	}
      return (true);
    }
  return (false);
}
