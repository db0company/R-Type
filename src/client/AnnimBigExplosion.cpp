#include "AnnimBigExplosion.hpp"
#include "SpriteInfo.hpp"

LibGraphic::AnnimBigExplosion::AnnimBigExplosion(sf::RenderWindow & app, sf::Sprite & sprite, int nbPlay) :
  _app(app), _sprite(sprite), _nbPlay(nbPlay)
{
  this->_coord.x = 200;
  this->_coord.y = 200;
  this->_clock.Reset();
  this->_clockVal = 0.1;
  this->_width = BIG_EXPLOSION_X;
  this->_height = BIG_EXPLOSION_Y;;
  this->_nbSprite = BIG_EXPLOSION_SIZE;
  this->_currentSprite = 0;
  this->_sprite.SetPosition(200, 200);
  this->_nbPlay = 1 * BIG_EXPLOSION_SIZE;
}

LibGraphic::AnnimBigExplosion::~AnnimBigExplosion()
{
}

void LibGraphic::AnnimBigExplosion::play()
{
  if (this->_nbPlay == -1)
    return;

  if (this->_clock.GetElapsedTime() < this->_clockVal)
    {
      this->_sprite.SetSubRect(sf::IntRect(BIG_EXPLOSION_X * this->_currentSprite, 0,
					   (BIG_EXPLOSION_X * this->_currentSprite) +
					   BIG_EXPLOSION_X, BIG_EXPLOSION_Y));
      this->_sprite.SetPosition(this->_coord.x, this->_coord.y);
      this->_app.Draw(this->_sprite);
      return;
    }
  this->_sprite.SetSubRect(sf::IntRect(BIG_EXPLOSION_X * this->_currentSprite, 0,
				       (BIG_EXPLOSION_X * this->_currentSprite) +
				       BIG_EXPLOSION_X, BIG_EXPLOSION_Y));
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
  // MySound * song = this->_sound;
  // song->PlaySound();
  this->_clock.Reset();
}

void LibGraphic::AnnimBigExplosion::pause()
{
}

void LibGraphic::AnnimBigExplosion::stop()
{
}

LibGraphic::Coord const & LibGraphic::AnnimBigExplosion::getCoord() const
{
  return this->_coord;
}

void LibGraphic::AnnimBigExplosion::setCoord(LibGraphic::Coord const & other)
{
  this->_coord.x = other.x;
  this->_coord.y = other.y;
}

float LibGraphic::AnnimBigExplosion::getTimer() const
{
  return this->_clockVal;
}

void LibGraphic::AnnimBigExplosion::setTimer(float other)
{
  this->_clockVal = other;
}

void LibGraphic::AnnimBigExplosion::setCoord(int x, int y)
{
  this->_coord.x = x;
  this->_coord.y = y;
}

void LibGraphic::AnnimBigExplosion::setScale(float x, float y)
{
  this->_sprite.SetScale(x, y);
}
