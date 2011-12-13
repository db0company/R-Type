#include <string>
#include <SFML/Audio.hpp>
#include <fstream>
#include "MyMusic.hpp"

MyMusic::MyMusic(const std::string &file, bool loop)
{
  if (!Music.OpenFromFile(file))
    throw (std::ios_base::failure("can't load music."));
  Music.SetLoop(loop);
  Music.SetVolume(15);
}


MyMusic::~MyMusic()
{

}

void MyMusic::PlayMusic()
{
  Music.Play();
}

void MyMusic::PauseMusic()
{
  Music.Pause();
}

void MyMusic::StopMusic()
{
  Music.Stop();
}

sf::Music::Status MyMusic::GetMusicState()const
{
  sf::Music::Status state = Music.GetStatus();
  return (state);
}
