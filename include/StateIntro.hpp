#ifndef STATEINTRO_H
# define STATEINTRO_H

#include "Sfml.hpp"
#include "Istate.hpp"
#include "RecupMap.hpp"
#include "PlayerMovement.hpp"
#include "SpriteInfo.hpp"
#include "BulletMovement.hpp"
#include "IAnnim.hpp"

namespace LibGraphic
{

  class AMonsterMovement;

  class StateIntro : public AState
  {
  public:
    StateIntro(std::map<std::string const, GraphicRessource *> const &,
		       std::map<std::string const, MyMusic *> const &,
		       std::map<std::string const, MySound *> const &,
		       std::map<std::string const, sf::Font *> const &,
		       sf::RenderWindow &);
    ~StateIntro();
    virtual bool init();
    virtual void draw();
    virtual Event gereEvent();
    virtual eStates getNextState();
  public:
    void drawStarField();
    void drawMap();

  private:
    eStates _nextState;
    sf::Clock Clock;
    sf::Clock _frontClock;
    std::string _gameLvl;

  };

}

#endif
