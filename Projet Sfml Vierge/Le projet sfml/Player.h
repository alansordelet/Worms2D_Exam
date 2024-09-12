#pragma once
#include"Objects.h"
class Player : public Objects
{
public :
	Player();
	Player(Terrain* _terrain);
	Player(sf::Vector2f _pos, int _health) {
		gothit = false;
		health = _health;
		player.setSize(sf::Vector2f(25, 25));
		player.setPosition(_pos);
		player.setFillColor(sf::Color::Blue);
		ObjectPos.x = tools::frand(100, 1000), tools::frand(100, 522);
		healthbar.setFillColor(sf::Color::Yellow);
		healthbar.setSize(sf::Vector2f(health, 15));		
	};
	~Player();

    

	void getHit(sf::Vector2f _posExplosion, sf::Vector2f _posPlayer, float _AddX, float _AddY) {
		if (_posExplosion.x < _posPlayer.x)
		{
			playerVelocity.x += _AddX;
		}
		else
		{
			playerVelocity.x -= _AddX;
		}
		playerVelocity.y -= _AddY;
	}

	void Events(sf::Event _event) {};
	void Update(sf::RenderWindow& _window);
	void Display(sf::RenderWindow& _window);
	sf::Vector2f GetObjectPos() { return ObjectPos; }
	void SetObjectPos(sf::Vector2f _newpos) {  ObjectPos = _newpos; }
	inline int getnextPlayer() { return nextP; }
	inline void addnextPlayer(int _newPlayer) { nextP = _newPlayer + nextP; }
	inline void setnextPlayer(int _newPlayer) { nextP = _newPlayer; }
	inline void setSelectedbool(bool _new) { playerSelected = _new; }
	inline void setHitbool(bool _new) { gethit = _new; }
	inline bool getHitbool( ) { return gethit; }
	inline bool getSelectedbool( ) { return playerSelected; }
	inline sf::Vector2f getPVelocity( ) { return playerVelocity; }
	inline int getnextP( ) { return nextP; }
	float gethealth() { return health; }
	sf::RectangleShape gethealthbar() { return healthbar; }
	void sethealthbar(sf::RectangleShape _r) { healthbar = _r; }
	void addhealth(float _newhealth) { health = health + _newhealth; }
	std::vector<Player*> Players;
	bool myTurn = false;
	bool gothit = false;
	bool weaponSelected = false;
	bool weaponFired = false;
private :
	sf::RectangleShape player;
	float totalTime = 0.0f;
	//sf::Vector2f playerPosition; // Player's position
	sf::Vector2f playerVelocity; // Player's velocity
	sf::Vector2f playerAcceleration; // Player's acceleration
	const float GRAVITY = 90.8f; // Gravity constant
	int nextP = 0;
	bool playerSelected = false;
	bool gethit = false;
	float newtimer = 0;
	bool isJumping = false;

};

