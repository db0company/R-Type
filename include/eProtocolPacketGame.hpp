#ifndef		__EPROTOCOLPACKETGAME_HPP__
# define	__EPROTOCOLPACKETGAME_HPP__

enum		eProtocolPacketGame
  {
    GAME_ERROR		= 99,
    GETGAME		= 0,
    GETLEVELGAME	= 1,
    CREATEGAME		= 2,
    JOINGAME		= 3,
    QUITGAME		= 4,
    ENDGAME		= 5,
    STARTGAME		= 6,
    GAME_MAX		= 7
  };

#endif		/*__EPROTOCOLPACKETGAME_HPP__*/
