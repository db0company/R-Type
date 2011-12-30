#include <cstdlib>
#include <iostream>
#include <fstream>
#include <sstream>
#include "Sfml.hpp"
#include "GraphicClientState.hpp"
#include "ClientNetwork.hpp"

extern LibGraphic::Volume gVolume;

// LibGraphic::Sfml::Sfml(void)
// {
//}

LibGraphic::Sfml::Sfml(ClientNetwork &cn) :
  _network(cn)
{
}

LibGraphic::Sfml::~Sfml(void)
{
}

bool LibGraphic::Sfml::init()
{
  #ifndef _WIN32
  if (!getenv("DISPLAY"))
    return false;
  #endif
  this->_app.Create(sf::VideoMode::GetMode(0), WINDOWNAME,
  		    sf::Style::Fullscreen);
  if (!this->_app.IsOpened())
    return false;
  this->_width = sf::VideoMode::GetMode(0).Width;
  this->_height = sf::VideoMode::GetMode(0).Height;
  gVolume.musicVolume = 50;
  gVolume.soundVolume = 50;
  this->loadRessources();
  this->createStates();
  this->_currentState = START;
  return true;
}

LibGraphic::Event LibGraphic::Sfml::getEvent()
{
  switch (this->_graphicState->getEventFromState(this->_currentState))
    {
    case EVENT_CHANGE_STATE :
      {
	this->_currentState = this->_graphicState->goToNextState(this->_currentState);
	break;
      }
    default : break;
    }
  LibGraphic::EVENT_NONE;
}

void LibGraphic::Sfml::quit()
{
  this->_app.Close();
}

void LibGraphic::Sfml::clean()
{
  this->_app.Clear();
}

void LibGraphic::Sfml::draw()
{
  this->_graphicState->draw(this->_currentState);
  this->_app.Display();
}

bool LibGraphic::Sfml::loadRessources()
{
  if (this->loadSprite() &&
      this->loadMusic() &&
      this->loadFont())
    return true;
  return false;
}

bool LibGraphic::Sfml::loadFont()
{
  std::fstream ressourceFile;
  std::string s;
  std::string tmp;
  sf::Font * font;

  ressourceFile.open("ressources/.ressources_fonts");
  if (!ressourceFile.is_open())
    {
      std::cerr << "[EXEPTION][Sfml.cpp] : fail to open " <<"ressources/.ressources_fonts" << std::endl;
      // throw
      return false;
    }
  while (ressourceFile.good())
    {
      getline(ressourceFile, s);
      tmp = this->getNextInfoRessource(s);
      font = new sf::Font;
      if (!font->LoadFromFile("ressources/fonts/" +
			      this->getNextInfoRessource(s)))
	{
	  std::cerr << "[EXEPTION][Sfml.cpp] : fail to load " << tmp << std::endl;
	}
      this->_ressourcesFont[tmp] = font;
    }
  return true;
}

bool LibGraphic::Sfml::loadSprite()
{
  std::fstream ressourceFile;
  std::string s;
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
      tmp = this->getNextInfoRessource(s);
      img = new LibGraphic::GraphicRessource;
      tmpImagePath = "ressources/images/" +
	this->getNextInfoRessource(s);
      if (!img->_image.LoadFromFile(tmpImagePath))
	{
	  std::cerr <<
	    "[EXEPTION][Sfml.cpp] : Fail to load " <<
	    tmpImagePath << std::endl;
	  // throw
	}
      img->_sprite.SetImage(img->_image);
      if (isFullscreen(this->getNextInfoRessource(s)))
	{
	  img->_isFullScreen = true;
	  img->_sprite.Resize(this->_width,
			      this->_height);
	}
      else
	{
	  img->_isFullScreen = false;
	  img->_dimension.width = this->getIntFromS(this->getNextInfoRessource(s));
	  img->_dimension.height = this->getIntFromS(this->getNextInfoRessource(s));
	}
      this->_ressourcesSprite[tmp] = img;
    }
  return true;
}

bool LibGraphic::Sfml::loadSound()
{
  std::fstream ressourceFile;
  std::string s;
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
      tmp = this->getNextInfoRessource(s);
      song = new MySound("ressources/sounds/" +
			 this->getNextInfoRessource(s));
      this->_ressourcesSounds[tmp] = song;
    }
  gVolume.soundVolume = 10;
  return true;
}

bool LibGraphic::Sfml::loadMusic()
{
  std::fstream ressourceFile;
  std::string s;
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
      tmp = this->getNextInfoRessource(s);
	  song = new MyMusic("ressources/musics/" +
			     this->getNextInfoRessource(s));
      this->_ressourcesPlayList[tmp] = song;
    }
  gVolume.musicVolume = 50;
  return true;
}

void LibGraphic::Sfml::createStates()
{
  this->_graphicState =
    new GraphicClientState(this->_ressourcesSprite,
			   this->_ressourcesPlayList,
			   this->_ressourcesSounds,
			   this->_ressourcesFont,
			   this->_app);
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
  unsigned long int found;
  std::string tmp;

  if ((found = s.find("::")) == std::string::npos)
    return s;
  tmp = s.substr(0, found);
  s = s.substr(found + 2, s.size());
  return tmp;
}

inline unsigned int LibGraphic::Sfml::getIntFromS(std::string s)
{
  unsigned int found;
  unsigned int res;
  std::string tmp;
  std::stringstream ss;

  found = s.find("::");
  tmp = s.substr(0, found);
  s = s.substr(found + 2, s.size());
  ss << tmp;
  ss >> res;
  return (res);
}
