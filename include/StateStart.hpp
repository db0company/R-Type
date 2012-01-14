#ifndef STATESTART_H
# define STATESTART_H

#include "Sfml.hpp"
#include "Istate.hpp"

namespace LibGraphic
{

  class StateStart : public AState
  {
  private:
    enum eSelectedButton
      {
	BUTTON_PLAY,
	BUTTON_EXIT,
	BUTTON_CREDITS,
	BUTTON_OPTIONS,
	BUTTON_INTRO,
	BUTTON_RANKING
      };
  public:
    StateStart(std::map<std::string const, GraphicRessource *> const &,
		       std::map<std::string const, MyMusic *> const &,
		       std::map<std::string const, MySound *> const &,
		       std::map<std::string const, sf::Font *> const &,
		       sf::RenderWindow &);
    ~StateStart();
    virtual bool init();
    virtual void draw();
    virtual Event gereEvent();
    virtual eStates getNextState();

  public:
    void setNextState(eState d);

  private:
    void drawText();
    void cursorMenuPos(const sf::Event &);

  private:
    eSelectedButton _currentButton;
    sf::Clock Clock;
    eStates _nextState;
  };

}

#endif //STATESTART_H
