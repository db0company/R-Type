#include <cstring>
#include "PacketAggregator.hpp"
#include "PacketFactory.hpp"

PacketAggregator::PacketAggregator(void) : _index(0)
{
  memset(this->_buffer, 0, 4096);
}

PacketAggregator::~PacketAggregator(void)
{
}

PacketAggregator::PacketAggregator(const PacketAggregator& other)
{
  this->_packetQueue = other._packetQueue;
  memcpy(this->_buffer, other._buffer, 4096);
  this->_index = other._index;
}

PacketAggregator&	PacketAggregator::operator=(const PacketAggregator&other)
{
  this->_packetQueue = other._packetQueue;
  memcpy(this->_buffer, other._buffer, 4096);
  this->_index = other._index;
  return (*this);
}

bool PacketAggregator::concat(char *str, int size)
{
  if (size + this->_index > 4096)
    return (false);
  memcpy(this->_buffer + this->_index, str, size);
  // std::cout << "concat here " << size << " index:"  << this->_index << std::endl;
  this->_index += size;
  return (true);
}

int  PacketAggregator::aggregatePacketToChar(void)
{
  int		nb_packet = 0;
  ProtocolPacket *packet;
  int		 size;

  size = 0;
  if (this->_packetQueue.empty())
    return (0);

  while (!this->_packetQueue.empty())
    {
      packet = this->_packetQueue.front();
      size = sizeof(packet->header) +
	PacketFactory::getPacketDataSize(packet);
      if (size + this->_index > 4096)
	return (nb_packet);
      memcpy(this->_buffer + this->_index, &(packet->header),
	     sizeof(packet->header));
      this->_index += sizeof(packet->header);
      // std::cout << "size : " << PacketFactory::getPacketDataSize(packet) << std::endl;
      memcpy(this->_buffer + this->_index,
	     PacketFactory::getPacketData(packet)->getData(),
	     PacketFactory::getPacketDataSize(packet));
      this->_index += PacketFactory::getPacketDataSize(packet);
      this->_packetQueue.pop();
      nb_packet++;
    }
  return (nb_packet);
}

int  PacketAggregator::aggregateCharToPackets(void)
{
  int	nb_packet;

  nb_packet = 0;
  while (this->aggregateCharToPacket())
    {
      ++nb_packet;
    }
  return (nb_packet);
}

int  PacketAggregator::aggregateCharToPacket(void)
{
  ProtocolPacketHeader header;
  unsigned int next;
  unsigned char *packet_data;

  next = 0;
  // std::cout << "index(" << this->_index << ") sizeof("
  // 	    << sizeof(ProtocolPacketHeader) << ")" << std::endl;
  if (this->_index < sizeof(ProtocolPacketHeader))
    return (0);
  memcpy(&header, this->_buffer, sizeof(ProtocolPacketHeader));
  if (this->_index - sizeof(ProtocolPacketHeader) < header.size)
    return (0);

  packet_data = new unsigned char[header.size];
  // std::cout << "premier caracter ici:" << std::endl;
  // std::cout << "||"<< (int)this->_buffer[sizeof(ProtocolPacketHeader)] <<"||" <<std::endl;
  memcpy(packet_data, this->_buffer + sizeof(ProtocolPacketHeader), header.size);
  // std::cout << "::"<< (int)packet_data[0] <<"::" << packet_data[0] << " size: " << header.size << std::endl;
  ProtocolPacket * packet = PacketFactory::createPacket(static_cast<eProtocolPacketGroup>(header.group), header.instruction, packet_data, header.size);

  // ProtocolPacket * packet = PacketFactory::createPacket(static_cast<eProtocolPacketGroup>(header.group), header.instruction, this->_buffer + sizeof(ProtocolPacketHeader), header.size);
  this->_packetQueue.push(packet);
  next += sizeof(ProtocolPacketHeader) + PacketFactory::getPacketDataSize(packet);
  // std::cout << "je memmove (buffer[0], buffer["<< next << "], 4096 - " << next << ") = " << 4096 - next << std::endl;
  memmove(this->_buffer, &(this->_buffer[next]), 4096 - next);
  // std::cout << "je memset (buffer[" << next << "], 0, " << 4096 - next << ")" << std::endl;
  memset(&(this->_buffer)[this->_index - next], 0, 4096 - (this->_index - next));

  // std::cout << "next ====" << next << std::endl;
  // std::cout << "index ====" << this->_index << std::endl;
  if (this->_index == next)
    {
      // std::cout << "wtf?" << std::endl;
    }
  this->_index = this->_index - next;
  if (this->_index > 1000)
    {
      std::cout << " ???  " << next << " " << this->_index<< std::endl;
      exit(EXIT_FAILURE);
    }
  return (1);
}

bool PacketAggregator::empty(void)
{
  return (this->_packetQueue.empty());
}

ProtocolPacket *PacketAggregator::front(void)
{
  return (this->_packetQueue.front());
}

bool PacketAggregator::erase(void)
{
  while (!this->_packetQueue.empty())
    {
      this->_packetQueue.pop();
    }
  return (0);
}

bool PacketAggregator::pop(void)
{
  if (this->_packetQueue.empty())
    return (false);
  this->_packetQueue.pop();
  return (true);
}

bool PacketAggregator::push(ProtocolPacket *data)
{
  this->_packetQueue.push(data);
  return (true);
}

unsigned int PacketAggregator::getSize(void) const
{
  return (this->_index);
}

unsigned char* PacketAggregator::getMsg(void) const
{
  unsigned char *msg;

  msg = new unsigned char[this->_index];

  memcpy(msg, this->_buffer, this->_index);
  return (msg);
}
