#include "AnnimTest.hpp"

LibGraphic::AnnimTest::AnnimTest(sf::RenderWindow & app, sf::Sprite & sprite, unsigned int nbPlay) :
  _app(app), _sprite(sprite),_nbPlay(nbPlay)
{
  this->_coord.x = 200;
  this->_coord.y = 200;
  this->_clock.Reset();
  this->_clockVal = 0.2;
  this->_width = 33;
  this->_height = 35;
  this->_nbSprite = 8;
  this->_currentSprite = 0;
  this->_sprite.SetPosition(200, 200);
}

LibGraphic::AnnimTest::~AnnimTest()
{
}

void LibGraphic::AnnimTest::play()
{
  if (this->_clock.GetElapsedTime() < this->_clockVal)
    {
      this->_sprite.SetSubRect(sf::IntRect(33 * this->_currentSprite, 0,
					   (33 * this->_currentSprite) + 33, 35));
      this->_app.Draw(this->_sprite);
      return;
    }
  this->_sprite.SetSubRect(sf::IntRect(33 * this->_currentSprite, 0,
  				       (33 * this->_currentSprite) + 33, 35));
  //   this->_sprite.SetScale(2, 2);
  this->_app.Draw(this->_sprite);
  ++this->_currentSprite;
  if (this->_currentSprite >= this->_nbSprite)
    this->_currentSprite = 0;
  this->_clock.Reset();
}

void LibGraphic::AnnimTest::pause()
{
}

void LibGraphic::AnnimTest::stop()
{
}

LibGraphic::Coord const & LibGraphic::AnnimTest::getCoord() const
{
  return this->_coord;
}

void LibGraphic::AnnimTest::setCoord(LibGraphic::Coord const & other)
{
  this->_coord.x = other.x;
  this->_coord.y = other.y;
  this->_sprite.SetPosition(this->_coord.x, this->_coord.y);
}

void LibGraphic::AnnimTest::setCoord(int x, int y)
{
  this->_coord.x = x;
  this->_coord.y = y;
  this->_sprite.SetPosition(this->_coord.x, this->_coord.y);
}

float LibGraphic::AnnimTest::getTimer() const
{
  return this->_clockVal;
}

void LibGraphic::AnnimTest::setTimer(float other)
{
  this->_clockVal = other;
}

void LibGraphic::AnnimTest::setScale(float x, float y)
{
  this->_sprite.SetScale(x, y);
}
