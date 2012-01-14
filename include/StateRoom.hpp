#ifndef STATEROOM_H
# define STATEROOM_H

#include "Sfml.hpp"
#include "Istate.hpp"

namespace LibGraphic
{

  class StateRoom : public AState
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

  public:
    void setMessage(std::string const &s);
    std::string const & getMessage() const;
    std::string const & getConversation() const;
    void addToConversation(std::string const &);
    void setGameForPreview(InfoGame *);
    std::list<std::string> &getPlayerNameList(void);

  private:
    void setNextState(eState d);
    void drawText();
    void drawConv();
    void cursorMenuPos(const sf::Event&);
    void readText(const sf::Event &);
    void drawInputButton();
    void drawSelectedMap(void);
    void drawPlayerList(void);

  private:
    eStates _nextState;
    eSelectedButton _currentButton;
    sf::Clock Clock;
    std::string _chat;
    std::string _conversation;
    bool _isDefaultText;
    InfoGame *_game;
    std::list<std::string> _playerNameList;
 };

}

#endif
