#ifndef GRAPHICCLIENTSTATE_H_
# define GRAPHICCLIENTSTATE_H_

#include <list>
#include <SFML/Graphics.hpp>
#include "MySound.hpp"
#include "RecupMap.hpp"
#include "MyMusic.hpp"
#include "GraphicUtils.hpp"
#include "IGraphic.hpp"
#include "Istate.hpp"
#include "EGraphicAction.hpp"
#include "InfoGame.hpp"
#include "SpriteInfo.hpp"
//#include "BulletMovement.hpp"
//#include "PlayerMovement.hpp"
namespace LibGraphic
{
  class PlayerMovement;
  class BulletMovement;
  class AMonsterMovement;
  class	GraphicClientState
  {
  public:
    GraphicClientState(std::map<std::string const, GraphicRessource *> const &,
		       std::map<std::string const, MyMusic *> const &,
		       std::map<std::string const, MySound *> const &,
		       std::map<std::string const, sf::Font *> const &,
		       sf::RenderWindow &);
    ~GraphicClientState(void);

  public:
    void draw(eStates);
    Event getEventFromState(eStates);
    eStates goToNextState(eStates scene);

  public:
    void resetInGameState(void);
    void resetRoomListState(void);
    std::string const &getGameName(void) const;
    std::string const &getGameLvl(void) const;
    void setGameName(std::string const &);
    void setGameLvl(std::string const &);
    eGraphicAction getAction(eStates scene);
    void setAction(eGraphicAction, eStates);
    void setNextState(eStates, eStates);
    std::list<std::string> &getLvlList(void);
    std::string const & getIp() const;
    std::string const & getLogin() const;
    int getPort();
    int getIdGame() const;
    std::string const & getLevel() const;
    int getSlot() const;
    bool getSpectator() const;
    std::string const & getMessage() const;
    void setMessage(std::string const &);
    RecupMap &getRecupMap(void);
    std::list<BulletMovement *> &getBulletList();
    std::string const & getConversation() const;
    void addToConversation(std::string const &);
    std::string const &getInGameName(void) const;
    void setGameForPreview(InfoGame *);
    std::map<int, InfoGame *> &getInfoGameMap(void);
    void setInfoGameMap(std::map<int, InfoGame *> &nmap);
    InfoGame * getGameForPreviewFromRoomlist(void);
    InfoGame * getGameForPreviewFromCreate(void);
    std::list<std::string> &getPlayerNameList(void);
    eMovement getLastMove(void) const;
    eBulletType getLastBullet(void) const;
    std::map<int, PlayerMovement *> const & getPlayerMap() const;
    std::map<int, PlayerMovement *> & getPlayerMap();
    std::map<int, AMonsterMovement *> &getMonsterMap();

    eShipColor getMyId() const;
    void setMyId(eShipColor id);
    void setMyPosition(Coord c);
    void setScore(unsigned int);
    void setLives(unsigned int);
 private:
    Event eventStart(eStates & scene);
    void loadStates();

  private:
    std::map<std::string const, GraphicRessource *>
    const & _ressourcesSprite;
    std::map<std::string const, MyMusic *> const & _ressourcesPlayList;
    std::map<std::string const, MySound *> const & _ressourcesSounds;
    std::map<std::string const, sf::Font *> const & _ressourcesFont;
  private:
    std::map<eStates, AState *> _stateInfos;
    sf::RenderWindow & _app;
    sf::Event _catchedEvent;
  };

}

#endif	// GRAPHICCLIENTSTATE.HPP_H_
