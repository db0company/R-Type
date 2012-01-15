
#include <iostream>
#include <sstream>
#include <string>
#include <cstring>
#include <cstdlib>
#include "HighScore.hpp"

HighScore::HighScore()
{
  char	buff[127];

  file.open(".highscore", std::fstream::in | std::fstream::out);
  if (file.is_open() == true)
    {
      while (file.good() == true)
	{
	  memset(buff, 0, 126);
	  file.getline(buff, 126);
	  list.push_back(buff);
	}
      file.close();
    }
}


HighScore::~HighScore()
{

}

bool	HighScore::addInFile()
{
  std::vector<std::string>::const_iterator it = list.begin();

  file.open(".highscore", std::fstream::out | std::fstream::trunc);
  if (file.is_open() == true)
    {
      while (it != list.end())
	{
	  file << (*it);
	  ++it;
	  if (it != list.end())
	    file << std::endl;
	}
      file.close();
    }
  else
    return (false);
  return (true);
}

bool	HighScore::addNewScore(int newScore, const std::string& newName)
{
  std::stringstream os;
  std::vector<std::string>::iterator it = list.begin();
  int		i = 0;
  while (it != list.end())
    {
      if (atoi((*it).c_str()) < newScore)
	{
	  os << newScore << " " << newName;
	  list.insert(it, os.str());
	  it = list.end();
	  --it;
	  if (list.size() > 5)
	    list.erase((list.end())--);
	  addInFile();
	  return (true);
	}
      ++i;
      ++it;
    }
  return (false);
}

const std::vector<std::string>&		HighScore::getListScore()const
{
  return (this->list);
}
