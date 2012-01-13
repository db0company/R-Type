#include "AudioUtils.hpp"
#include "Client.hpp"
#include "Language.hpp"

LibGraphic::Volume gVolume;
LibGraphic::Language language;

int main()
{
  Client client;

  if (client.init())
    return (client.run());
  system("pause");
  return (0);
}
