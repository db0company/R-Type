
#ifndef			_USER_HPP__
# define		_USER_HPP__

# include		"ATCPClientSocket.h"
# include		<string>

class			User
{
/* ************************************************************************* */
/*                             Attributes                                    */
/* ************************************************************************* */
 private:
  bool			_safe;
  bool			_log;
  std::string		_login;
  ATCPClientSocket*	_socket;
  std::string		_ip;

/* ************************************************************************* */
/*                             Coplien Form                                  */
/* ************************************************************************* */
 public:
  User(ATCPClientSocket *, std::string const &ip);
  User(User const &);
  User &		operator=(User const &);
  ~User(void);

/* ************************************************************************* */
/*                             Member Functions                              */
/* ************************************************************************* */
 public:
  bool			isSafe(void)const;
  void			setSafe(bool);
  bool			isLog(void)const;
  void			setLog(bool);
  ATCPClientSocket *	getSocket(void);
  std::string const &	getIp(void)const;
};

#endif			// _USER_HPP__
