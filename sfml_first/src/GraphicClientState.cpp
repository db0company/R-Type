#include "GraphicClientState.hpp"

LibGraphic::GraphicClientState::GraphicClientState(std::map<std::string const, GraphicRessource *> const & ressourcesSprite,
						   std::map<std::string const, MyMusic *> const & ressourcesPlayList,
						   std::map<std::string const, MySound *> const & ressourcesSounds,
						   std::map<std::string const, sf::Font *> const & ressourcesFont,
						   sf::RenderWindow & app):
  _ressourcesSprite(ressourcesSprite), _ressourcesPlayList(ressourcesPlayList),
  _ressourcesSounds(ressourcesSounds), _ressourcesFont(ressourcesFont),
  _app(app)
{
}

LibGraphic::GraphicClientState::~GraphicClientState(void)
{
}

sf::Sprite & LibGraphic::GraphicClientState::getSprite(std::string const & spriteName) const
{
  return ((*this->_ressourcesSprite.find(spriteName)).second->_sprite);
}

LibGraphic::MyMusic * LibGraphic::GraphicClientState::getMusic(std::string const & musicName) const
{
  return ((*this->_ressourcesPlayList.find(musicName)).second);
}

sf::Font * LibGraphic::GraphicClientState::getFont(std::string const & fontName) const
{
  return ((*this->_ressourcesFont.find(fontName)).second);
}

void LibGraphic::GraphicClientState::draw(eStates scene)
{
  switch (scene)
    {
    case START:
      {
	this->displayStart();
	break;
      }
    case ROOMLIST:
      {
	this->displayRoomlist();
	break;
      }
    case GAMEPARAMETER:
      {
	this->displayGameparameter();
	break;
      }
    case ROOM:
      {
	this->displayRoom();
	break;
      }
    case OPTIONS:
      {
	this->displayOptions();
	break;
      }
    case CREDITS:
      {
	this->displayCredits();
	break;
      }
    case RANKING:
      {
	this->displayRanking();
	break;
      }
    case INTRO:
      {
	this->displayIntro();
	break;
      }
    case INGAME:
      {
	this->displayIngame();
	break;
      }
    case UNKNOWN_STATE : break;
    default: break;
    }
}

// void LibGraphic::GraphicClientState::displayStart()
// {
//   this->_app.Draw(this->getSprite("StartBackground"));
//   MyMusic * song = this->getMusic("StartMusic");
//   if (song->GetMusicState() == sf::Music::Stopped ||
//       song->GetMusicState() == sf::Music::Paused)
//     song->PlayMusic();
// }

void LibGraphic::GraphicClientState::displayStart()
{
  sf::String *tmp;
  this->_app.Draw(this->getSprite("StartMenuBackground"));
  this->getSprite("StartMenu").SetPosition(450, 650);
  this->getSprite("StartMenu").SetColor(sf::Color(255,255,255, 200));
  this->_app.Draw(this->getSprite("StartMenu"));
  tmp = this->getStdToSfString("PLAY", this->getFont("StartFontF"));
  tmp->SetPosition(530, 750);
  tmp->Scale(2.5, 2.5);
  tmp->SetColor(sf::Color(255,255,255, 220));
  this->_app.Draw(*tmp);
  MyMusic * song = this->getMusic("StartMusic");
  if (song->GetMusicState() == sf::Music::Stopped ||
      song->GetMusicState() == sf::Music::Paused)
    song->PlayMusic();
}

void LibGraphic::GraphicClientState::displayRoomlist()
{
  //  sf::String *tmp;
  this->_app.Draw(this->getSprite("StartMenuBackground"));
  //  this->getSprite("StartMenu")->SetPosition(400, 600);
  this->_app.Draw(this->getSprite("StartMenu"));
  // tmp = this->getStdToSfString("PLAY", this->getFont("StartFontF"));
  // tmp->SetPosition(550, 720);
  // tmp->Scale(2.3, 2.3);
  // this->_app.Draw(*tmp);
  MyMusic * song = this->getMusic("StartMusic");
  if (song->GetMusicState() == sf::Music::Stopped ||
      song->GetMusicState() == sf::Music::Paused)
    song->PlayMusic();
}

void LibGraphic::GraphicClientState::displayGameparameter(){}
void LibGraphic::GraphicClientState::displayRoom(){}
void LibGraphic::GraphicClientState::displayOptions(){}
void LibGraphic::GraphicClientState::displayCredits(){}
void LibGraphic::GraphicClientState::displayRanking(){}
void LibGraphic::GraphicClientState::displayIntro(){}
void LibGraphic::GraphicClientState::displayIngame(){}


LibGraphic::Event LibGraphic::GraphicClientState::eventStart(eStates & scene)
{
  sf::Event Event;

  while (this->_app.GetEvent(Event))
    {
      if (Event.Type == sf::Event::KeyPressed)
	{
	  switch (Event.Key.Code)
	    {
	    case sf::Key::Escape:
	      //return LibGraphic::__EVENT_QUIT;
	      {
		this->_app.Close();
		exit(EXIT_SUCCESS);
	      }
	    case sf::Key::P:
	      {
		scene = ROOMLIST;
		break;
	      }
	    default:
	      break;
	    }
	}
    }
  return LibGraphic::EVENT_NONE;
}

LibGraphic::Event LibGraphic::GraphicClientState::getEventFromState(eStates & scene)
{
  switch (scene)
    {
    case START: return this->eventStart(scene);
    case ROOMLIST: return this->eventStart(scene);
    case GAMEPARAMETER: return this->eventStart(scene);
    case ROOM: return this->eventStart(scene);
    case OPTIONS: return this->eventStart(scene);
    case CREDITS: return this->eventStart(scene);
    case RANKING: return this->eventStart(scene);
    case INTRO: return this->eventStart(scene);
    case INGAME: return this->eventStart(scene);
    case UNKNOWN_STATE: return LibGraphic::EVENT_NONE;
    default: break;
    }
  return LibGraphic::EVENT_NONE;
}

inline sf::String * LibGraphic::GraphicClientState::getStdToSfString(std::string const & s, sf::Font * daFont)
{
  return (new sf::String(s, *daFont));
}
