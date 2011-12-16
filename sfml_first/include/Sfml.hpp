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
    bool loadSound();
    bool loadMusic();
    bool loadSprite();
    bool loadRessources();
    bool createStates();
    inline bool isFullscreen(std::string s);
    inline std::string getNextInfoRessource(std::string &);
    GraphicClientState * createStateStart();
    GraphicClientState * createStateIngame();

  private:
    int _width;
    int _height;
    sf::RenderWindow _app;
    GraphicClientState * _currentState;

    std::map<std::string const, GraphicRessource const *> _ressourcesSprite;
    std::map<std::string const, MyMusic *> _ressourcesPlayList;
    std::map<std::string const, MySound *> _ressourcesSounds;
    std::map<eStates, GraphicClientState *> _statesMap;
  };

}

#endif	// SFML_H_
