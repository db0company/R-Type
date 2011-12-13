#include <string>
#include <SFML/Audio.hpp>

#ifndef		__MYMUSIC_HPP__
# define	__MYMUSIC_HPP__

class MyMusic
{
private:
  sf::Music Music;
public:
  MyMusic(const std::string &file, bool loop);
  ~MyMusic();
  void PlayMusic();
  void PauseMusic();
  void StopMusic();
  sf::Music::Status GetMusicState()const;

};

# endif
