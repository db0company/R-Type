#ifndef INGAME_H
# define INGAME_H

#include "Sfml.hpp"
#include "Istate.hpp"
#include "RecupMap.hpp"
#include "PlayerMovement.hpp"
#include "SpriteInfo.hpp"

namespace LibGraphic
{

  class StateInGame : public IState
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

  public:
    sf::Sprite & getSprite(std::string const &) const;
    MyMusic * getMusic(std::string const &) const;
    sf::Font * getFont(std::string const &) const;
    inline sf::String * getStdToSfString(std::string const &, sf::Font *);
    RecupMap &getRecupMap(void);

    void setGameName(std::string const &s);
    void setGameLvl(std::string const &s);
    std::string const &getInGameName(void) const;
    std::string const &getGameLvl(void) const;

    eMovement getLastMove() const;

    std::map<int, PlayerMovement *> const & getPlayerMap() const;
    std::map<int, PlayerMovement *> & getPlayerMap();

    eShipColor getMyId() const;
    void setMyId(eShipColor id);
  private:
    void setNextState(eState d);
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
    std::map<std::string const, GraphicRessource *>
    const & _ressourcesSprite;
    std::map<std::string const, MyMusic *> const & _ressourcesPlayList;
    std::map<std::string const, MySound *> const & _ressourcesSounds;
    std::map<std::string const, sf::Font *> const & _ressourcesFont;
    sf::RenderWindow & _app;

  private:

    RecupMap	_rMap;
    eStates _nextState;
    sf::Clock Clock;
    sf::Clock _mapClock;
    sf::Clock _frontClock;
    unsigned int _lives;
    unsigned int _score;
    std::string _gameName;
    std::string _gameLvl;
    // monsters
    // players

    eShipColor _myid;
    std::map<int, PlayerMovement *> _playerMap;

    PlayerMovement * _player;
  };

}

#endif
