#include <string>
#include <SFML/Audio.hpp>

#ifndef		__MYSOUND_HPP__
# define	__MYSOUND_HPP__

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
