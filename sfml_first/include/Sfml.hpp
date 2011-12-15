#ifndef SFML_H_
# define SFML_H_

#include <SFML/Graphics.hpp>
#include "MyMusic.hpp"
#include "MySound.hpp"
#include "IGraphic.hpp"

#define WINDOWNAME "R-Type"

namespace LibGraphic
{

  struct GraphicRessource
  {
    sf::Image _image;
    sf::Sprite _sprite;
    bool _isFullScreen;
  };

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
    inline bool isFullscreen(std::string s);

  private:
    int _width;
    int _height;
    sf::RenderWindow _app;
    std::map<std::string const, GraphicRessource const *> _ressourcesSprite;
    std::map<std::string const, LibGraphic::MyMusic *> _ressourcesPlayList;
    std::map<std::string const, LibGraphic::MySound *> _ressourcesSounds;
  };

}

#endif	// SFML_H_
