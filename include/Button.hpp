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
