#include "Sfml.hpp"

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
