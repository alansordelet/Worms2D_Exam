#pragma once
#include"Terrain.h"
#include"tools.h"
class Objects
{
public :
	Objects(Terrain* _terrain);
	Objects() {};
	~Objects();
	inline bool checkCollision2(const sf::Uint8* pixels, const sf::FloatRect& rect)
	{
		// Check if the player is within the screen
		if (std::round(rect.left) >= 1200 || std::round(rect.left + rect.width) < 0 ||
			std::round(rect.top) >= 800 || std::round(rect.top + rect.height) < 0)
			return false;

		// Loop over all pixels within the player's rectangle and check if they're green
		for (int x = std::max(std::floor(rect.left), 0.f); x < std::min(std::round(rect.left + rect.width), 1200.f); x++) {
			for (int y = std::max(std::floor(rect.top), 0.f); y < std::min(std::round(rect.top + rect.height), 800.f); y++) {
				int index = (x + y * 1200) * 4;
				if (pixels[index] == 0 && pixels[index + 1] == 255 && pixels[index + 2] == 0) {
					return true; // collision detected
				}
			}
		}
		return false; // no collision detected
	}

	inline bool checkCollision(const sf::Uint8* pixels, const sf::FloatRect& rect)
	{	
		for (int x = rect.left; x < rect.left + rect.width; x++) {
			for (int y = rect.top; y < rect.top + rect.height; y++) {
				if (x >= 0 && x < SCREEN_WIDTH && y >= 0 && y < SCREEN_HEIGHT)// so the game doesnt crash when collison out of screen
				{
					int index = (x + y * 1200) * 4;
					if (pixels[index] == 0 && pixels[index + 1] == 255 && pixels[index + 2] == 0) {
						return true; 
					}
				}
			}
		}
		return false; 
	}

	virtual void Events(sf::Event _event) = 0;
	virtual void Display(sf::RenderWindow& _window) = 0;
	virtual void Update(sf::RenderWindow& _window) = 0;
	virtual sf::Vector2f GetObjectPos() { return ObjectPos; }
	virtual void SetObjectPos(sf::Vector2f _newpos) { ObjectPos = _newpos; }
	virtual float gethealth() { return health; }
	virtual sf::RectangleShape gethealthbar() { return healthbar; }
	sf::RectangleShape healthbar;
	virtual void addhealth(float _newhealth) { health = health + _newhealth; }
	float health = 50;
protected :
	Terrain* terrain;
	std::vector<sf::RectangleShape> healthbars;
	
	
	sf::Vector2f ObjectPos = {0.0f, 0.0f};
};

