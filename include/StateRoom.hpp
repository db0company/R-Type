#ifndef STATEROOM_H
# define STATEROOM_H

#include "Sfml.hpp"
#include "Istate.hpp"

namespace LibGraphic
{

  class StateRoom : public IState
  {

  private:
    enum eSelectedButton
      {
	BUTTON_ROOM_CHAT,
	BUTTON_ROOM_QUIT,
	BUTTON_ROOM_START
      };

  public:
    StateRoom(std::map<std::string const, GraphicRessource *> const &,
		       std::map<std::string const, MyMusic *> const &,
		       std::map<std::string const, MySound *> const &,
		       std::map<std::string const, sf::Font *> const &,
		       sf::RenderWindow &);
    ~StateRoom();
    virtual bool init();
    virtual void draw();
    virtual Event gereEvent();
    virtual eStates getNextState();
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

  public:
    std::string const & getMessage() const;

  private:
    std::map<std::string const, GraphicRessource *>
    const & _ressourcesSprite;
    std::map<std::string const, MyMusic *> const & _ressourcesPlayList;
    std::map<std::string const, MySound *> const & _ressourcesSounds;
    std::map<std::string const, sf::Font *> const & _ressourcesFont;
    sf::RenderWindow & _app;

  private:
    eStates _nextState;
    eSelectedButton _currentButton;
    sf::Clock Clock;
    std::string _chat;
    bool _isDefaultText;
    eGraphicAction _action;
  };

}

#endif
