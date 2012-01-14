#include "AnnimCircleExplosion.hpp"
#include "SpriteInfo.hpp"

LibGraphic::AnnimCircleExplosion::AnnimCircleExplosion(sf::RenderWindow & app, sf::Sprite & sprite, int nbPlay) :
  _app(app), _sprite(sprite),_nbPlay(nbPlay)
{
  this->_coord.x = 200;
  this->_coord.y = 200;
  this->_clock.Reset();
  this->_clockVal = 0.1;
  this->_width = CIRCLE_EXPLOSION_X;
  this->_height = CIRCLE_EXPLOSION_Y;;
  this->_nbSprite = CIRCLE_EXPLOSION_SIZE;
  this->_currentSprite = 0;
  this->_sprite.SetPosition(200, 200);


  //  this->_nbPlay = 0;

}

LibGraphic::AnnimCircleExplosion::~AnnimCircleExplosion()
{
}

void LibGraphic::AnnimCircleExplosion::play()
{
  if (this->_nbPlay == -1)
    return;

  if (this->_nbPlay)
    {
      if (this->_nbPlay == 1)
	{
	  this->_nbPlay = -1;
	}
      else
	--this->_nbPlay;
    }
  if (this->_clock.GetElapsedTime() < this->_clockVal)
    {
      this->_sprite.SetSubRect(sf::IntRect(CIRCLE_EXPLOSION_X * this->_currentSprite, 0,
					   (CIRCLE_EXPLOSION_X * this->_currentSprite) +
					   CIRCLE_EXPLOSION_X, CIRCLE_EXPLOSION_Y));
      this->_app.Draw(this->_sprite);
      return;
    }
  this->_sprite.SetSubRect(sf::IntRect(CIRCLE_EXPLOSION_X * this->_currentSprite, 0,
				       (CIRCLE_EXPLOSION_X * this->_currentSprite) +
				       CIRCLE_EXPLOSION_X, CIRCLE_EXPLOSION_Y));
  this->_app.Draw(this->_sprite);
  ++this->_currentSprite;
  if (this->_currentSprite >= this->_nbSprite)
    this->_currentSprite = 0;
  this->_clock.Reset();
}

void LibGraphic::AnnimCircleExplosion::pause()
{
}

void LibGraphic::AnnimCircleExplosion::stop()
{
}

LibGraphic::Coord const & LibGraphic::AnnimCircleExplosion::getCoord() const
{
  return this->_coord;
}

void LibGraphic::AnnimCircleExplosion::setCoord(LibGraphic::Coord const & other)
{
  this->_coord.x = other.x;
  this->_coord.y = other.y;
}

float LibGraphic::AnnimCircleExplosion::getTimer() const
{
  return this->_clockVal;
}

void LibGraphic::AnnimCircleExplosion::setTimer(float other)
{
  this->_clockVal = other;
}
