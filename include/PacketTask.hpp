#ifndef _PACKETTASK_HPP_
#define _PACKETTASK_HPP_

struct PacketTask
{
  void *(*pfonct)(void *);
  void *param;
};

#endif // _PACKETTASK_HPP_
