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
    GraphicClientState(std::string const &);
    ~GraphicClientState(void);

    // Getters/Setters
  public:
    std::string const & getName() const;

    // Attributes
  private:
    std::string const & _name;
    std::map<std::string const, MySound *> _ressourcesSounds;
    std::map<std::string const, MyMusic *> _ressourcesPlayList;
    std::map<std::string const, const GraphicRessource *>
    _ressourcesSprite;

  };

}

#endif	// GRAPHICCLIENTSTATE.HPP_H_
