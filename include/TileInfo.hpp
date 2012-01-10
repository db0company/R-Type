#ifndef __TILEINFO_HH
#define __TILEINFO_HH

#define TILE_SIZE_X 128
#define TILE_SIZE_Y 192

enum eTileName
  {
    TileSize1A = 0,
    TileSize1B = 1,
    TileSize1C = 2,
    TileSize2 = 3,
    TileSize3 = 4,
    TileSize4BaseLeft = 5,
    TileSize4Left = 6,
    TileSize4BaseRight = 7,
    TileSize4Right = 8,
    TileSize2Diago = 9,
    TileAlien1 = 10,
    TileAlien2 = 11,
    TileAlien3 = 12,
    TileEmpty
  };

enum eTilePos
  {
    CEILING = 0,
    FLOOR = 1
  };

struct TileStruct
{
  eTileName up;
  eTileName down;
  TileStruct() {}
  TileStruct(const eTileName& u, const eTileName& d) 
    : up(u), down(d)
  { }
  TileStruct&	operator=(const TileStruct & t)
  {
    this->up = t.up;
    this->down = t.down;
    return (*this);
  }
};

#endif // __TILEINFO_HH
