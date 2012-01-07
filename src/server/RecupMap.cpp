#include <cstring>
#include <map>
#include <fstream>
#include <iostream>
#include <string>
#include "RecupMap.hpp"

RecupMap::RecupMap()
{
  st.insert(std::pair<std::string, eTileName>("TileSize1A", TileSize1A));
  st.insert(std::pair<std::string, eTileName>("TileSize1B", TileSize1B));
  st.insert(std::pair<std::string, eTileName>("TileSize1C", TileSize1C));
  st.insert(std::pair<std::string, eTileName>("TileSize2", TileSize2));
  st.insert(std::pair<std::string, eTileName>("TileSize3", TileSize3));
  st.insert(std::pair<std::string, eTileName>("TileSize4BaseLeft", TileSize4BaseLeft));
  st.insert(std::pair<std::string, eTileName>("TileSize4Left", TileSize4Left));
  st.insert(std::pair<std::string, eTileName>("TileSize4BaseRight", TileSize4BaseRight));
  st.insert(std::pair<std::string, eTileName>("TileSize4Right", TileSize4Right));
  st.insert(std::pair<std::string, eTileName>("TileSize2Diago", TileSize2Diago));
  st.insert(std::pair<std::string, eTileName>("TileAlien1", TileAlien1));
  st.insert(std::pair<std::string, eTileName>("TileAlien2", TileAlien2));
  st.insert(std::pair<std::string, eTileName>("TileAlien3", TileAlien3));
}

RecupMap::~RecupMap()
{

}

eTileName	RecupMap::getEnumFromString(const std::string& s1)const
{
  std::map<std::string, eTileName>::const_iterator	tile;

  if ((tile = st.find(s1)) == st.end())
    {
      std::cout << s1 << " faudrait lancer une std::error" << std::endl;
      //error
    }
  return (tile->second);
}

void		RecupMap::recupFromFile(const std::string& file)
{
  std::fstream	os;
  char		buff1[1024];
  char		buff2[1024];
  std::string	tmp;
  int		i = 0;
  size_t	y;

   os.open(file.c_str(), std::fstream::in);
   while (os.good() == true)
    {
      memset(buff1, 0, 1024);
      memset(buff2, 0, 1024);
      os.getline(buff1, 1024, ';');
      os.getline(buff2, 1024, '|');
      tmp = buff2;
      if ((y = tmp.find("\n")) != 0)
	  buff2[y] = '\0';
      mapContent.insert(std::pair<int, TileStruct
				  (i, TileStruct(
						 getEnumFromString(buff1),
						 getEnumFromString(buff2))));
      ++i;
    }
}

const TileStruct&	RecupMap::operator[](int i)
{
  return (this->mapContent[i]);
}

int			RecupMap::size()const
{
  return (this->mapContent.size());
}
