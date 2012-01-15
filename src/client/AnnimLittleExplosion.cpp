#include "AnnimLittleExplosion.hpp"
#include "SpriteInfo.hpp"

LibGraphic::AnnimLittleExplosion::AnnimLittleExplosion(sf::RenderWindow & app, sf::Sprite & sprite, int nbPlay) :
  _app(app), _sprite(sprite),_nbPlay(nbPlay)
{
  this->_coord.x = 200;
  this->_coord.y = 200;
  this->_clock.Reset();
  this->_clockVal = 0.1;
  this->_width = LITTLE_EXPLOSION_X;
  this->_height = LITTLE_EXPLOSION_Y;;
  this->_nbSprite = LITTLE_EXPLOSION_SIZE;
  this->_currentSprite = 0;
  this->_sprite.SetPosition(200, 200);



  this->_nbPlay = 1 * LITTLE_EXPLOSION_SIZE;
}

LibGraphic::AnnimLittleExplosion::~AnnimLittleExplosion()
{
}

int LibGraphic::AnnimLittleExplosion::getNbPlay() const
{
  return this->_nbPlay;
}

void LibGraphic::AnnimLittleExplosion::play()
{
  if (this->_nbPlay == -1)
    return;

  if (this->_clock.GetElapsedTime() < this->_clockVal)
    {
      this->_sprite.SetSubRect(sf::IntRect(LITTLE_EXPLOSION_X * this->_currentSprite, 0,
					   (LITTLE_EXPLOSION_X * this->_currentSprite) +
					   LITTLE_EXPLOSION_X, LITTLE_EXPLOSION_Y));
      this->_sprite.SetPosition(this->_coord.x, this->_coord.y);
      this->_app.Draw(this->_sprite);
      return;
    }
  this->_sprite.SetSubRect(sf::IntRect(LITTLE_EXPLOSION_X * this->_currentSprite, 0,
				       (LITTLE_EXPLOSION_X * this->_currentSprite) +
				       LITTLE_EXPLOSION_X, LITTLE_EXPLOSION_Y));
  if (this->_nbPlay)
    {
      if (this->_nbPlay == 1)
	{
	  this->_nbPlay = -1;
	}
      else
	--this->_nbPlay;
    }
  this->_sprite.SetPosition(this->_coord.x, this->_coord.y);
  this->_app.Draw(this->_sprite);
  ++this->_currentSprite;
  if (this->_currentSprite >= this->_nbSprite)
    this->_currentSprite = 0;
  this->_clock.Reset();
}

void LibGraphic::AnnimLittleExplosion::pause()
{
}

void LibGraphic::AnnimLittleExplosion::stop()
{
}

LibGraphic::Coord const & LibGraphic::AnnimLittleExplosion::getCoord() const
{
  return this->_coord;
}

void LibGraphic::AnnimLittleExplosion::setCoord(LibGraphic::Coord const & other)
{
  this->_coord.x = other.x;
  this->_coord.y = other.y;
}

float LibGraphic::AnnimLittleExplosion::getTimer() const
{
  return this->_clockVal;
}

void LibGraphic::AnnimLittleExplosion::setTimer(float other)
{
  this->_clockVal = other;
}

void LibGraphic::AnnimLittleExplosion::setCoord(int x, int y)
{
  this->_coord.x = x;
  this->_coord.y = y;
}

void LibGraphic::AnnimLittleExplosion::setScale(float x, float y)
{
  this->_sprite.SetScale(x, y);
}
