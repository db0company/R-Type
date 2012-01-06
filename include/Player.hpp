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
private:
  User		*us;
};

#endif		/*__PLAYER_HPP__*/
