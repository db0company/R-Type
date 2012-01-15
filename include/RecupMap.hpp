#ifndef		__RECUPMAP__HPP__
# define	__RECUPMAP__HPP__

# include <istream>
# include <vector>
# include "TileInfo.hpp"

class		RecupMap
{
private:
  std::vector<TileStruct> mapContent;
  std::vector<eTileName> st;
public:
  RecupMap();
  ~RecupMap();
  eTileName	getEnumFromInt(unsigned int i);
  void	recupFromFile(const std::string& file);
  const TileStruct&	operator[](int i);
  int		size()const;
};

#endif		/*__RECUPMAP__HPP__*/
