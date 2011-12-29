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
  if (!this->_udp->SNCreate(ip, port))
    {
      std::cerr << "Error: Can't create socket udp" << std::endl;
      return (false);
    }
  if (!this->_tcp->SNConnect())
    {
      std::cerr << "Error: Can't connect to server " << ip
		<< " on port " << port << std::endl;
      return (false);
    }
  std::cout << "Connected to Server" << std::endl;
  this->_tcp->SNAddRead();
  this->_udp->SNAddRead();
  this->_tcp->SNAddWrite();
  return (true);
}

bool ClientNetwork::select(void)
{
  if (this->_selector)
    if (!this->_selector->SNSelect())
      {
	return (false);
      }
  return (true);
}

bool ClientNetwork::feedPacketAggregatorTCP(void)
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
  return (true);
}

// udp ok? todo a tester
bool ClientNetwork::feedPacketAggregatorUDP(void)
{
  int size;
  char buffer[1024] = {0};

  if (this->_udp->SNGetRead())
    {
      if ((size = this->_udp->SNRead(buffer, 1024)) <= 0)
	{
	  return (false);
	}
      else
	this->paReadUDP.concat(buffer, size);
    }
  return (true);
}

bool ClientNetwork::process(void)
{
  int				nb_packet;
  ProtocolPacket		*packet;

  nb_packet = this->paRead.aggregateCharToPackets();
  if (this->paRead.empty() && this->paReadUDP.empty())
    return (false);
  while (!this->paRead.empty())
    {
      packet = this->paRead.front();
      // ici on a le packet a executer!
      // serai parfait : packetManager->Process(packet);
      this->paRead.pop();
    }
  while (!this->paReadUDP.empty())
    {
      packet = this->paReadUDP.front();
      // ici on a le packet a executer!
      // serai parfait : packetManager->Process(packet);
      this->paReadUDP.pop();
    }
  return (true);
}

bool ClientNetwork::sendPacketToServer(void)
{
  unsigned int size;
  unsigned char	*msg;
  int nb;

  if (this->_tcp->SNGetWrite())
    {
      nb = this->paWrite.aggregatePacketToChar();
      if (nb > 0)
	{
	  std::cout << nb << "packet(s) to aggregate (TCP)" << std::endl;
	  size = this->paWrite.getSize();
	  msg = this->paWrite.getMsg();
	  this->_tcp->SNWrite(msg, size);
	  this->paWrite.erase(); //done ? todo
	}
    }
  nb = this->paWriteUDP.aggregatePacketToChar();
  if (nb > 0)
    {
      std::cout << nb << "packet(s) to aggregate (UDP)" << std::endl;
      size = this->paWriteUDP.getSize();
      msg = this->paWriteUDP.getMsg();
      this->_udp->SNWrite(msg, size);
      this->paWriteUDP.erase(); //done ? todo
    }
  return (true);
}

bool ClientNetwork::pushTCP(ProtocolPacket *t)
{
  this->paWrite.push(t);
  return (true);
}

bool ClientNetwork::pushUDP(ProtocolPacket *t)
{
  this->paWriteUDP.push(t);
  return (true);
}
