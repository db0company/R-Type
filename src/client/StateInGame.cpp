#include <sstream>
#include <iostream>
#include "StateInGame.hpp"
#include "TileInfo.hpp"
#include "Language.hpp"
#include "SpriteInfo.hpp"
#include "AMonsterMovement.hpp"
#include "RedEvil.hpp"
#include "IAnnim.hpp"

extern LibGraphic::Volume gVolume;
extern LibGraphic::Language language;
extern bool errorToPrint;
extern bool helpToShow;
LibGraphic::StateInGame::StateInGame(std::map<std::string const, GraphicRessource *> const & ressourcesSprite,
						   std::map<std::string const, MyMusic *> const & ressourcesPlayList,
						   std::map<std::string const, MySound *> const & ressourcesSounds,
						   std::map<std::string const, sf::Font *> const & ressourcesFont,
						   sf::RenderWindow & app):
  AState(ressourcesSprite, ressourcesPlayList, ressourcesSounds,
	 ressourcesFont, app), _lives(0), _score(0)
{
  this->_running = true;
  this->_gameName = "";
  this->_gameLvl = "Star";
  this->_nextState = UNKNOWN_STATE;
  this->_mapClock.Reset();
  this->Clock.Reset();
  this->_frontClock.Reset();
  this->_myid = BLUESHIP;
  this->_player = new LibGraphic::PlayerMovement(this->_app,
						 this->getSprite("PlayerShip"), this->getSound("LaserSound"));
  this->_bulletInst = new LibGraphic::BulletMovement(this->_app, this->getSprite("Missile"), LibGraphic::NORMAL_BULLET);
  this->_enemyBulletInst = new LibGraphic::BulletMovement(this->_app, this->getSprite("MissileEnemy"), LibGraphic::NORMAL_BULLET);
  this->_lives = 0;
  this->_mapLoaded = false;
  gpos = 0;
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
  sf::Sprite &test = this->getSprite("SpriteMap");
  int i;
  float time = this->_mapClock.GetElapsedTime();

  if (this->_mapLoaded == false)
    {
      this->_rMap.recupFromFile("ressources/map/"+ this->_gameLvl + ".map");
      this->_mapLoaded = true;
    }
  if (time < 0.01)
    {
      i = 0;
      while (i < this->_rMap.size())
      	{
	  if (this->_rMap[i].up != TileEmpty)
	    {
	      test.SetPosition(MapX(i) + gpos, 30);
	      test.SetSubRect(sf::IntRect(MapX(this->_rMap[i].up), MapY(0),
					  MapX(this->_rMap[i].up + 1), MapY(1)));
	      this->_app.Draw(test);
	    }
	  if (this->_rMap[i].down != TileEmpty)
	    {
	      test.SetPosition(MapX(i) + gpos, 1050 - MapY(1));
	      test.SetSubRect(sf::IntRect(MapX(this->_rMap[i].down), MapY(1),
					  MapX(this->_rMap[i].down + 1), MapY(2)));
	      this->_app.Draw(test);
	    }
      	  ++i;
      	}
    }
  else
    {
      i = 0;
      gpos -= 1;
      while (i < this->_rMap.size())
	{
	  if (this->_rMap[i].up != TileEmpty)
	    {
	      test.SetPosition(MapX(i) + gpos, 30);
	      test.SetSubRect(sf::IntRect(MapX(this->_rMap[i].up), MapY(0),
					  MapX(this->_rMap[i].up + 1), MapY(1)));
	      this->_app.Draw(test);
	    }
	  if (this->_rMap[i].down != TileEmpty)
	    {

	      test.SetPosition(MapX(i) + gpos, 1050 - MapY(1));
	      test.SetSubRect(sf::IntRect(MapX(this->_rMap[i].down), MapY(1),
					  MapX(this->_rMap[i].down + 1), MapY(2)));
	      this->_app.Draw(test);
	    }
	  ++i;
	}
      this->_mapClock.Reset();
    }
}

void LibGraphic::StateInGame::drawBullet()
{
  this->_bulletInst->draw();
  this->_enemyBulletInst->draw();
}

void LibGraphic::StateInGame::drawMenu()
{
  sf::String *sLife;
  sf::Sprite &s = this->getSprite("PlayerShip");
  sf::Sprite &backm = this->getSprite("MenuBack");
  sf::String *sScore;

  unsigned int i = 0;

  backm.SetPosition(0, 0);
  this->_app.Draw(backm);
  if (language == ENGLISH)
    sLife = this->getStdToSfString("Lives :", this->getFont("StartFontF"));
  else
    sLife = this->getStdToSfString("Vies :", this->getFont("StartFontF"));
  sLife->SetPosition(10, 0);
  sLife->Scale(0.6, 0.6);
  this->_app.Draw(*sLife);
  sScore = this->getStdToSfString("Score : " + this->stringOfInt(this->_score),
				  this->getFont("StartFontF"));
  sScore->SetPosition(1500, 0);
  sScore->Scale(0.6, 0.6);
  this->_app.Draw(*sScore);
  s.SetSubRect(sf::IntRect(2 * SPRITE_SHIP_X, 0 * SPRITE_SHIP_Y,
			   3 * SPRITE_SHIP_X, 1 * SPRITE_SHIP_Y));
  while (i < this->_lives)
    {
      s.SetScale(1, 1);
      s.SetPosition(i * (SPRITE_SHIP_X + 15) + 100, 2);
      this->_app.Draw(s);
      ++i;
    }
}

