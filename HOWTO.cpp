//Comment Creer un Packet Reseau: (ProtocolPacket)

//    ProtocolPacket est une structure dans [R-Type/include/ProtocolPacket.h]
//    Elle contient un header. on rempli le header avec la fonction statique de
//    PacketFactory::createPacket (les 2 premiers arguments)
//    static ProtocolPacket *createPacket(eProtocolPacketGroup group,
//                                        ushort instruction,
//                                        PacketData *);

//    Pour savoir quel groupe utiliser et quelle instruction pour le header
//    regarder dans include/eProtocol*.h*

//    La Data du Packet (3eme Argument) est rempli a la main avec la classe
//    PacketData [R-Type/src/protocol/PacketData.cpp] en Utilisant les fonctions
//    membres AddChar() AddString() AddShort().

#include "PacketData.hpp"
#include "PacketFactory.hpp"

int	reponse_du_server_a_la_demande_de_creation_de_game_qui_fail(User *user,
								    Server &s)
{
  //    1) Creation du PacketData
  PacketData *data = new PacketData;

  //    2) Remplissage de la data. Par exemple si le serveur a recu une demande de
  //       creation de game d'un client et que le client a envoyer de la merde.
  //       le serveur lui reponds avec un packet contenant une data avec une octet
  //       contenant un 0 (failure). On fait donc:

  data->addChar(0);

  //       Le protocol permet au serveur d'envoyer plus d'information sur le pourquoi
  //       ca a fail en envoyant en plus du char une string.

  data->addString("C'est quoi cette game que t'essaye de creer imbecile ? ");

  //	 La data est termine. Il faut maintenant creer le ProtocolPacket:

  ProtocolPacket *packet_to_send = PacketFactory::createPacket(THE_GAME, static_cast<ushort>(CREATEGAME), to_send);

  //	  ***** Pour l'envoyer par TCP *****:
  //	  Il faut un pointeur vers le client qui doit recevoir le msg (User *user)
  //	  Puis on fait:

  user->addPacketToSend(packet_to_send);

  //      Ici ca push le packet sur la queue write du client.
  //      Plus rien a faire l'envoi etc c'est geree.

  //      ***** Pour l'envoyer par UDP sans passer par le thread*****:
  //      Idem que tcp sauf qu'on appel addPacketToSendUDP au lieu de addPacketToSend

  user->addPacketToSendUDP(packet_to_send);


  //      ***** Pour l'envoyer par UDP AVEC THREAD o/ *****:
  //	  On creer une struct SendToClientData {packet, ip}
  SendToClientData *UDP = new SendToClientData;
  //      On la remplis

  UDP->packet = packet_to_send;
  UDP->ip = user->getIp();

  //	  On creer une Packet Task (thread)
  //	  On lui passe le taskManager du server, la fonction udp et
  //      la data (SendToClientData)

  PacketTask *pa = new PacketTask(server->getTaskManager(), &TaskNetwork::sendtoclientdata, UDP);
  //	  On push dans la safequeue et signal qu'on a add un elem :)

  server.getTaskQueue().push(pa);
  server.getCondVar()->signal();

  // Et voila o/ Un thread va gentiment executer le pfonct d'envoi udp

  // Dans R-Type/src/server/protocol/action/*.cpp il y a plein d'exemple de packet creer
  // a la facon TCP (et un exemple UDP dans ProtocolGame::CreateGame
}

//cote serveur si tu recoi un packet Move d'un client ca sera dans /src/server/protocol/ProtocolMovement.cpp
// dans la function ActionMove.
// ca marche comme ca pour tout.
// chaque packet a un group (== la classe ProtocolMovement ProtocolLobby ProtocolGame etc)
// chaque packet a aussi une instruction (== une fonction de la classe associe au groupe)
// la fonction en question contien un PacketData (la data du packet, logique)
// elle contien aussi un user * (le user qui a envoye le packet)
// et elle contien un Server & (reference sur le serveur pour pouvoir avoir access a tout par getter (safequeue pour push, game manager pour manager... etc))
// pour envoyer un message a un user on fait user->addPacketToSend(ICI LE PACKET);
// si un user a creer une game il a un pointeur vers sa game. user->getGame() (peut return null!)
// on peut recuperer la liste des users de la game avec (game->getUserMap)
// c'est utile pour envoyer un meme message a tout les client de la game (iterator FTW)


// cote client si tu recoi un packet c'est pareil. c'est dans /src/CLIENT/protocol/Protocol*.cpp
// meme style: si tu recoi une instruction GETGAME de group GAME c'est dans ProtocolGame.cpp la fonction ActionGetGame.
// contrairement au cote serveur on a pas de User * (normal, c'est toujours le serveur qui envoi le packet), et a la place dun Server & on a un Client & (pour getter / setter partout comme on veut.)

//cote client pour envoyer un packet on fait ClientNetwork->pushTCP(PACKET A SEND) ou pushUDP pour l'udp
//					       (contenu ds class client)


