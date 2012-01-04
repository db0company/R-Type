
#ifndef		PERSOTYPES_H_
# define	PERSOTYPES_H_

typedef		void			generic;
typedef		unsigned short		ushort;
typedef		unsigned int		uint;
typedef		unsigned char		uchar;

typedef		char			DataRawType;

# define	KO			0
# define	OK			!KO

# ifdef _WIN32
typedef		unsigned int		UInt32;
# else
#  include	<stdint.h>
typedef		uint32_t		UInt32;
# endif

#endif		// !PERSOTYPES_H_
