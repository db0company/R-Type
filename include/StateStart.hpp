#ifndef STATESTART_H
# define STATESTART_H

#include "Sfml.hpp"
#include "Istate.hpp"

namespace LibGraphic
{

  class StateStart : public IState
  {
  private:
    enum eSelectedButton
      {
	PLAY,
	EXIT,
	CREDITS,
	OPTIONS,
	INTRO,
	RANKING
      };
  public:
    StateStart(std::map<std::string const, GraphicRessource *> const &,
		       std::map<std::string const, MyMusic *> const &,
		       std::map<std::string const, MySound *> const &,
		       std::map<std::string const, sf::Font *> const &,
		       sf::RenderWindow &);
    ~StateStart();
    virtual bool init();
    virtual void draw();
    virtual Event gereEvent();
  public:
    sf::Sprite & getSprite(std::string const &) const;
    MyMusic * getMusic(std::string const &) const;
    sf::Font * getFont(std::string const &) const;
   inline sf::String * getStdToSfString(std::string const &, sf::Font *);

  private:
    void drawText();
    void cursorMenuPos(const sf::Event &);

  private:
    std::map<std::string const, GraphicRessource *>
    const & _ressourcesSprite;
    std::map<std::string const, MyMusic *> const & _ressourcesPlayList;
    std::map<std::string const, MySound *> const & _ressourcesSounds;
    std::map<std::string const, sf::Font *> const & _ressourcesFont;
    sf::RenderWindow & _app;
  private:
    eSelectedButton _currentButton;
    sf::Clock Clock;
  };

}

#endif //STATESTART_H
