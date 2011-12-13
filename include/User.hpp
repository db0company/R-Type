#ifndef _USER_HPP__
#define _USER_HPP__

#include "ATCPClientSocket.h"

class User
{
public:
  User(void);
  ~User(void);
  User& operator=(User const &);
  User(User const &);
private:
  bool			_log;
  std::string		_login;
  //eConnectStatus	_cstatus;
  ATCPClientSocket*	_socket;
};

#endif// _USER_HPP__
