#include <iostream>
#include "SpriteInfo.hpp"
#include "PlayerMovement.hpp"

LibGraphic::PlayerMovement::PlayerMovement(sf::RenderWindow & app,
					   sf::Sprite & sprite):
  _app(app), _sprite(sprite)
{
  this->_coord.x = 400;
  this->_coord.y = 400;
  this->_id = BLUESHIP;
  this->_clock.Reset();
  this->_rotate = SHIP_MIDDLE;
}

LibGraphic::PlayerMovement::~PlayerMovement() {}


void LibGraphic::PlayerMovement::move(const sf::Event & event)
{
  const sf::Input & Input = this->_app.GetInput();
  float JoystickX = Input.GetJoystickAxis(0, sf::Joy::AxisX);
  float JoystickY = Input.GetJoystickAxis(0, sf::Joy::AxisY);
  bool LeftKeyDown = Input.IsKeyDown(sf::Key::Left);
  bool UpKeyDown = Input.IsKeyDown(sf::Key::Up);
  bool RightKeyDown = Input.IsKeyDown(sf::Key::Right);
  bool DownKeyDown = Input.IsKeyDown(sf::Key::Down);

  if (UpKeyDown || (JoystickY < -50))
    UpPlayer(LeftKeyDown, RightKeyDown, JoystickX);
  else if (DownKeyDown || (JoystickY > 50))
    DownPlayer(LeftKeyDown, RightKeyDown, JoystickX);
  else if (LeftKeyDown || (JoystickX < -50))
    {
      if (this->_rotate == SHIP_UP)
	{
	  this->_rotate = SHIP_MIDDLE_UP;
	  this->_clock.Reset();
	}
      else if (this->_rotate == SHIP_DOWN)
	{
	  this->_rotate = SHIP_MIDDLE_DOWN;
	  this->_clock.Reset();
	}
      else if (this->_clock.GetElapsedTime() >= 0.3)
	this->_rotate = SHIP_MIDDLE;
      this->_coord.x -= SHIPSPEED;
    }
  else if (RightKeyDown || (JoystickX > 50))
    {
      if (this->_rotate == SHIP_UP)
	{
	  this->_rotate = SHIP_MIDDLE_UP;
	  this->_clock.Reset();
	}
      else if (this->_rotate == SHIP_DOWN)
	{
	  this->_rotate = SHIP_MIDDLE_DOWN;
	  this->_clock.Reset();
	}
      else if (this->_clock.GetElapsedTime() >= 0.3)
	this->_rotate = SHIP_MIDDLE;
      this->_coord.x += SHIPSPEED;
    }
  else
    {
      if (this->_rotate == SHIP_UP)
	{
	  this->_rotate = SHIP_MIDDLE_UP;
	  this->_clock.Reset();
	}
      else if (this->_rotate == SHIP_DOWN)
	{
	  this->_rotate = SHIP_MIDDLE_DOWN;
	  this->_clock.Reset();
	}
      else if (this->_clock.GetElapsedTime() >= 0.3)
	this->_rotate = SHIP_MIDDLE;
    }
}

void LibGraphic::PlayerMovement::UpPlayer(bool LeftKeyDown, bool RightKeyDown, float JoystickX)
{
  if (LeftKeyDown || JoystickX < -50)
    {
      this->_coord.y -= SHIPSPEED;
      this->_coord.x -= SHIPSPEED;
    }
  else if (RightKeyDown || JoystickX > 50)
    {
      this->_coord.y -= SHIPSPEED;
      this->_coord.x += SHIPSPEED;
    }
  else
    this->_coord.y -= SHIPSPEED;

  if (this->_rotate == SHIP_MIDDLE_UP && this->_clock.GetElapsedTime() >= 0.3)
    {
      this->_rotate = SHIP_UP;
      this->_clock.Reset();
    }
  else if (this->_rotate != SHIP_UP)
    this->_rotate = SHIP_MIDDLE_UP;
}

void LibGraphic::PlayerMovement::DownPlayer(bool LeftKeyDown, bool RightKeyDown, float JoystickX)
{
  if (LeftKeyDown || JoystickX < -50)
    {
      this->_coord.y += SHIPSPEED;
      this->_coord.x -= SHIPSPEED;
    }
  else if (RightKeyDown || JoystickX > 50)
    {
      this->_coord.y += SHIPSPEED;
      this->_coord.x += SHIPSPEED;
    }
  else
    this->_coord.y += SHIPSPEED;

  if (this->_rotate == SHIP_MIDDLE_DOWN && this->_clock.GetElapsedTime() >= 0.3)
    {
      this->_rotate = SHIP_DOWN;
      this->_clock.Reset();
    }
  else if (this->_rotate != SHIP_DOWN)
    this->_rotate = SHIP_MIDDLE_DOWN;
}

void LibGraphic::PlayerMovement::draw()
{
  this->_sprite.SetSubRect(sf::IntRect(this->_rotate * SPRITE_SHIP_X,
				       this->_id * SPRITE_SHIP_Y,
				       this->_rotate * SPRITE_SHIP_X + SPRITE_SHIP_X,
				       this->_id * SPRITE_SHIP_Y + SPRITE_SHIP_Y));
  this->_sprite.SetPosition(this->_coord.x, this->_coord.y);
  this->_sprite.SetScale(2, 2);
  this->_app.Draw(this->_sprite);
}

LibGraphic::Coord const & LibGraphic::PlayerMovement::getCoord() const
{
  return this->_coord;
}

void LibGraphic::PlayerMovement::setCoord(LibGraphic::Coord const & coord)
{
  this->_coord.x = coord.x;
  this->_coord.y = coord.y;
}

eShipColor LibGraphic::PlayerMovement::getId() const
{
  return this->_id;
}

void LibGraphic::PlayerMovement::setId(eShipColor id)
{
  this->_id = id;
}
