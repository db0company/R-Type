#ifndef __DEFINEEXPORTMONSTER_HPP__
# define __DEFINEEXPORTMONSTER_HPP__

# ifdef _WIN32
#  ifdef LIBMONSTER_EXPORTS
#   define LIBMONSTER_API __declspec(dllexport)
#  else
#   define LIBMONSTER_API __declspec(dllimport)
#  endif /* LIBMONSTER_EXPORTS */

# endif /* _WIN32 */

#endif /* __DEFINEEXPORTMONSTER_HPP__ */
