#ifndef		__ITHREADDATA_HPP__
# define	__ITHREADDATA_HPP__

struct		IThreadData
{
  virtual void	ExecParam() = 0;
  virtual ~IThreadData() {}
};

#endif		/*__ITHREADDATA_HPP__*/
