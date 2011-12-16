#ifndef GRAPHICCLIENTSTATE_H_
# define GRAPHICCLIENTSTATE_H_

#include "MySound.hpp"
#include "MyMusic.hpp"
#include "GraphicUtils.hpp"

namespace LibGraphic
{

  class	GraphicClientState
  {

  private:
    // Constructors/Destructors
  public:
    GraphicClientState(std::string const &,
		       std::map<std::string const, const GraphicRessource *> const &,
		       std::map<std::string const, MyMusic *> const &,
		       std::map<std::string const, MySound *> const &);
    ~GraphicClientState(void);

    // Getters/Setters
  public:
    std::string const & getName() const;
    sf::Sprite const & getSprite(std::string const &) const;
    MyMusic * getMusic(std::string const &) const;

    // Attributes
  public:

  private:

    std::string const & _name;
    std::map<std::string const, const GraphicRessource *>
    const & _ressourcesSprite;
    std::map<std::string const, MyMusic *> const & _ressourcesPlayList;
    std::map<std::string const, MySound *> const & _ressourcesSounds;

  };

}

#endif	// GRAPHICCLIENTSTATE.HPP_H_
