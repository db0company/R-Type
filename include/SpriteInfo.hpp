#ifndef SPRITEINFO_H_
# define SPRITEINFO_H_


//    explosions      //

#define BIB_EXPLOSION_X 64
#define BIG_EXPLOSION_Y 66
#define BIG_EXPLOSION_SIZE 5 // 0 a 4
	// BigExplosion.png

#define CIRCLE_EXPLOSION_X 32
#define CIRCLE_EXPLOSION_Y 31
#define CIRCLE_EXPLOSION_SIZE 6 // 0 a 5
	// CircleExplosion.png

#define LITTLE_EXPLOSION_X 34
#define LITTLE_EXPLOSION_Y 33
#define LITTLE_EXPLOSION_SIZE 6 // 0 a 5
	//LittleExplosion.png

//    PlayerShip      //

#define SPRITE_SHIP_X 33
#define SPRITE_SHIP_Y 16 // ou 17 ? maybe. to try
	// PlayerShip.png

enum eShipRotation
  {
    SHIP_DOWN= 0,
    SHIP_MIDDLE_DOWN = 1,
    SHIP_MIDDLE = 2,
    SHIP_MIDDLE_UP = 3,
    SHIP_UP = 4
  };

enum eShipColor
  {
    BLUESHIP = 0,
    VIOLETSHIP = 1,
    GREENSHIP = 2,
    REDSHIP = 3,
    DARKSHIP = 4
  };

#endif
