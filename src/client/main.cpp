//#include "Sfml.hpp"
#include "AudioUtils.hpp"
#include "Client.hpp"

LibGraphic::Volume gVolume;

int main()
{
  Client client("127.0.0.1", 12348);

  if (client.init())
    client.run();
}
