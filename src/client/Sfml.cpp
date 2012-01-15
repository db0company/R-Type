#include <cstdlib>
#include <iostream>
#include <fstream>
#include <sstream>
#include "Sfml.hpp"
#include "GraphicClientState.hpp"
#include "ClientNetwork.hpp"
#include "Language.hpp"
#include "SpriteInfo.hpp"
#include "AMonsterMovement.hpp"
#include "IAnnim.hpp"

extern LibGraphic::Volume gVolume;
extern LibGraphic::Language language;

bool errorToPrint = false;
bool helpToShow = false;

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
  gVolume.musicVolume = 5;
  gVolume.soundVolume = 50;
  language = ENGLISH;
  if (!this->loadRessources())
    return false;
  this->createStates();
  this->_currentState = START;
  this->_errorClock.Reset();
  return true;
}

void		LibGraphic::Sfml::goToNextState(void)
{
  this->_currentState = this->_graphicState->goToNextState(this->_currentState);
}

LibGraphic::Event LibGraphic::Sfml::getEvent()
{
  LibGraphic::Event event = this->_graphicState->getEventFromState(this->_currentState);
  return (event);
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
  sf::String tmp;
  sf::Sprite help;

  this->_graphicState->draw(this->_currentState);
  if (errorToPrint && this->_errorClock.GetElapsedTime() > 5)
    {
      errorToPrint = false;
      this->_errorClock.Reset();
    }
  else if (errorToPrint)
    {
      tmp.SetText(this->_errorMessage);
      tmp.SetColor(sf::Color(255,0,0, 255));
      this->_app.Draw(tmp);
    }
  else
    this->_errorClock.Reset();
  if (helpToShow)
    {
      help = this->getSprite("help");
      help.SetColor(sf::Color(255,255,255,200));
      help.SetPosition(350, 80);
      this->_app.Draw(help);
    }
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
      exit(EXIT_FAILURE);
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
      exit(EXIT_FAILURE);
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

	  exit(EXIT_FAILURE);
	  // throw
	  return (false);
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

      exit(EXIT_FAILURE);
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
      exit(EXIT_FAILURE);
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

std::string const & LibGraphic::Sfml::getLogin() const
{
  return this->_graphicState->getLogin();
}

std::string const & LibGraphic::Sfml::getIp() const
{
  return this->_graphicState->getIp();
}

int LibGraphic::Sfml::getPort() const
{
  return this->_graphicState->getPort();
}

int LibGraphic::Sfml::getIdGame() const
{
  return this->_graphicState->getIdGame();
}

std::string const & LibGraphic::Sfml::getLevel() const
{
  return this->_graphicState->getLevel();
}

int LibGraphic::Sfml::getSlot() const
{
  return this->_graphicState->getSlot();
}

bool LibGraphic::Sfml::getSpectator() const
{
  return this->_graphicState->getSlot();
}

std::string const & LibGraphic::Sfml::getMessage() const
{
  return this->_graphicState->getMessage();
}

std::string const & LibGraphic::Sfml::getGameName() const
{
  return this->_graphicState->getGameName();
}

// void LibGraphic::Sfml::setNextState(eState s, eState d)
// {
//   this->_currentState = d;
//   this->_graphicState->setNextState(s, d);
// }

void LibGraphic::Sfml::setCurrentState(eStates s)
{
  this->_currentState = s;
}

void LibGraphic::Sfml::errorMessage(std::string const & message)
{
  this->_errorMessage = message;
  this->_errorMessage += " Press escape to erase the message.";
  errorToPrint = true;
}

void LibGraphic::Sfml::setMessage(std::string const &m)
{
  this->_graphicState->setMessage(m);
}

std::string const & LibGraphic::Sfml::getConversation() const
{
  return this->_graphicState->getConversation();
}

void LibGraphic::Sfml::addToConversation(std::string const & m)
{
  this->_graphicState->addToConversation(m);
}

std::map<int, InfoGame *> & LibGraphic::Sfml::getInfoGameMap(void) const
{
  return this->_graphicState->getInfoGameMap();
}

void LibGraphic::Sfml::setInfoGameMap(std::map<int, InfoGame *> &nmap)
{
  this->_graphicState->setInfoGameMap(nmap);
}

RecupMap &LibGraphic::Sfml::getRecupMap(void)
{
  return (this->_graphicState->getRecupMap());
}

std::list<std::string> &LibGraphic::Sfml::getLvlList(void)
{
  return this->_graphicState->getLvlList();
}

std::string const &LibGraphic::Sfml::getInGameName(void) const
{
  return this->_graphicState->getInGameName();
}

std::string const &LibGraphic::Sfml::getGameLvl(void) const
{
  return this->_graphicState->getGameLvl();
}

void LibGraphic::Sfml::setGameName(std::string const &s)
{
  this->_graphicState->setGameName(s);
}

void LibGraphic::Sfml::setGameLvl(std::string const &s)
{
  this->_graphicState->setGameLvl(s);
}

void LibGraphic::Sfml::setGameForPreview(InfoGame*g)
{
  this->_graphicState->setGameForPreview(g);
}

InfoGame * LibGraphic::Sfml::getGameForPreviewFromRoomlist(void)
{
  return this->_graphicState->getGameForPreviewFromRoomlist();
}

InfoGame * LibGraphic::Sfml::getGameForPreviewFromCreate(void)
{
  return this->_graphicState->getGameForPreviewFromCreate();
}

std::list<std::string> &LibGraphic::Sfml::getPlayerNameList(void)
{
  return this->_graphicState->getPlayerNameList();
}

LibGraphic::eMovement LibGraphic::Sfml::getLastMove() const
{
  return this->_graphicState->getLastMove();
}

std::map<int, LibGraphic::AMonsterMovement *> &LibGraphic::Sfml::getMonsterMap()
{
  return this->_graphicState->getMonsterMap();
}

std::map<int, LibGraphic::PlayerMovement *> const & LibGraphic::Sfml::getPlayerMap() const
{
  return this->_graphicState->getPlayerMap();
}

std::map<int, LibGraphic::PlayerMovement *> & LibGraphic::Sfml::getPlayerMap()
{
  return this->_graphicState->getPlayerMap();
}

sf::RenderWindow & LibGraphic::Sfml::getWindow()
{
  return this->_app;
}

sf::Sprite & LibGraphic::Sfml::getSprite(std::string const & spriteName)
{
  return this->_ressourcesSprite.find(spriteName)->second->_sprite;
}

eShipColor LibGraphic::Sfml::getMyId() const
{
  return this->_graphicState->getMyId();
}

void LibGraphic::Sfml::setMyId(eShipColor id)
{
  this->_graphicState->setMyId(id);
}

void LibGraphic::Sfml::setMyPosition(Coord c)
{
  this->_graphicState->setMyPosition(c);
}

LibGraphic::eBulletType LibGraphic::Sfml::getLastBullet(void) const
{
  return this->_graphicState->getLastBullet();
}

std::list<LibGraphic::BulletMovement *> &LibGraphic::Sfml::getBulletList(void)
{
  return this->_graphicState->getBulletList();
}

void LibGraphic::Sfml::resetInGameState(void)
{
  this->_graphicState->resetInGameState();
}

void LibGraphic::Sfml::resetRoomListState(void)
{
  this->_graphicState->resetRoomListState();
}

void LibGraphic::Sfml::setScore(unsigned int i)
{
    this->_graphicState->setScore(i);
}

void LibGraphic::Sfml::setLives(unsigned int i)
{
  this->_graphicState->setLives(i);
}

std::list<std::string> & LibGraphic::Sfml::getRankingList()
{
  return this->_graphicState->getRankingList();
}

std::list<LibGraphic::IAnnim *> &LibGraphic::Sfml::getExplosionList()
{
  return this->_graphicState->getExplosionList();
}

void LibGraphic::Sfml::setRunning(bool b)
{
  this->_graphicState->setRunning(b);
}

std::list<LibGraphic::Coord *> & LibGraphic::Sfml::getCoordBulletList()
{
  return this->_graphicState->getCoordBulletList();
}

std::list<LibGraphic::Coord *> & LibGraphic::Sfml::getEnnemyCoordBulletList()
{
  return this->_graphicState->getEnemyCoordBulletList();
}
