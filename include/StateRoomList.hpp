#ifndef STATEROOMLIST_H
# define STATEROOMLIST_H

#include "Sfml.hpp"
#include "Istate.hpp"
#include "InfoGame.hpp"

namespace LibGraphic
{

  class StateRoomList : public IState
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
    virtual void setNextState(eStates e);
    virtual eGraphicAction getAction();
    virtual void setAction(eGraphicAction);

  public:
    sf::Sprite & getSprite(std::string const &) const;
    MyMusic * getMusic(std::string const &) const;
    sf::Font * getFont(std::string const &) const;
   inline sf::String * getStdToSfString(std::string const &, sf::Font *);

  private:
    void drawText();
    void cursorMenuPos(const sf::Event&);
    void readText(const sf::Event &);

  private:
    std::map<std::string const, GraphicRessource *>
    const & _ressourcesSprite;
    std::map<std::string const, MyMusic *> const & _ressourcesPlayList;
    std::map<std::string const, MySound *> const & _ressourcesSounds;
    std::map<std::string const, sf::Font *> const & _ressourcesFont;
    sf::RenderWindow & _app;
    std::list<InfoGame *> _infoGame; // todo getter / setter

  private:
    eStates _nextState;
    eSelectedButton _currentButton;
    sf::Clock Clock;
    unsigned int _deepList;
    unsigned int _nbGame;
    eGraphicAction _action;
 };

}
#endif
