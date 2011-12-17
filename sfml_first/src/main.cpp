#include "Sfml.hpp"
#include "AudioUtils.hpp"

LibGraphic::Volume gVolume;

int main()
{
  LibGraphic::Sfml test;

  test.init();
  while (true)
    {
      test.getEvent();
      test.clean();
      test.draw();
    }
}
