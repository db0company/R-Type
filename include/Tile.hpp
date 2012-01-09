#ifndef		__TILE_HPP__
# define	__TILE_HPP__

#include "AObject.hpp"
#include "TileInfo.hpp"

class		Tile : public AObject
{
private:
  eTileName	tileType;
public:
  Tile();
  Tile(eTileName t);
  eTileName	getTileType()const;
  void		setTileType(eTileName t);
  ~Tile();
  Tile&		operator=(const Tile& old);
};

#endif		/*__TILE_HPP__*/
