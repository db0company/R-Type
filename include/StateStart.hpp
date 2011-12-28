#ifndef STATESTART_H
# define STATESTART_H

#include "Sfml.hpp"
#include "Istate.hpp"

namespace LibGraphic
{

  class StateStart : public IState
  {
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
    std::map<std::string const, GraphicRessource *>
    const & _ressourcesSprite;
    std::map<std::string const, MyMusic *> const & _ressourcesPlayList;
    std::map<std::string const, MySound *> const & _ressourcesSounds;
    std::map<std::string const, sf::Font *> const & _ressourcesFont;
  private:
    sf::RenderWindow & _app;


  };

}

#endif //STATESTART_H
