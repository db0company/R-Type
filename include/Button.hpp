#ifndef BUTTON_H_
# define BUTTON_H_

#include "Sfml.hpp"

namespace LibGraphic
{

  enum eDesign
    {
      TYPE1,
      TYPE_UNKNOWN
    };

  enum eButton
    {
      BUTTON_PLAY,
      BUTTON_EXIT,
      BUTTON_CREDITS,
      BUTTON_OPTIONS,
      BUTTON_INTRO,
      BUTTON_COMMAND
    };


  struct eButtonInfo
  {
    std::string buttonText;
    float squaleW;
    float squaleH;
    float x;
    float y;
  };


  class Button
  {

  private:
    Button(void);
    Button(const Button &);
    Button& operator=(const Button &);

  public:
    ~Button(void);
    Button(int, int, eDesign,
	   GraphicRessource const &, std::string = "");

  public:
    bool createButton();
    int getX() const;
    int getY() const;
    eDesign getDesign() const;
    std::string const & getText() const;
    void setX(int);
    void setY(int);
    void setDesign(eDesign);
    void setText(std::string const &);

  private:
    Coord _coord;
    eDesign _design;
    GraphicRessource const & _associatedSprite;

    std::string _text;
  };

}

#endif	// BUTTON_H_
