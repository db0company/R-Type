#include <iostream>
#include "StateInGame.hpp"
#include "TileInfo.hpp"
#include "Language.hpp"
#include "SpriteInfo.hpp"

extern LibGraphic::Volume gVolume;
extern LibGraphic::Language language;
extern bool errorToPrint;

LibGraphic::StateInGame::StateInGame(std::map<std::string const, GraphicRessource *> const & ressourcesSprite,
						   std::map<std::string const, MyMusic *> const & ressourcesPlayList,
						   std::map<std::string const, MySound *> const & ressourcesSounds,
						   std::map<std::string const, sf::Font *> const & ressourcesFont,
						   sf::RenderWindow & app):
  AState(ressourcesSprite, ressourcesPlayList, ressourcesSounds,
	 ressourcesFont, app), _lives(0), _score(0)
{
  this->_nextState = UNKNOWN_STATE;
  this->_mapClock.Reset();
  this->Clock.Reset();
  this->_frontClock.Reset();
  this->_myid = BLUESHIP;
  this->_player = new LibGraphic::PlayerMovement(this->_app,
					      this->getSprite("PlayerShip"));
}

LibGraphic::StateInGame::~StateInGame()
{
}

bool LibGraphic::StateInGame::init()
{
  return true;
}

int LibGraphic::StateInGame::MapX(int x)
{
  return (x * TILE_SIZE_X);
}

int LibGraphic::StateInGame::MapY(int y)
{
  return (y * TILE_SIZE_Y);
}

void LibGraphic::StateInGame::drawStarField()
{
  static int scale = 0;
  static int scalefront = 0;
  sf::Sprite &b = this->getSprite("Starfield" + this->_gameLvl);
  sf::Sprite &b2 = this->getSprite("Starfield" + this->_gameLvl);
  sf::Sprite &front = this->getSprite("SecondField" + this->_gameLvl);
  sf::Sprite &front2 = this->getSprite("SecondField" + this->_gameLvl);
  float time = this->Clock.GetElapsedTime();
  float timefront = this->_frontClock.GetElapsedTime();

  if (time < 0.05)
    {
      b.SetPosition(0 - scale, 0);
      this->_app.Draw(b);
      b2.SetPosition(1680 - scale, 0);
      this->_app.Draw(b2);
    }
  else
    {
      scale += 1;
      if (scale >= 1680)
	scale = 0;
      b.SetPosition(0 - scale, 0);
      this->_app.Draw(b);
      b2.SetPosition(1680 - scale, 0);
      this->_app.Draw(b2);
      this->Clock.Reset();
    }
  if (timefront < 0.03)
    {
      front.SetPosition(0 - scalefront, 0);
      this->_app.Draw(front);
      front2.SetPosition(1680 - scalefront, 0);
      this->_app.Draw(front2);
    }
  else
    {
      scalefront += 1;
      if (scalefront >= 1680)
	scalefront = 0;
      front.SetPosition(0 - scalefront, 0);
      this->_app.Draw(front);
      front2.SetPosition(1680 - scalefront, 0);
      this->_app.Draw(front2);
      this->_frontClock.Reset();
    }
}

void LibGraphic::StateInGame::drawMap()
{
  static int gpos = 0;
  sf::Sprite &test = this->getSprite("SpriteMap");
  int i;
  float time = this->_mapClock.GetElapsedTime();

  if (time < 0.01)
    {
      i = 0;
      this->_rMap.recupFromFile("ressources/map/"+ this->_gameLvl + ".map");
      while (i < this->_rMap.size())
      	{
      	  test.SetPosition(MapX(i) + gpos, 0);
      	  test.SetSubRect(sf::IntRect(MapX(this->_rMap[i].up), MapY(0),
      				      MapX(this->_rMap[i].up + 1), MapY(1)));
      	  this->_app.Draw(test);
      	  test.SetPosition(MapX(i) + gpos, 1050 - MapY(1));
      	  test.SetSubRect(sf::IntRect(MapX(this->_rMap[i].down), MapY(1),
      				      MapX(this->_rMap[i].down + 1), MapY(2)));
      	  this->_app.Draw(test);
      	  ++i;
      	}
    }
  else
    {
      i = 0;
      gpos -= 1;
      this->_rMap.recupFromFile("ressources/map/"+ this->_gameLvl + ".map");
      while (i < this->_rMap.size())
	{
	  test.SetPosition(MapX(i) + gpos, 0);
	  test.SetSubRect(sf::IntRect(MapX(this->_rMap[i].up), MapY(0),
				      MapX(this->_rMap[i].up + 1), MapY(1)));
	  this->_app.Draw(test);
	  test.SetPosition(MapX(i) + gpos, 1050 - MapY(1));
	  test.SetSubRect(sf::IntRect(MapX(this->_rMap[i].down), MapY(1),
				      MapX(this->_rMap[i].down + 1), MapY(2)));
	  this->_app.Draw(test);
	  ++i;
	}
      this->_mapClock.Reset();
    }
}

