#ifndef _USER_HPP__
#define _USER_HPP__

#include "ATCPClientSocket.h"
#include <string>

class User
{
private:
  User(void);
public:
  User(ATCPClientSocket *, std::string const &ip);
  ~User(void);
  User& operator=(User const &);
  User(User const &);
  bool			isSafe(void)const;
  void			setSafe(bool);
  bool			isLog(void)const;
  void			setLog(bool);
  ATCPClientSocket	*getSocket(void);
  std::string const	&getIp(void)const;
private:
  bool			_safe;
  bool			_log;
  std::string		_login;
  ATCPClientSocket*	_socket;
  std::string		_ip;
};

#endif// _USER_HPP__
