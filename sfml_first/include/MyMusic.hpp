#ifndef		__MYMUSIC_HPP__
# define	__MYMUSIC_HPP__

#include <string>
#include <SFML/Audio.hpp>
#include "AudioUtils.hpp"

namespace LibGraphic
{

  class MyMusic
  {
  private:
    sf::Music Music;
  public:
    MyMusic(const std::string &file);
    ~MyMusic();
    void PlayMusic();
    void PauseMusic();
    void StopMusic();
    sf::Music::Status GetMusicState()const;
  };

}

# endif
