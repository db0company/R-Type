#ifndef SFML_H_
# define SFML_H_

#include <list>
#include <SFML/Graphics.hpp>
#include "MyMusic.hpp"
#include "MySound.hpp"
#include "IGraphic.hpp"
#include "GraphicUtils.hpp"
#include "GraphicClientState.hpp"
#include "EGraphicAction.hpp"
#include "InfoGame.hpp"
#include "RecupMap.hpp"
//#include "ClientNetwork.hpp"

#define WINDOWNAME "R-Type"

class			ClientNetwork;

namespace LibGraphic
{

  class	Sfml : public IGraphic
  {
    Sfml(void);
  public:
    Sfml(ClientNetwork &);
    ~Sfml(void);
    Sfml(const Sfml&);
    Sfml&	operator=(const Sfml&);
  public:
    virtual bool init();
    virtual Event getEvent();
    virtual void quit();
    virtual void clean();
    virtual void draw();
    // Getter/Setter pour le reseau

  public:
    void	   setCurrentState(eStates);
    void	   goToNextState(void);
    void	   setNextState(eState s, eStates d);
    std::string const &getGameName(void) const;
    std::string const &getGameLvl(void) const;
    void setGameName(std::string const &);
    void setGameLvl(std::string const &);

    std::list<std::string> &getLvlList(void);
    std::string const & getIp() const;
    std::string const & getLogin() const;
    int getPort() const;
    int getIdGame() const;
    std::string const & getLevel() const;
    int getSlot() const;
    bool getSpectator() const;
    std::string const & getMessage() const;
    std::string const & getInGameName() const;
    void setMessage(std::string const &s);
    RecupMap &getRecupMap(void);
    std::string const & getConversation() const;
    void addToConversation(std::string const &);
    void setGameForPreview(InfoGame*);
    InfoGame * getGameForPreviewFromRoomlist(void);
    InfoGame * getGameForPreviewFromCreate(void);
    std::map<int, InfoGame *> &getInfoGameMap(void) const;
    void setInfoGameMap(std::map<int, InfoGame *> &nmap);
    std::list<std::string> &getPlayerNameList(void);
    eMovement getLastMove(void) const;

  public:
    void errorMessage(std::string const &);

  private:
    bool loadFont();
    bool loadSound();
    bool loadMusic();
    bool loadSprite();
    bool loadRessources();
    void createStates();
    inline bool isFullscreen(std::string s);
    inline std::string getNextInfoRessource(std::string &);
    inline unsigned int getIntFromS(std::string s);

  private:
    std::string _errorMessage;
    int _width;
    int _height;
    sf::RenderWindow _app;
    eStates _currentState;
    GraphicClientState * _graphicState;

    std::map<std::string const, GraphicRessource *> _ressourcesSprite;
    std::map<std::string const, MyMusic *> _ressourcesPlayList;
    std::map<std::string const, MySound *> _ressourcesSounds;
    std::map<std::string const, sf::Font *> _ressourcesFont;
    ClientNetwork &_network;
  };

}

#endif	// SFML_H_
