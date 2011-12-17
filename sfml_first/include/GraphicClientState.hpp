#ifndef GRAPHICCLIENTSTATE_H_
# define GRAPHICCLIENTSTATE_H_

#include <SFML/Graphics.hpp>
#include "MySound.hpp"
#include "MyMusic.hpp"
#include "GraphicUtils.hpp"
#include "IGraphic.hpp"

namespace LibGraphic
{

  class	GraphicClientState
  {

  private:
    // Constructors/Destructors
  public:
    GraphicClientState(std::map<std::string const, const GraphicRessource *> const &,
		       std::map<std::string const, MyMusic *> const &,
		       std::map<std::string const, MySound *> const &, sf::RenderWindow &);
    ~GraphicClientState(void);

    // Getters/Setters
  public:
    sf::Sprite const & getSprite(std::string const &) const;
    MyMusic * getMusic(std::string const &) const;

    // Attributes
  public:

    void draw(eStates);
    Event getEventFromState(eStates & scene);

  private:

    Event eventStart(eStates & scene);

  private:
    std::map<std::string const, const GraphicRessource *>
    const & _ressourcesSprite;
    std::map<std::string const, MyMusic *> const & _ressourcesPlayList;
    std::map<std::string const, MySound *> const & _ressourcesSounds;
    sf::RenderWindow & _app;
  };

}

#endif	// GRAPHICCLIENTSTATE.HPP_H_
