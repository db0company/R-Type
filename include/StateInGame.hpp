#ifndef INGAME_H
# define INGAME_H

#include "Sfml.hpp"
#include "Istate.hpp"
#include "RecupMap.hpp"
#include "PlayerMovement.hpp"
#include "SpriteInfo.hpp"
#include "BulletMovement.hpp"

namespace LibGraphic
{

  class StateInGame : public AState
  {

  public:
    StateInGame(std::map<std::string const, GraphicRessource *> const &,
		       std::map<std::string const, MyMusic *> const &,
		       std::map<std::string const, MySound *> const &,
		       std::map<std::string const, sf::Font *> const &,
		       sf::RenderWindow &);
    ~StateInGame();
    virtual bool init();
    virtual void draw();
    virtual Event gereEvent();
    virtual eStates getNextState();

    RecupMap &getRecupMap(void);

    void setGameName(std::string const &s);
    void setGameLvl(std::string const &s);
    std::string const &getInGameName(void) const;
    std::string const &getGameLvl(void) const;

    eMovement getLastMove() const;
    eBulletType getLastBullet() const;

    std::map<int, PlayerMovement *> const & getPlayerMap() const;
    std::map<int, PlayerMovement *> & getPlayerMap();
    std::list<BulletMovement *> &getBulletList();

    eShipColor getMyId() const;
    void setMyId(eShipColor id);
    void setMyPosition(Coord c);
    void resetInGameState();

  private:
    void setNextState(eState d);
    void drawBullet();
    void drawMonsters();
    void drawText();
    void drawConv();
    void drawStarField();
    void drawMap();
    void drawPlayers();
    void cursorMenuPos(const sf::Event&);
    void readText(const sf::Event &);
    int MapX(int x);
    int MapY(int y);
  private:

    int		gpos;
    RecupMap	_rMap;
    eStates _nextState;
    sf::Clock Clock;
    sf::Clock _mapClock;
    sf::Clock _frontClock;
    unsigned int _lives;
    unsigned int _score;
    std::string _gameName;
    std::string _gameLvl;
    bool _mapLoaded;
   // monsters
    // players

    eShipColor _myid;
    std::list<BulletMovement *>	_bulletList;
    std::map<int, PlayerMovement *> _playerMap;
    PlayerMovement * _player;
  };

}

#endif
