#ifndef STATEOPTIONS_H
# define STATEOPTIONS_H

#include "Sfml.hpp"
#include "Istate.hpp"

namespace LibGraphic
{

  class StateOptions : public IState
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
    virtual eGraphicAction getAction();
    virtual void setAction(eGraphicAction);

 public:
    sf::Sprite & getSprite(std::string const &) const;
    MyMusic * getMusic(std::string const &) const;
    sf::Font * getFont(std::string const &) const;
   inline sf::String * getStdToSfString(std::string const &, sf::Font *);

  public:
    std::string const & getName() const;
    std::string const & getIp() const;
    std::string const & getPort() const;

    bool isDefaultName() const;
    bool isDefaultIp() const;
    bool isDefaultPort() const;

  private:
    void drawText();
    void cursorMenuPos(const sf::Event&);
    void readText(const sf::Event &);

  private:
    std::map<std::string const, GraphicRessource *>
    const & _ressourcesSprite;
    std::map<std::string const, MyMusic *> const & _ressourcesPlayList;
    std::map<std::string const, MySound *> const & _ressourcesSounds;
    std::map<std::string const, sf::Font *> const & _ressourcesFont;
    sf::RenderWindow & _app;

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
  };

}

#endif // STATEOPTIONS_H
