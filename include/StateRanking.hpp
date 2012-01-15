#ifndef STATERANKING_H
# define STATERANKING_H

#include "Sfml.hpp"
#include "Istate.hpp"

namespace LibGraphic
{

  class StateRanking : public AState
  {

  private:
    enum eSelectedButton
      {
	BUTTON_RANKING_BACK
      };

  public:
    StateRanking(std::map<std::string const, GraphicRessource *> const &,
		       std::map<std::string const, MyMusic *> const &,
		       std::map<std::string const, MySound *> const &,
		       std::map<std::string const, sf::Font *> const &,
		       sf::RenderWindow &);
    ~StateRanking();
    virtual bool init();
    virtual void draw();
    virtual Event gereEvent();
    virtual eStates getNextState();

  public:
    void setNextState(eState d);
    std::list<std::string> & getRankingList();

  private:
    void drawText();
    void drawRank();
    std::string stringOfInt(int v);

  private:
    eStates _nextState;
    eSelectedButton _currentButton;
    sf::Clock Clock;

  private:
    std::list<std::string> _rank;

  };

}

#endif
