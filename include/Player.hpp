#ifndef		__PLAYER_HPP__
# define	__PLAYER_HPP__

#include "Entities.hpp"
#include "User.hpp"
class		Player : public Entities
{
public:
  Player(User *us, const std::string& name);
  ~Player();
  const std::string&	getIp()const;
  User		*getUser();
  int		getId()const;
  void		setId(int i);
private:
  User		*us;
  int		id;
};

#endif		/*__PLAYER_HPP__*/
