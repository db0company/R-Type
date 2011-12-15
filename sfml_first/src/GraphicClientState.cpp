#include "GraphicClientState.hpp"

LibGraphic::GraphicClientState::GraphicClientState(std::string const & state):
  _name(state)
{
}

LibGraphic::GraphicClientState::~GraphicClientState(void)
{
}

std::string const & LibGraphic::GraphicClientState::getName() const
{
  return this->_name;
}
