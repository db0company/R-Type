#ifndef STATECREATEGAME_H
# define STATECREATEGAME_H

#include <iostream>
#include <list>
#include <string>
#include "Sfml.hpp"
#include "Istate.hpp"
#include "AnnimTest.hpp"
#include "AnnimBigExplosion.hpp"
#include "AnnimCircleExplosion.hpp"
#include "AnnimLittleExplosion.hpp"

namespace LibGraphic
{

  class StateCreateGame : public AState
  {

  private:
    enum eSelectedButton
      {
 	BUTTON_CREATE_MAP,
	BUTTON_CREATE_TEAMSIZE_1,
	BUTTON_CREATE_TEAMSIZE_2,
	BUTTON_CREATE_TEAMSIZE_3,
	BUTTON_CREATE_TEAMSIZE_4,
	BUTTON_CREATE_SPECTATOR,
	BUTTON_CREATE_NAME,
	BUTTON_CREATE_BACK,
	BUTTON_CREATE_CREATE
      };

  public:
    StateCreateGame(std::map<std::string const, GraphicRessource *> const &,
		    std::map<std::string const, MyMusic *> const &,
		    std::map<std::string const, MySound *> const &,
		    std::map<std::string const, sf::Font *> const &,
		    sf::RenderWindow &);
    ~StateCreateGame();
    virtual bool init();
    virtual void draw();
    virtual Event gereEvent();
    virtual eStates getNextState();

  public:
    void setNextState(eState d);
    bool getSpectator() const;
    int getSlot() const;
    InfoGame *getGamePreview();
    std::string const & getGameName() const;
    std::list<std::string> &getLvlList(void);
    std::string const &getLevel() const;

  private:
    void drawText();
    void drawMap();
    void cursorMenuPos(const sf::Event&);
    void readText(const sf::Event &);
    void incMap();
    void decMap();

  private:
    std::list<std::string> _lvlList;
    eStates _nextState;
    eSelectedButton _currentButton;
    sf::Clock Clock;
    bool _isSpectatorChecked;
    unsigned char _teamSize;
    std::string _name;
    std::string _previewSelected;
    bool _isDefaultMap;

    //    AnnimTest * test;
    AnnimLittleExplosion * test;
  };

}

#endif
