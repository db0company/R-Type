#ifndef		__POSITION_HPP__
# define	__POSITION_HPP__

class		Position
{
private:
public:
  int		x;
  int		y;
  int		tilex;
  int		tiley;
  Position(int x, int y);
  Position();
  Position(const Position& old);
  ~Position();
  bool		operator==(const Position& old)const;
  Position	&operator=(const Position& old);
  int		getX()const;
  int		getY()const;
};

#endif		/*__POSITION_HPP__*/
