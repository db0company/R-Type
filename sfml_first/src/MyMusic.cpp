#include <string>
#include <SFML/Audio.hpp>
#include <fstream>
#include "MyMusic.hpp"

LibGraphic::MyMusic::MyMusic(const std::string &file)
{
  if (!Music.OpenFromFile(file))
    throw (std::ios_base::failure("can't load music."));
  Music.SetVolume(15);
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
