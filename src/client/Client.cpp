#include <iostream>
#include "Client.hpp"

Client::Client(void) : cNetwork("", 0), cGraphic(cNetwork)
{}

Client::~Client(void)
{}

Client::Client(const Client&other) :
  cNetwork(other.cNetwork), cGraphic(cNetwork)
{}

Client&	Client::operator=(const Client&)
{
  return *this;
}

Client::Client(std::string const &ip, int port) :
  cNetwork(ip, port), cGraphic(cNetwork)
{
}

bool Client::init(void)
{
  if (!this->cGraphic.init())
    {
      std::cerr << "Error: Can't initialize sfml" << std::endl;
      return (false);
    }
  return (true);
}

bool Client::run(void)
{
  while (true)
    {
      this->cGraphic.getEvent();
      this->cGraphic.clean();
      this->cGraphic.draw();
    }
  return (true);
}
