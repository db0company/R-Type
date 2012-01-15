#include "AMonsterMovement.hpp"

namespace LibGraphic
{

  AMonsterMovement::AMonsterMovement(sf::RenderWindow &app, sf::Sprite &sprite,
				     unsigned int w, unsigned int h,
				     unsigned int nbSprite,
				     unsigned int nbPlay) :
    _app(app), _sprite(sprite), _width(w), _height(h),
    _nbSprite(nbSprite), _nbPlay(nbPlay)
  {
    this->_coord.x = 0;
    this->_coord.y = 0;
    this->_clock.Reset();
    this->_clockVal = 0.2;
    this->_currentSprite = 0;
    this->_sprite.SetPosition(0, 0);
  }

  AMonsterMovement::~AMonsterMovement(void)
  {
  }

  void AMonsterMovement::play(void)
  {
    if (this->_clock.GetElapsedTime() < this->_clockVal)
      {
	this->setCoord(this->_coord.x, this->_coord.y);
	this->_sprite.SetSubRect(sf::IntRect(this->_width * this->_currentSprite, 0,
					     (this->_width * this->_currentSprite) +
					     this->_width, this->_height));
	this->_app.Draw(this->_sprite);
	return;
      }
    this->_sprite.SetSubRect(sf::IntRect(this->_width * this->_currentSprite, 0,
					 (this->_width * this->_currentSprite) +
					 this->_width, this->_height));
    this->setCoord(this->_coord.x, this->_coord.y);
    this->_app.Draw(this->_sprite);
    ++this->_currentSprite;
    if (this->_currentSprite >= this->_nbSprite)
      this->_currentSprite = 0;
    this->_clock.Reset();
  }

  void AMonsterMovement::pause(void)
  {
  }

  void AMonsterMovement::stop(void)
  {
  }

  Coord const &AMonsterMovement::getCoord(void) const
  {
    return this->_coord;
  }

  void AMonsterMovement::setCoord(unsigned int x, unsigned int y)
  {
    this->_coord.x = x;
    this->_coord.y = y;
    this->_sprite.SetPosition(this->_coord.x, this->_coord.y);
  }

  void AMonsterMovement::setScale(float x, float y)
  {
    this->_sprite.SetScale(x, y);
  }

  float AMonsterMovement::getTimet(void) const
  {
    return (this->_clockVal);
  }

  void AMonsterMovement::setTimer(float c)
  {
    this->_clockVal = c;
  }

} // end namespace LibGraphic
