#ifndef		__RECUPMAP__HPP__
# define	__RECUPMAP__HPP__

# include <istream>
# include <map>
# include "TileInfo.hpp"

class		RecupMap
{
private:
  std::map<int, TileStruct> mapContent;
  std::map<std::string, eTileName> st;
public:
  RecupMap();
  ~RecupMap();
  eTileName	getEnumFromString(const std::string& s1)const;
  void	recupFromFile(const std::string& file);
  const TileStruct&	operator[](int i);
  int		size()const;
};

#endif		/*__RECUPMAP__HPP__*/
