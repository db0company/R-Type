#ifndef		__MYSOUND_HPP__
# define	__MYSOUND_HPP__

#include <string>
#include <SFML/Audio.hpp>
#include "AudioUtils.hpp"

namespace LibGraphic
{

  class MySound
  {
  private:
    sf::SoundBuffer Buffer;
    sf::Sound Sound;
  public:
    MySound(const std::string &file);
    ~MySound();
    void PlaySound();
    void PauseSoud();
    void StopSound();
    sf::Sound::Status GetSoundState()const;
  };

}

# endif
