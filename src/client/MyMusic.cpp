#include <iostream>
#include <string>
#include <SFML/Audio.hpp>
#include <fstream>
#include "MyMusic.hpp"

extern LibGraphic::Volume gVolume;

LibGraphic::MyMusic::MyMusic(const std::string &file)
{
  if (!Music.OpenFromFile(file))
    throw (std::ios_base::failure("can't load music."));
  Music.SetVolume(gVolume.musicVolume);
}


LibGraphic::MyMusic::~MyMusic()
{

}

void LibGraphic::MyMusic::PlayMusic()
{
  Music.Play();
}

void LibGraphic::MyMusic::PauseMusic()
{
  Music.Pause();
}

void LibGraphic::MyMusic::StopMusic()
{
  Music.Stop();
}

sf::Music::Status LibGraphic::MyMusic::GetMusicState()const
{
  sf::Music::Status state = Music.GetStatus();
  return (state);
}
