#ifndef INFOGAME_H_
# define INFOGAME_H_

#include <string>

class	InfoGame
{
public:
  InfoGame(void);
  ~InfoGame(void);
  InfoGame(const InfoGame&);
  InfoGame&	operator=(const InfoGame&);

  unsigned int	getId(void) const;
  std::string const & getOwner(void) const;
  std::string const & getName(void) const;
  std::string const & getMap(void) const;
  bool		getObs(void) const;
  unsigned int	getPlayers(void) const;
  unsigned int	getPlayerMax(void) const;

  void setId(unsigned int id);
  void setOwner(std::string const &owner);
  void setName(std::string const &);
  void setMap(std::string const &);
  void setObs(bool);
  void setPlayers(unsigned int);
  void setPlayerMax(unsigned int);

private:
  unsigned int	_id;
  std::string	_owner;
  std::string	_name;
  std::string	_map;
  bool		_obs;
  unsigned int	_players;
  unsigned int	_player_max;
};

#endif	// INFOGAME_H_
