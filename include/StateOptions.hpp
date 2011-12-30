#ifndef STATEOPTIONS_H
# define STATEOPTIONS_H

#include "Sfml.hpp"
#include "Istate.hpp"

namespace LibGraphic
{

  class StateOptions : public IState
  {

  private:
    enum eSelectedButton
      {
	BACK,
	VALIDATE
      };

    enum eSelectedArea
      {
	NAME,
	IP,
	PORT,
	VOLUME_MUSIC,
	VOLUME_EFFECT
      };

  public:
    StateOptions(std::map<std::string const, GraphicRessource *> const &,
		       std::map<std::string const, MyMusic *> const &,
		       std::map<std::string const, MySound *> const &,
		       std::map<std::string const, sf::Font *> const &,
		       sf::RenderWindow &);
    ~StateOptions();
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
    std::map<std::string const, GraphicRessource *>
    const & _ressourcesSprite;
    std::map<std::string const, MyMusic *> const & _ressourcesPlayList;
    std::map<std::string const, MySound *> const & _ressourcesSounds;
    std::map<std::string const, sf::Font *> const & _ressourcesFont;
    sf::RenderWindow & _app;

  private:
    eStates _nextState;
    std::string test;
  };

}

#endif // STATEOPTIONS_H
