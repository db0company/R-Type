
#ifndef			PROTOCOLPACKETGROUP_H_
# define		PROTOCOLPACKETGROUP_H_

enum			eProtocolPacketGroup
  {
    GROUP_ERROR		= 99,
    THE_GAME		= 0,
    GAME_DETAILS	= 1,
    MOVEMENT		= 2,
    LOBBY		= 3,
    GROUP_MAX		= 4
  };

#endif			// !PROTOCOLPACKETGROUP_H_
