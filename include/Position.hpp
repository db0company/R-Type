#ifndef		__POSITION_HPP__
# define	__POSITION_HPP__

class		Position
{
private:
public:
  float		x;
  float		y;
  unsigned int		tilex;
  unsigned int		tiley;
  Position(float x, float y);
  Position();
  Position(const Position& old);
  ~Position();
  bool		operator==(const Position& old)const;
  Position	&operator=(const Position& old);
  int		getX()const;
  int		getY()const;
};

#endif		/*__POSITION_HPP__*/
