#ifndef SFML_H_
# define SFML_H_

#include <SFML/Graphics.hpp>
#include "MyMusic.hpp"
#include "MySound.hpp"
#include "IGraphic.hpp"
#include "GraphicUtils.hpp"
#include "GraphicClientState.hpp"

#define WINDOWNAME "R-Type"

namespace LibGraphic
{

  class	Sfml : public IGraphic
  {
  public:
    Sfml(void);
    ~Sfml(void);
    Sfml(const Sfml&);
    Sfml&	operator=(const Sfml&);
  public:
    virtual bool init();
    virtual Event getEvent();
    virtual void quit();
    virtual void clean();
    virtual void draw();

  private:
    bool loadFont();
    bool loadSound();
    bool loadMusic();
    bool loadSprite();
    bool loadRessources();
    void createStates();
    inline bool isFullscreen(std::string s);
    inline std::string getNextInfoRessource(std::string &);

  private:
    int _width;
    int _height;
    sf::RenderWindow _app;
    eStates _currentState;
    GraphicClientState * _graphicState;

    std::map<std::string const, GraphicRessource const *> _ressourcesSprite;
    std::map<std::string const, MyMusic *> _ressourcesPlayList;
    std::map<std::string const, MySound *> _ressourcesSounds;
    std::map<std::string const, sf::Font *> _ressourcesFont;
  };

}

#endif	// SFML_H_
