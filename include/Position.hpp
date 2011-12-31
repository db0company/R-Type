#ifndef		__POSITION_HPP__
# define	__POSITION_HPP__

class		Position
{
public:
  float		x;
  float		y;
  Position(float x, float y);
  Position();
  Position(const Position& old);
  ~Position();
  bool		operator=(const Position& old)const;
  Position	&operator=(const Position& old);
};

#endif		/*__POSITION_HPP__*/
