#include"tools.h"
#include"terrain.h"
#include"Camera.h"
#include"Bazooka.h"
#include"Dynamite.h"
#include"LilUzi.h"
#include"Grenade.h"
#include"Player.h"

typedef enum StateAI
{
	CHECKING_POS,
	MOVING,
	FIRING
};


class Enemy
{
public: 
	Enemy(Terrain* _terrain, Bazooka* _weaponProjectiles, Dynamite* _weaponProjectiles2, LilUzi* _weaponProjectiles3, Grenade* _weaponProjectiles4, Player* _player, Camera* _camera);
	~Enemy();
	Enemy(sf::Vector2f _pos, int _health) {
		thisone = false;
		enemyhealth = _health;
		Enemies.setSize(sf::Vector2f(25, 25));
		Enemies.setPosition(_pos);
		Enemies.setFillColor(sf::Color::Red);
		ObjectPos.x = tools::frand(100, 1000), tools::frand(100, 522);
		healthbar.setFillColor(sf::Color::Yellow);
		healthbar.setSize(sf::Vector2f(enemyhealth, 15));
	};

	void getHit(sf::Vector2f _posExplosion, sf::Vector2f _posPlayer, float _AddX, float _AddY) {
		if (_posExplosion.x < _posPlayer.x)
		{
			EnemyVelocity.x += _AddX;
		}
		else
		{
			EnemyVelocity.x -= _AddX;
		}
		EnemyVelocity.y -= _AddY;
	}
	bool isProjectilePushedBack = false;
	inline bool checkCollision(const sf::Uint8* pixels, const sf::FloatRect& rect)
	{
		// Loop over all pixels within the player's rectangle and check if they're green
		for (int x = rect.left; x < rect.left + rect.width; x++) {
			for (int y = rect.top; y < rect.top + rect.height; y++) {
				if (x >= 0 && x < SCREEN_WIDTH && y >= 0 && y < SCREEN_HEIGHT)// so the game doesnt crash when collison out of screen
				{
					int index = (x + y * 1200) * 4;
					if (pixels[index] == 0 && pixels[index + 1] == 255 && pixels[index + 2] == 0) {
						return true; // Collision detected
					}
				}
			}
		}
		return false; // No collision detected
	}

	bool isPositionInRadius(sf::Vector2f position, sf::Vector2f center, float radius)
	{
		float distance = std::sqrt(std::pow(position.x - center.x, 2) + std::pow(position.y - center.y, 2));
		if (distance <= radius)
		{
			return true;
		}
		else
		{
			return false;
		}
	}



	bool isRectInRadius(sf::FloatRect rect, sf::FloatRect center, float radius)
	{
		sf::Vector2f rectCenter(rect.left + rect.width / 2.0f, rect.top + rect.height / 2.0f);
		sf::Vector2f centerCenter(center.left + center.width / 2.0f, center.top + center.height / 2.0f);
		float distance = std::sqrt(std::pow(rectCenter.x - centerCenter.x, 2) + std::pow(rectCenter.y - centerCenter.y, 2));
		return (distance <= radius);
	}

	void Events(sf::Event _event) {};
	void Update(sf::RenderWindow& _window);
	void Display(sf::RenderWindow& _window);
	void DisplayAllhealth(sf::RenderWindow& _window);
	virtual sf::Vector2f GetObjectPos() { return ObjectPos; }
	virtual void SetObjectPos(sf::Vector2f _newpos) { ObjectPos = _newpos; }
	virtual sf::RectangleShape getEnemyhealthbar() { return healthbar; }
	float getEnemyhealth() { return enemyhealth; }
	void addEnemyhealth(float _newhealth) { enemyhealth = enemyhealth + _newhealth; }
	std::vector<Enemy*> AllEnemies;	
	sf::Clock explosionTimer; // Initialize and start the timer when the explosion starts

	// Check if the timer has elapsed or reached its end time
	
private:
	sf::RectangleShape Enemies;
	sf::Vector2f EnemyVelocity;
	sf::Vector2f ObjectPos;
	Terrain* terrain;
	Bazooka* eBazookaProjectiles;
	Dynamite* eDynamiteProjectiles;
	LilUzi* eUziProjectiles;
	Grenade* eGrenadeProjectiles;
	Player* player;
	bool thisone = false;
	sf::VertexArray line;
	StateAI aistate;
	Camera* camera;	
	sf::RectangleShape healthbar;
	int enemyhealth = 50;
	sf::RectangleShape Allenemyhealth;
};

