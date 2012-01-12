#ifndef STATECREATEGAME_H
# define STATECREATEGAME_H

#include <iostream>
#include <list>
#include <string>
#include "Sfml.hpp"
#include "Istate.hpp"

namespace LibGraphic
{

  class StateCreateGame : public IState
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
    sf::Sprite & getSprite(std::string const &) const;
    MyMusic * getMusic(std::string const &) const;
    sf::Font * getFont(std::string const &) const;
    inline sf::String * getStdToSfString(std::string const &, sf::Font *);

  public:
    void setNextState(eState d);
    bool getSpectator() const;
    int getSlot() const;
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
    std::map<std::string const, GraphicRessource *>
    const & _ressourcesSprite;
    std::map<std::string const, MyMusic *> const & _ressourcesPlayList;
    std::map<std::string const, MySound *> const & _ressourcesSounds;
    std::map<std::string const, sf::Font *> const & _ressourcesFont;
    sf::RenderWindow & _app;

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
  };

}

#endif
