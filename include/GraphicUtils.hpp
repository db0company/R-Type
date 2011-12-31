#ifndef GRAPHICUTILS_H_
# define GRAPHICUTILS_H_

#include <SFML/Graphics.hpp>

namespace LibGraphic
{
  enum eStates
    {
      START,
      ROOMLIST,
      GAMEPARAMETER,
      ROOM,
      OPTIONS,
      CREDITS,
      RANKING,
      INTRO,
      INGAME,
      UNKNOWN_STATE
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

  struct SpriteCoord
  {
    std::string name;
    Coord coordInFile;
  };

  struct EventUtils
  {
    sf::Event Event;
    sf::Input Input;
  };

}

#endif //GRAPHICUTILS_H_
