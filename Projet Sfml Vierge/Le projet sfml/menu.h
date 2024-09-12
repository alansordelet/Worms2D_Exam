#pragma once
#include "tools.h"
#include "StateManager.h"
#include"SoundManager.h"


enum WritingState
{
	EMPTY,
	//MENU_CHOOSE,
	//MENU_PRINCIPAL,
	//MENU_DELETING, //delete save file
	WRITING_IP,
	WRITING_PORT,
	WRITING_NAME
};

class Menu
{
public:
	Menu();
	Menu(StateManager* _sm);
	void init();
	void update(sf::RenderWindow& _window, sf::Event& _event);
	void setFullscreen(sf::RenderWindow& _window);
	void setVsynch(sf::RenderWindow& _window);
	float soundAlgo(sf::Vector2f _x);
	void setSoundVolume(sf::RenderWindow& _window, sf::Event& _event);
	void updateOptions(sf::RenderWindow& _window, sf::Event& _event);
	void updateLobbyHost(sf::RenderWindow& _window);
	void updateLobbyClient(sf::RenderWindow& _window);
	void EventMenu(sf::Event& _event);
	void display(sf::RenderWindow& _window);
	void drawVolume(sf::RenderWindow& _window);
	void displayOptions(sf::RenderWindow& _window);
	void destroy();
	
	bool getHostConnectedStatus() { return hostConnected; };
	void setHostConnectedStatus(bool _value) { hostConnected = _value; };

	bool getClientConnectedStatus() { return clientConnected; };
	void setClientConnectedStatus(bool _value) { clientConnected = _value; };
	sf::Text getText() { return playerPortInputT; }
	std::string getString() { return playerInputS; }
	bool playMusic = false;
	bool Joiner;
	bool Hoster;
	SoundManager sounds;
protected:
	float menuTimer;
private:
	StateManager* sm;
	sf::View viewmenu;
	sf::RectangleShape menuToGameRs;

	sf::RectangleShape menuToOptionsRs;
	sf::RectangleShape rs3;
	sf::RectangleShape rs4;

	sf::RectangleShape volumeBar;
	sf::CircleShape volumeButton;

	sf::Texture menuTexture;
	sf::Texture menuTexture2;

	sf::Vector2f menuPosition;

	sf::Text t;
	sf::Text tJouer;
	sf::Text tOption;
	sf::Font f;
	sf::Text text;
	sf::Font font;
	sf::Text text2;
	//Pour rentrer l'IP et le Port
	bool inEmptyMenu; //dans le menu de base
	bool choosingGame; //choix entre host et join
	bool hostingGame;//apres avoir choisi host
	bool joiningGame;//apres avoir choisi join
	bool optionactive = false;
	sf::RectangleShape cursorRS;
	bool showCursor;
			
	std::string playerInputS;
	sf::Text playerInputT;

	std::string playerPortInputS;
	sf::Text playerPortInputT;

	std::string playerUsernameInputS;
	sf::Text  playerUsernameInputT;

	bool fullscreen;
	bool vsynch;
	bool WritingGameIP;

	bool isDragging;

	//POUR LE LOBBY

	bool hostConnected;
	bool clientConnected;
};
