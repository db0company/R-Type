#ifndef GRAPHICCLIENTSTATE_H_
# define GRAPHICCLIENTSTATE_H_

#include <SFML/Graphics.hpp>
#include "MySound.hpp"
#include "MyMusic.hpp"
#include "GraphicUtils.hpp"
#include "IGraphic.hpp"
#include "Istate.hpp"

namespace LibGraphic
{

  class	GraphicClientState
  {
  public:
    GraphicClientState(std::map<std::string const, GraphicRessource *> const &,
		       std::map<std::string const, MyMusic *> const &,
		       std::map<std::string const, MySound *> const &,
		       std::map<std::string const, sf::Font *> const &,
		       sf::RenderWindow &);
    ~GraphicClientState(void);

  public:
    void draw(eStates);
    Event getEventFromState(eStates);

  private:
    Event eventStart(eStates & scene);
    void loadStates();

  private:
    std::map<std::string const, GraphicRessource *>
    const & _ressourcesSprite;
    std::map<std::string const, MyMusic *> const & _ressourcesPlayList;
    std::map<std::string const, MySound *> const & _ressourcesSounds;
    std::map<std::string const, sf::Font *> const & _ressourcesFont;
    std::map<eStates, IState *> _stateInfos;
  private:
    sf::RenderWindow & _app;
    sf::Event _catchedEvent;
  };

}

#endif	// GRAPHICCLIENTSTATE.HPP_H_
