#ifndef __OS_HPP__
# define __OS_HPP__

# ifdef _WIN32
#  include "OSWindows.hpp"
# else
#  include "OSUnix.hpp"
# endif /* _WIN32 */

#endif /* __OS_HPP__ */
