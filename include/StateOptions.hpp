#ifndef STATEOPTIONS_H
# define STATEOPTIONS_H

#include "Sfml.hpp"
#include "Istate.hpp"
#include "AnnimTest.hpp"

namespace LibGraphic
{

  class StateOptions : public AState
  {

  private:
    enum eSelectedButton
      {
	BUTTON_OPTIONS_NAME,
	BUTTON_OPTIONS_IP,
	BUTTON_OPTIONS_PORT,
	BUTTON_OPTIONS_VOL_MUSICS,
	BUTTON_OPTIONS_VOL_EFFECTS,
	BUTTON_OPTIONS_LANG_EN,
	BUTTON_OPTIONS_LANG_FR,
	BUTTON_OPTIONS_BACK,
	BUTTON_OPTIONS_VALIDATE
      };

  public:
    StateOptions(std::map<std::string const, GraphicRessource *> const &,
		       std::map<std::string const, MyMusic *> const &,
		       std::map<std::string const, MySound *> const &,
		       std::map<std::string const, sf::Font *> const &,
		       sf::RenderWindow &);
    ~StateOptions();
    virtual bool init();
    virtual void draw();
    virtual Event gereEvent();
    virtual eStates getNextState();

 public:
    void setNextState(eState d);

  public:
    std::string const & getName() const;
    std::string const & getIp() const;
    std::string const & getPort() const;

    bool isDefaultName() const;
    bool isDefaultIp() const;
    bool isDefaultPort() const;

  private:
    void drawText();
    void drawCursor();
    void cursorMenuPos(const sf::Event&);
    void readText(const sf::Event &);

  private:
    eStates _nextState;
    eSelectedButton _currentButton;
    sf::Clock Clock;
  private:
    std::string _name;
    std::string _ip;
    std::string _port;

    bool _isDefaultName;
    bool _isDefaultIp;
    bool _isDefaultPort;
    eGraphicAction _action;

    AnnimTest * test;

  };

}

#endif // STATEOPTIONS_H
