#ifndef SFML_H_
# define SFML_H_

#include <SFML/Graphics.hpp>
#include "MyMusic.hpp"
#include "MySound.hpp"
#include "IGraphic.hpp"
#include "GraphicUtils.hpp"
#include "GraphicClientState.hpp"
#include "EGraphicAction.hpp"
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
    eGraphicAction getAction() const;
    void	   setAction(eGraphicAction);
    void	   setNextState(eStates s);
    std::string const & getIp() const;
    int getPort() const;
    int getIdGame() const;
    std::string const & getLevel() const;
    int getSlot() const;
    bool getSpectator() const;
    std::string const & getMessage() const;
    std::string const & getGameName() const;

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