void LibGraphic::StateInGame::drawExplosion()
{
  std::list<LibGraphic::IAnnim *>::iterator it;

  for (it = this->_explosionList.begin(); it != this->_explosionList.end(); ++it)
    {
      if ((*it)->getNbPlay() >= 0)
	(*it)->play();
      else
	{
	  LibGraphic::IAnnim * tmp;
	  tmp = (*it);
	  delete tmp;
	  it = this->_explosionList.erase(it);
	}
    }
}

std::string LibGraphic::StateInGame::stringOfInt(int v)
{
  std::stringstream ss;
  std::string s;

  ss << v;
  ss >> s;
  return s;
}

void LibGraphic::StateInGame::draw()
{
  this->drawStarField();
  this->drawMap();
  if (this->_running)
    {
      this->drawText();
      this->drawBullet();
      this->drawMonsters();
      this->drawPlayers();
    }
  this->drawMenu();
  if (this->_running)
    this->drawExplosion();
  if (this->_lives == 0 && this->_playerMap.size() == 0)
    this->_running = false;
  if (!this->_running)
    {
      sf::String *str = this->getStdToSfString("GAME OVER",
					       this->getFont("StartFontF"));
      str->SetPosition(600, 500);
      str->SetScale(2, 2);
      this->_app.Draw(*str);
    }
  MyMusic * song = this->getMusic("StartMusic");
  if (song->GetMusicState() == sf::Music::Stopped ||
      song->GetMusicState() == sf::Music::Paused)
    song->PlayMusic();
}

void LibGraphic::StateInGame::drawMonsters()
{
  std::map<int, AMonsterMovement *>::iterator it;

  for (it = this->_monsterMap.begin(); it != this->_monsterMap.end(); ++it)
    {
      it->second->play();
    }
}

void LibGraphic::StateInGame::setRunning(bool t)
{
  this->_running = t;
}

void LibGraphic::StateInGame::drawPlayers()
{
  this->_player->setId(this->_myid);
  if (this->_lives)
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

  errorToPrint = false;
  while (this->_app.GetEvent(Event))
    {
      if (Event.Type == sf::Event::KeyPressed)
	{
	  switch (Event.Key.Code)
	    {
	    case sf::Key::Escape :
	      //return LibGraphic::__EVENT_QUIT;
	      {
		if (this->_running)
		  {
		    // this->_app.Close();
		    // exit(EXIT_SUCCESS);
		    // this->_nextState = ROOMLIST;
		    // return (EVENT_INGAME_QUIT);
		  }
		else
		  {
		    this->_nextState = ROOMLIST;
		    return (EVENT_INGAME_QUIT);
		  }
		break;
	      }
	    case sf::Key::H :
	      {
		if (helpToShow)
		  helpToShow = false;
		else
		  helpToShow = true;
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
		if (this->_running)
		  {
		    // this->_app.Close();
		    // exit(EXIT_SUCCESS);
		    // this->_nextState = ROOMLIST;
		    // return (EVENT_INGAME_QUIT);
		  }
		else
		  {
		    this->_nextState = ROOMLIST;
		    return (EVENT_INGAME_QUIT);
		  }
		break;
      	      }
	    case 3:
	      {
		if (helpToShow)
		  helpToShow = false;
		else
		  helpToShow = true;
		break;
	      }
      	    default : break;
      	    }
      	}
    }
  this->_player->move(Event);
  return EVENT_NONE;
}

void LibGraphic::StateInGame::readText(const sf::Event &)
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

// std::map<int, AMonsterMovement *> const &LibGraphic::StateInGame::getMonsterMap() const
// {
//   return this->_monsterMap;
// }

std::map<int, LibGraphic::AMonsterMovement *> &LibGraphic::StateInGame::getMonsterMap()
{
  return this->_monsterMap;
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

// std::list<LibGraphic::Coord *> &LibGraphic::StateInGame::getEnemyBulletList(void)
// {
//   return (this->_enemyBulletList);
// }

void LibGraphic::StateInGame::resetInGameState(void)
{
  this->_nextState = UNKNOWN_STATE;
  this->_mapClock.Reset();
  this->Clock.Reset();
  this->_frontClock.Reset();
  this->_myid = BLUESHIP;
  this->_player = new LibGraphic::PlayerMovement(this->_app,
						 this->getSprite("PlayerShip"),
						 this->getSound("LaserSound"));
  this->_lives = 3;
  this->_score = 0;
  gpos = 0;
  this->_mapLoaded = false;
  this->_gameName = "";
  // this->_gameLvl = "Star";
  this->_monsterMap.clear();
  this->_playerMap.clear();
  this->_bulletList.clear();
  this->_enemyBulletList.clear();
  this->_explosionList.clear();
  this->_running = true;
}

void LibGraphic::StateInGame::setScore(unsigned int i)
{
  this->_score = i;
}

void LibGraphic::StateInGame::setLives(unsigned int i)
{
  this->_lives = i;
}

std::list<LibGraphic::IAnnim *> &LibGraphic::StateInGame::getExplosionList()
{
  return (this->_explosionList);
}

std::list<LibGraphic::Coord *> & LibGraphic::StateInGame::getCoordBulletList()
{
  return this->_bulletInst->getCoordList();
}

std::list<LibGraphic::Coord *> & LibGraphic::StateInGame::getEnemyCoordBulletList()
{
  return this->_enemyBulletInst->getCoordList();
}
