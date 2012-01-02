//#include "Sfml.hpp"
#include "AudioUtils.hpp"
#include "Client.hpp"
#include "Language.hpp"


LibGraphic::Volume gVolume;
LibGraphic::Language language;

int main()
{
  Client client("127.0.0.1", 12348);

  if (client.init())
    client.run();
}
