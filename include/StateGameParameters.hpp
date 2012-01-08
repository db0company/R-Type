#ifndef STATEGAMEPARAMETERS_H
# define STATEGAMEPARAMETERS_H

#include "Sfml.hpp"
#include "Istate.hpp"

namespace LibGraphic
{

  class StateGameParameters : public IState
  {
  private:
    enum eSelectedButton
      {
	BUTTON_GAME_NAME,
	BUTTON_NB_PLAYER_1,
	BUTTON_NB_PLAYER_2,
	BUTTON_NB_PLAYER_3,
	BUTTON_NB_PLAYER_4,
	OBSERVER,
	LEVEL
      };
  public:
    StateGameParameters(std::map<std::string const, GraphicRessource *> const &,
			std::map<std::string const, MyMusic *> const &,
			std::map<std::string const, MySound *> const &,
			std::map<std::string const, sf::Font *> const &,
			sf::RenderWindow &);
    ~StateGameParameters();
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
