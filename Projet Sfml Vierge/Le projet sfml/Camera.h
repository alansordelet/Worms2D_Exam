#pragma once
#include"tools.h"
#include"Weapons.h"
#include"StateManager.h"
#include"SoundManager.h"
class Camera
{
public:
	Camera();
	~Camera();
	void initsoundgame()
	{
		if (playmusic == false)
		{
			sounds.loadSound("GameMusic", "GameMusic.wav");
			sounds.playSoundQuick("GameMusic");
			sounds.setSoundLoop("GameMusic", true);
			playmusic = true;
		}
		
	}
	inline void initCamera(StateManager* _sm)
	{
		sm = _sm;
		uzitexture.loadFromFile("..\\Ressources\\uzi.png");
		grenadetexture.loadFromFile("..\\Ressources\\grenade.png");
		bazookatexture.loadFromFile("..\\Ressources\\bazooka.png");
		dynamitetexture.loadFromFile("..\\Ressources\\dynamite.png");

		uzisprite.setTexture(uzitexture);
		grenadesprite.setTexture(grenadetexture);
		dynamitesprite.setTexture(dynamitetexture);
		bazookasprite.setTexture(bazookatexture);

		dynamitesprite.setScale(sf::Vector2f(0.08,0.08));
		uzisprite.setScale(sf::Vector2f(0.13,0.13));
		bazookasprite.setScale(sf::Vector2f(0.03,0.03));
		grenadesprite.setScale(sf::Vector2f(0.03,0.03));
		ViewHUD.setSize(SCREEN_WIDTH, SCREEN_HEIGHT);
		ViewGame.setSize(600, 400);

		weaponBar.setSize(sf::Vector2f(200.f, 900.f));
		weaponBar.setFillColor(sf::Color::Black);
		weaponBar.setPosition(1200, 0);	

		for (int i = 0; i < 5; i++) {
			sf::RectangleShape rect(sf::Vector2f(50, 50));
			rect.setFillColor(sf::Color::White);
			weapons.push_back(rect); 
		}
		font.loadFromFile("..\\Ressources\\Basic.ttf");
		text.setString("Enter to Select // Press N to Switch");
		text.setFont(font);
		text.setCharacterSize(34); 
		text.setFillColor(sf::Color::White);

		textTimer.setString("Timer : " + stringtime);
		textTimer.setFont(font);
		textTimer.setCharacterSize(34);
		textTimer.setFillColor(sf::Color::Black);
		
	}
	bool playmusic = false;
	void UpdateCamera();
	void DisplayCameraGame(sf::RenderWindow& _window);
	void DisplayCameraMinimap(sf::RenderWindow& _window);
	void DisplayCameraHUD(sf::RenderWindow& _window);
	inline void setPosCamera(sf::Vector2f _NewPosC) { posCameraGame = _NewPosC; }
	inline inline sf::Vector2f getPosCamera() { return posCameraGame; }
	int getWC() { return weaponChoice; }
	void addorReduceWC(int _add) { weaponChoice = weaponChoice + _add; }
	void setWC(int _set) { weaponChoice = _set; }

	inline bool getTurn() { return nextTurn; }
	inline void setTurn(bool _new) { nextTurn = _new; }

	inline bool getpassTurn() { return passTurn; }
	inline void setpassTurn(bool _new) { passTurn = _new; }

	inline int getnextEnemy() { return nextE; }
	inline void addnextEnemy(int _newPlayer) { nextE = _newPlayer + nextE; }
	inline void setnextEnemy(int _newPlayer) { nextE = _newPlayer; }
	
	SoundManager sounds;
	sf::View ViewGame;
	sf::View ViewMinimap;
	sf::View ViewHUD;
	bool SelectingPlayer = true;
	bool RandomisePlayer = false;
	
private:
	float newtimer;
	sf::RectangleShape rs_view;
	sf::Vector2f posCameraGame;
	sf::RectangleShape weaponBar;
	std::vector<RectangleShape> weapons;
	sf::Vector2f targetPosition = { 1200, 0 };
	int weaponChoice = 0;
	bool Selecting = false;
	bool nextTurn = false;
	bool passTurn = false;
	sf::Text text;
	sf::Text textTimer;
	sf::Font font;
	float initialY = 300.0f;
	float amplitude = 30.0f;
	float frequency = 0.2f;
	float time = 0.0f;
	float timerforPlayer = 0.0f;
	std::string stringtime;
	float timerlooking = 0;
	int nextE = 0;
	StateManager* sm;
	sf::Sprite dynamitesprite;
	sf::Sprite grenadesprite;
	sf::Sprite uzisprite;
	sf::Sprite bazookasprite;
	sf::Texture dynamitetexture;
	sf::Texture bazookatexture;
	sf::Texture grenadetexture;
	sf::Texture uzitexture;
};

