#ifndef STATEROOMLIST_H
# define STATEROOMLIST_H

#include <map>
#include "Sfml.hpp"
#include "Istate.hpp"
#include "InfoGame.hpp"

namespace LibGraphic
{

  class StateRoomList : public AState
  {

  private:
    enum eSelectedButton
      {
	BUTTON_ROOMLIST_GAME,
	BUTTON_ROOMLIST_BACK,
	BUTTON_ROOMLIST_REFRESH,
	BUTTON_ROOMLIST_SPECTATE,
	BUTTON_ROOMLIST_CREATE,
	BUTTON_ROOMLIST_JOIN
      };

  public:
    StateRoomList(std::map<std::string const, GraphicRessource *> const &,
		       std::map<std::string const, MyMusic *> const &,
		       std::map<std::string const, MySound *> const &,
		       std::map<std::string const, sf::Font *> const &,
		       sf::RenderWindow &);
    ~StateRoomList();
    virtual bool init();
    virtual void draw();
    virtual Event gereEvent();
    virtual eStates getNextState();

  public:
    void setNextState(eState d);
    std::map<int, InfoGame *> &getInfoGameMap(void);
    void setInfoGameMap(std::map<int, InfoGame *> &nmap);
    int getIdGame() const;
    InfoGame *getGamePreview();

  private:
    void drawText();
    void drawGames();
    void cursorMenuPos(const sf::Event&);
    void readText(const sf::Event &);
    void drawSelectedMap(void);

  private:
    std::map<int, InfoGame *> _infoGameMap;
    eStates _nextState;
    eSelectedButton _currentButton;
    sf::Clock Clock;
    unsigned int _deepList;
    unsigned int _nbGame;
    InfoGame * _selectedGame;
 };

}
#endif
