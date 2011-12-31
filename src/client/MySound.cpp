#include <SFML/Audio.hpp>
#include <fstream>
#include "MySound.hpp"

extern LibGraphic::Volume gVolume;

LibGraphic::MySound::MySound(const std::string &file)
{
  if (!Buffer.LoadFromFile(file))
    throw (std::ios_base::failure("Can't load sound."));
  Sound.SetBuffer(Buffer);
  Sound.SetVolume(gVolume.soundVolume);
}


LibGraphic::MySound::~MySound()
{

}

void LibGraphic::MySound::PlaySound()
{
  Sound.Play();
}

void LibGraphic::MySound::PauseSoud()
{
  Sound.Pause();
}

void LibGraphic::MySound::StopSound()
{
  Sound.Stop();
}

void LibGraphic::MySound::UpdateVolume()
{
  Sound.SetVolume(gVolume.soundVolume);
}

sf::Sound::Status LibGraphic::MySound::GetSoundState()const
{
  sf::Sound::Status state = Sound.GetStatus();
  return (state);
}
