#include <SFML/Audio.hpp>
#include <fstream>
#include "MySound.hpp"

MySound::MySound(const std::string &file)
{
  if (!Buffer.LoadFromFile(file))
    throw (std::ios_base::failure("Can't load sound."));
  Sound.SetBuffer(Buffer);
  Sound.SetVolume(5);
}


MySound::~MySound()
{

}

void MySound::PlaySound()
{
  Sound.Play();
}

void MySound::PauseSoud()
{
  Sound.Pause();
}

void MySound::StopSound()
{
  Sound.Stop();
}

sf::Sound::Status MySound::GetSoundState()const
{
  sf::Sound::Status state = Sound.GetStatus();
  return (state);
}
