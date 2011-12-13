#include <iostream>
#include <SFML/Graphics.hpp>
#include "Sfml.hpp"

LibGraphic::Sfml::Sfml(void)
{
}

LibGraphic::Sfml::~Sfml(void)
{
}

bool LibGraphic::Sfml::init()
{
  #ifndef _Win32
  if (!getenv("DISPLAY"))
    return false;
  #endif
  this->App.Create(sf::VideoMode::GetMode(0), WINDOWNAME, sf::Style::Fullscreen);
  if (!this->App.IsOpened())
    return false;
  return true;
}

LibGraphic::Event LibGraphic::Sfml::getEvent()
{
  sf::Event Event;

  while (App.GetEvent(Event))
    {
      if (Event.Type == sf::Event::KeyPressed)
	{
	  switch (Event.Key.Code)
	    {
	    case sf::Key::Escape:
	      return LibGraphic::__EVENT_QUIT;
	    default:
	      break;
	    }
	}
    }
  return LibGraphic::__EVENT_NONE;
}

void LibGraphic::Sfml::quit()
{
  this->App.Close();
}

void LibGraphic::Sfml::clean()
{
  this->App.Clear();
}

void LibGraphic::Sfml::draw()
{
  this->App.Display();
}

extern "C"
{
  LibGraphic::IGraphic * getLib()
  {
    return new LibGraphic::Sfml();
  }
}
