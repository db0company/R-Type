#ifndef STATEJOINCREATE_H
# define STATEJOINCREATE_H

#include "Sfml.hpp"
#include "Istate.hpp"

namespace LibGraphic
{

  class StateJoinCreate : public IState
  {

  private:
    enum eSelectedButton
      {
	BUTTON_JOINCREATE_JOIN,
	BUTTON_JOINCREATE_CREATE,
	BUTTON_JOINCREATE_BACK
      };

  public:
    StateJoinCreate(std::map<std::string const, GraphicRessource *> const &,
		       std::map<std::string const, MyMusic *> const &,
		       std::map<std::string const, MySound *> const &,
		       std::map<std::string const, sf::Font *> const &,
		       sf::RenderWindow &);
    ~StateJoinCreate();
    virtual bool init();
    virtual void draw();
    virtual Event gereEvent();
    virtual eStates getNextState();
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

  private:
    eStates _nextState;
    eSelectedButton _currentButton;
    sf::Clock Clock;

  };

}

#endif
