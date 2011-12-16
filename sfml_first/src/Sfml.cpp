#include <cstdlib>
#include <iostream>
#include <fstream>
#include <sstream>
#include "Sfml.hpp"
#include "GraphicClientState.hpp"

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
  this->_app.Create(sf::VideoMode::GetMode(0), WINDOWNAME,
		    sf::Style::Fullscreen);
  if (!this->_app.IsOpened())
    return false;
  this->_width = sf::VideoMode::GetMode(0).Width;
  this->_height = sf::VideoMode::GetMode(0).Height;
  this->loadRessources();
  this->createStates();
  return true;
}

LibGraphic::Event LibGraphic::Sfml::getEvent()
{
  sf::Event Event;

  while (this->_app.GetEvent(Event))
    {
      if (Event.Type == sf::Event::KeyPressed)
	{
	  switch (Event.Key.Code)
	    {
	    case sf::Key::Escape:
	      //return LibGraphic::__EVENT_QUIT;
	      {
		this->_app.Close();
		exit(EXIT_SUCCESS);
	      }
	    default:
	      break;
	    }
	}
    }
  return LibGraphic::EVENT_NONE;
}

void LibGraphic::Sfml::quit()
{
  this->_app.Close();
}

void LibGraphic::Sfml::clean()
{
  this->_app.Clear();
  this->_app.Draw((*this->_ressourcesSprite.find("StartBackground")).second->_sprite);

  MyMusic * song = this->_ressourcesPlayList["StartBackground"];
  if (song->GetMusicState() == sf::Music::Stopped ||
      song->GetMusicState() == sf::Music::Paused)
    song->PlayMusic();
}

void LibGraphic::Sfml::draw()
{
  this->_app.Display();
}

bool LibGraphic::Sfml::loadRessources()
{
  if (this->loadSprite() && this->loadMusic())
    return true;
  return false;
}

bool LibGraphic::Sfml::loadSprite()
{
  std::fstream ressourceFile;
  std::string s;
  unsigned int found;
  unsigned int rfound;
  LibGraphic::GraphicRessource * img;
  std::string tmp;
  std::string tmpImagePath;

  ressourceFile.open("ressources/.ressources_images");
  if (!ressourceFile.is_open())
    {
      std::cerr << "[EXEPTION][Sfml.cpp] : fail to open " <<"ressources/.ressources_images" << std::endl;
      // throw
      return false;
    }
  while (ressourceFile.good())
    {
      getline(ressourceFile, s);
      if ((found = s.find("::")) != std::string::npos &&
	  (rfound = s.rfind("::")) != std::string::npos)
	{
	  tmp = s.substr(0, found);
	  img = new LibGraphic::GraphicRessource;
	  tmpImagePath = "ressources/images/" +
	    s.substr(found + 2, rfound - (found + 2));
	  if (!img->_image.LoadFromFile(tmpImagePath))
	    {
	      std::cerr <<
		"[EXEPTION][Sfml.cpp] : Fail to load " <<
		tmpImagePath << std::endl;
	      // throw
	    }
	  img->_sprite.SetImage(img->_image);
	  if (isFullscreen(s.substr(rfound + 2, 1)))
	    {
	      img->_isFullScreen = true;
	      img->_sprite.Resize(this->_width,
				  this->_height);
	    }
	  this->_ressourcesSprite[tmp] = img;
	}
    }
  return true;
}

bool LibGraphic::Sfml::loadSound()
{
  std::fstream ressourceFile;
  std::string s;
  unsigned int found;
  std::string tmp;
  MySound * song;

  ressourceFile.open("ressources/.ressources_sounds");
  if (!ressourceFile.is_open())
    {
      std::cerr << "[EXEPTION][Sfml.cpp] : fail to open " <<"ressources/.ressources_sounds" << std::endl;
      // throw
      return false;
    }
  while (ressourceFile.good())
    {
      getline(ressourceFile, s);
      if ((found = s.find("::")) != std::string::npos)
	{
	  tmp = s.substr(0, found);
	  song = new MySound("ressources/sounds/" + s.substr(found + 2,
				      s.size() - found + 1));
	}
      this->_ressourcesSounds[tmp] = song;
    }
  return true;
}

bool LibGraphic::Sfml::loadMusic()
{
  std::fstream ressourceFile;
  std::string s;
  unsigned int found;
  std::string tmp;
  MyMusic * song;

  ressourceFile.open("ressources/.ressources_musics");
  if (!ressourceFile.is_open())
    {
      std::cerr << "[EXEPTION][Sfml.cpp] : fail to open " <<"ressources/.ressources_musics" << std::endl;
      // throw
      return false;
    }
  while (ressourceFile.good())
    {
      getline(ressourceFile, s);
      if ((found = s.find("::")) != std::string::npos)
	{
	  tmp = s.substr(0, found);
	  song = new MyMusic("ressources/musics/" + s.substr(found + 2,
				      s.size() - found + 1));
	}
      this->_ressourcesPlayList[tmp] = song;
    }
  return true;
}

bool LibGraphic::Sfml::createStates()
{
  this->_statesMap[START] = this->createStateStart();
  this->_statesMap[INGAME] = this->createStateIngame();
  return true;
}

LibGraphic::GraphicClientState * LibGraphic::Sfml::createStateStart()
{
  return (new LibGraphic::GraphicClientState("Start"));
}

LibGraphic::GraphicClientState * LibGraphic::Sfml::createStateIngame()
{
  return (new LibGraphic::GraphicClientState("Ingame"));
}

inline bool LibGraphic::Sfml::isFullscreen(std::string s)
{
  std::stringstream ss;
  int tmp;

  ss << s;
  ss >> tmp;
  if (tmp)
    return true;
  return false;
}

inline std::string LibGraphic::Sfml::getNextInfoRessource(std::string & s)
{
  unsigned int found;

  if ((found = s.find("::")) == std::string::npos)
    return s;
  return (s.substr(0, found));
}
