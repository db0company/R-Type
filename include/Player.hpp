#ifndef		__PLAYER_HPP__
# define	__PLAYER_HPP__

#include "Entities.hpp"
#include "User.hpp"
class		Player : public Entities
{
public:
  Player(User *us, const std::string& name);
  ~Player();
  Player(Player const &p);
  Player &operator=(Player const &);
  const std::string&	getIp()const;
  User		*getUser();
  int		getId()const;
  void		setId(int i);
  void		AddToScore(int i);
  int		getScore()const;
private:
  User		*us;
  int		id;
  int		score;
};

#endif		/*__PLAYER_HPP__*/
