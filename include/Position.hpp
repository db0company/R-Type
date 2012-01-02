#ifndef		__POSITION_HPP__
# define	__POSITION_HPP__

class		Position
{
private:
public:
  float		x; // je crois que ca se fait dans ce cas la de
  float		y; // mettre en public. Insulez moi si c pas le cas.
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
