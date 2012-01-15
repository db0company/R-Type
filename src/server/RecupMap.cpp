#include <cstring>
#include <map>
#include <fstream>
#include <iostream>
#include <string>
#include <cstdlib>
#include "RecupMap.hpp"

RecupMap::RecupMap()
{
  st.push_back(TileSize1A);
  st.push_back(TileSize1B);
  st.push_back(TileSize1C);
  st.push_back(TileSize2);
  st.push_back(TileSize3);
  st.push_back(TileSize4BaseLeft);
  st.push_back(TileSize4Left);
  st.push_back(TileSize4BaseRight);
  st.push_back(TileSize4Right);
  st.push_back(TileSize2Diago);
  st.push_back(TileAlien1);
  st.push_back(TileAlien2);
  st.push_back(TileAlien3);
}

RecupMap::~RecupMap()
{

}

eTileName	RecupMap::getEnumFromInt(unsigned int i)
{
  if (i < st.size())
    return (st[i]);
  return (TileEmpty);
}

void		RecupMap::recupFromFile(const std::string& file)
{
  std::fstream	os;
  char		buff1[4];
  char		buff2[4];
  std::string	tmp;
  int		nb1;
  int		nb2;
  int		i = 0;
  std::vector<TileStruct>::iterator it;
  TileStruct	t;
  
  os.open(file.c_str(), std::fstream::in);
  mapContent.reserve(500);
  while (os.good() == true)
    {
      memset(buff1, 0, 4);
      memset(buff2, 0, 4);
      os.getline(buff1, 4, ';');
      nb1 = atoi(buff1);
      os.getline(buff2, 4, '|');
      nb2 = atoi(buff2);
      tmp = buff2;
      
      it = mapContent.end();
      t = TileStruct(getEnumFromInt(nb1), getEnumFromInt(nb2));
      mapContent.insert(it, t);
      ++i;
    }
  it = mapContent.begin();
  std::cout << "FINAL @@##" << std::endl;
  while (it != mapContent.end())
    {
      std::cout << (*it).up << " "<< (*it).down << std::endl;
      ++it;
    }
}

void		RecupMap::mstrtab(char const *s)
{
  int		i = 0;
  int		x;
  int		y;
  std::vector<TileStruct>::iterator it;
  TileStruct	t;

  while (s[i] != '\0')
    {
      x = atoi(s + i);
      while (s[i] != ';')
	++i;
      ++i;
      y = atoi(s + i);
      while (s[i] != '|' && s[i] != '\0')
	++i;
      it = mapContent.end();
      t = TileStruct(getEnumFromInt(x), getEnumFromInt(y));
      mapContent.insert(it, t);
      if (s[i] == '|')
	++i;
    }
}

void		RecupMap::recupFromString(const std::string& str)
{
  mstrtab(str.c_str());
}

const TileStruct&	RecupMap::operator[](int i)
{
  return (this->mapContent[i]);
}

int			RecupMap::size()const
{
  return (this->mapContent.size());
}
