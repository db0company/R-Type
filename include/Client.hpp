#ifndef CLIENT_H_
# define CLIENT_H_

#include "Sfml.hpp"
#include "ClientNetwork.hpp"

class	Client
{
private:
  Client(const Client&);
  Client&	operator=(const Client&);
public:
  Client(void);
  ~Client(void);
  Client(std::string const &ip, int port);

  bool init(void);
  bool run(void);
  bool gereAction(LibGraphic::Event e, bool);
  bool actionRefresh(void);
  bool actionConnect(void);
  bool actionJoin(std::string const &id, int id_game, bool obs);
  bool actionCreate(std::string const &log, std::string const &name,
		    std::string const &lvl, int slot, bool spec);
  bool actionChat(std::string const &, std::string const &);
  bool actionStart(void);
  bool actionGetLvl(void);

  LibGraphic::Sfml	&getGraphic(void);
private:
  ClientNetwork		cNetwork;
  LibGraphic::Sfml	cGraphic;
};

#endif	// CLIENT_H_
