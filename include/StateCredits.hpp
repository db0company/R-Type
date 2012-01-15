#ifndef STATECREDITS_H
# define STATECREDITS_H

#include "Sfml.hpp"
#include "Istate.hpp"

namespace LibGraphic
{

  class StateCredits : public AState
  {

  private:
    enum eSelectedButton
      {
	BUTTON_CREDITS_BACK
      };

    struct credit
    {
      std::string s;
      unsigned int pos;
      credit(std::string const & sP, unsigned int posP):
	s(sP), pos(posP) {}
    };

  public:
    StateCredits(std::map<std::string const, GraphicRessource *> const &,
		       std::map<std::string const, MyMusic *> const &,
		       std::map<std::string const, MySound *> const &,
		       std::map<std::string const, sf::Font *> const &,
		       sf::RenderWindow &);
    ~StateCredits();
    virtual bool init();
    virtual void draw();
    virtual Event gereEvent();
    virtual eStates getNextState();

  public:
    void setNextState(eState d);

  private:
    void drawText();
    void drawCredits();
    void loadCredits();

  private:
    eStates _nextState;
    eSelectedButton _currentButton;
    sf::Clock Clock;

  private:
    std::list<credit *> _list;
    bool _end;
  };

}

#endif
