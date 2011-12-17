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
  public:
    GraphicClientState(std::map<std::string const, const GraphicRessource *> const &,
		       std::map<std::string const, MyMusic *> const &,
		       std::map<std::string const, MySound *> const &,
		       std::map<std::string const, sf::Font *> const &,
		       sf::RenderWindow &);
    ~GraphicClientState(void);

  public:
    sf::Sprite const & getSprite(std::string const &) const;
    MyMusic * getMusic(std::string const &) const;
    sf::Font * getFont(std::string const &) const;

  public:
    void draw(eStates);
    Event getEventFromState(eStates &);

  private:
    Event eventStart(eStates & scene);
   inline sf::String const * getStdToSfString(std::string const &, sf::Font *);

    void displayStart();
    void displayRoomlist();
    void displayGameparameter();
    void displayRoom();
    void displayOptions();
    void displayCredits();
    void displayRanking();
    void displayIntro();
    void displayIngame();

  private:
    std::map<std::string const, const GraphicRessource *>
    const & _ressourcesSprite;
    std::map<std::string const, MyMusic *> const & _ressourcesPlayList;
    std::map<std::string const, MySound *> const & _ressourcesSounds;
    std::map<std::string const, sf::Font *> const & _ressourcesFont;
    sf::RenderWindow & _app;
  };

}

#endif	// GRAPHICCLIENTSTATE.HPP_H_
