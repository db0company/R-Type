#ifndef SFML_H_
# define SFML_H_

#include "IGraphic.hpp"

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
    sf::RenderWindow App;
  };
}
#endif	// SFML_H_
