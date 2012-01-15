
#include <vector>
#include <string>
#include <sstream>
#include <fstream>

#ifndef		__HIGHSCORE_HPP__
# define	__HIGHSCORE_HPP__

class		HighScore
{
private:
  std::vector<std::string> list;
  std::fstream file;
public:
  HighScore();
  ~HighScore();
  bool	addInFile();
  bool	addNewScore(int newScore, const std::string& newName);
  const std::vector<std::string>&		getListScore()const;
};

#endif
