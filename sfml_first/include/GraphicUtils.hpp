#ifndef GRAPHICUTILS_H_
# define GRAPHICUTILS_H_

#include <SFML/Graphics.hpp>

namespace LibGraphic
{

  enum eStates
    {
      START,
      INGAME
    };

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

}

#endif //GRAPHICUTILS_H_