void LibGraphic::StateInGame::drawBullet()
{
  std::list<BulletMovement *>::iterator it;

  for (it = this->_bulletList.begin(); it != this->_bulletList.end(); ++it)
    {
      (*it)->draw();
    }
  std::cout << this->_bulletList.size() << std::endl;
}

void LibGraphic::StateInGame::draw()
{
  this->drawStarField();
  this->drawMap();
  this->drawText();
  this->drawBullet();
  this->drawMonsters();
  this->drawPlayers();
}

void LibGraphic::StateInGame::drawMonsters()
{
}

void LibGraphic::StateInGame::drawPlayers()
{
  this->_player->setId(this->_myid);
  this->_player->draw();
  std::map<int, PlayerMovement *>::iterator it;

  for (it = this->_playerMap.begin(); it != this->_playerMap.end(); ++it)
    {
      if (it->second->getId() != this->_myid)
	{
	  it->second->draw();
	}
    }
}

void LibGraphic::StateInGame::drawText()
{
}

LibGraphic::Event LibGraphic::StateInGame::gereEvent()
{
  sf::Event Event;

  while (this->_app.GetEvent(Event))
    {
      if (Event.Type == sf::Event::KeyPressed)
	{
	  switch (Event.Key.Code)
	    {
	    case sf::Key::Escape :
	      //return LibGraphic::__EVENT_QUIT;
	      {
		// if (errorToPrint)
		//   errorToPrint = false;
		// else
		//   {
		// this->_app.Close();
		// exit(EXIT_SUCCESS);
		this->_nextState = ROOMLIST;
		return (EVENT_CHANGE_STATE);
		// }
		break;
	      }
	    default : break;
	    }
	}
      if (Event.Type == sf::Event::JoyButtonReleased)
      	{
      	  switch (Event.JoyButton.Button)
      	    {
	    case 0:
      	      {
		break;
      	      }
      	    case 1:
      	      {
		break;
      	      }
      	    default : break;
      	    }
      	}
    }
  this->_player->move(Event);
  return EVENT_NONE;
}

void LibGraphic::StateInGame::readText(const sf::Event & Event)
{
}

LibGraphic::eStates LibGraphic::StateInGame::getNextState()
{
  return this->_nextState;
}

RecupMap &LibGraphic::StateInGame::getRecupMap(void)
{
  return (this->_rMap);
}

std::string const &LibGraphic::StateInGame::getInGameName(void) const
{
  return (this->_gameName);
}

std::string const &LibGraphic::StateInGame::getGameLvl(void) const
{
  return (this->_gameLvl);
}

void LibGraphic::StateInGame::setGameName(std::string const &s)
{
  this->_gameName = s;
}

void LibGraphic::StateInGame::setGameLvl(std::string const &s)
{
  this->_gameLvl = s;
}

LibGraphic::eMovement LibGraphic::StateInGame::getLastMove() const
{
  return this->_player->getLastMove();
}

std::map<int, LibGraphic::PlayerMovement *> const & LibGraphic::StateInGame::getPlayerMap() const
{
  return this->_playerMap;
}

std::map<int, LibGraphic::PlayerMovement *> & LibGraphic::StateInGame::getPlayerMap()
{
  return this->_playerMap;
}

eShipColor LibGraphic::StateInGame::getMyId() const
{
  return this->_myid;
}

void LibGraphic::StateInGame::setMyId(eShipColor id)
{
  this->_myid = id;
}

void LibGraphic::StateInGame::setMyPosition(Coord c)
{
  this->_player->setCoord(c);
}

LibGraphic::eBulletType LibGraphic::StateInGame::getLastBullet() const
{
  return this->_player->getLastBullet();
}

std::list<LibGraphic::BulletMovement *> &LibGraphic::StateInGame::getBulletList(void)
{
  return (this->_bulletList);
}
