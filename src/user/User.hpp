
#ifndef			USERHPP
# define		USERHPP

# include		"UserSocket.hpp"
# include		"ATCPClientSocket.h"
# include		<string>

class			User
{
/* ************************************************************************* */
/*                             Attributes                                    */
/* ************************************************************************* */
 private:
  bool			safe;
  bool			log;
  std::string		login;
  std::string		ip;
  UserSocket		tcp;

/* ************************************************************************* */
/*                             Coplien Form                                  */
/* ************************************************************************* */
 public:
  User(ATCPClientSocket *, std::string const & ip);
  User(User const & other);
  User &		operator=(User const & other);
  ~User(void);

/* ************************************************************************* */
/*                             Getters/Setters                               */
/* ************************************************************************* */
 public:
  bool			isSafe(void)const;
  void			setSafe(bool);
  bool			isLog(void)const;
  void			setLog(bool);
  ATCPClientSocket *	getSocketTCP(void);
  std::string const &	getIp(void)const;

/* ************************************************************************* */
/*                             Member Functions                              */
/* ************************************************************************* */
 public:
  
};

#endif			// USERHPP
