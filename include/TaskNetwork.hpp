#ifndef		__TASKNETWORK_HPP__
# define	__TASKNETWORK_HPP__

class		TaskNetwork
{
private:
public:
  TaskNetwork(void);
  ~TaskNetwork(void);
  // struct {User *user, ATCPServerSocket *, Packet *}
  void sendToClient(void *data);
};

#endif		/*__TASKNETWORK_HPP__*/
