#ifndef SFML_H_
# define SFML_H_

#include <SFML/Graphics.hpp>
#include "MyMusic.hpp"
#include "MySound.hpp"
#include "IGraphic.hpp"

#define WINDOWNAME "R-Type"

namespace LibGraphic
{
  struct Size
  {
    unsigned int width;
    unsigned int height;
  };

  struct Coord
  {
    int x;
    int y;
  };

  struct GraphicRessource
  {
    sf::Image _image;
    sf::Sprite _sprite;
    bool _isFullScreen;
    Size _dimension;
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
    inline std::string getNextInfoRessource(std::string &);

  private:
    int _width;
    int _height;
    sf::RenderWindow _app;
    std::map<std::string const, GraphicRessource const *> _ressourcesSprite;
    std::map<std::string const, MyMusic *> _ressourcesPlayList;
    std::map<std::string const, MySound *> _ressourcesSounds;
  };

}

#endif	// SFML_H_
