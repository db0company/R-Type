#include <iostream>
#include <string>

#include "Button.hpp"

LibGraphic::Button::Button(int x, int y, eDesign design, GraphicRessource const & sprite, std::string text):
  _design(design), _associatedSprite(sprite), _text(text)
{
  this->_coord.x = x;
  this->_coord.y = y;
}

LibGraphic::Button::~Button(void)
{
}

bool LibGraphic::Button::createButton()
{
  return (true);
}

int LibGraphic::Button::getX() const
{
  return _coord.x;
}

int LibGraphic::Button::getY() const
{
  return _coord.y;
}

void LibGraphic::Button::setX(int x)
{
  this->_coord.x = x;
}

void LibGraphic::Button::setY(int y)
{
  this->_coord.y = y;
}

LibGraphic::eDesign LibGraphic::Button::getDesign() const
{
  return this->_design;
}

void LibGraphic::Button::setDesign(eDesign design)
{
  this->_design = design;
}

std::string const & LibGraphic::Button::getText() const
{
  return this->_text;
}

void LibGraphic::Button::setText(std::string const & text)
{
  this->_text = text;
}
