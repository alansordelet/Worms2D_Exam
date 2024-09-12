#pragma once
#include"tools.h"
#include"terrain.h"
#include"Player.h"
#include <cmath>
class Projectile
{
public:
	const float g = 9.81f; // gravitational acceleration
	const float max_velocity = 100; // max velocity
	const float max_angle = 180.f;   // max angle 
	const float min_angle = -180.f;    // min angle 
	const float time_step = 0.001f;   // time simulation // reduce for slow and increase for accelerated time 

	inline static sf::Vector2f FollowEnnemis(sf::Vector2f _PosSuivie, sf::Vector2f _PosSuiveur, int _vitess) {
		sf::Vector2f Vector{ _PosSuivie.x - _PosSuiveur.x,_PosSuivie.y - _PosSuiveur.y };
		float norm = sqrt(Vector.x * Vector.x + Vector.y * Vector.y);
		return sf::Vector2f(_vitess * (Vector.x / norm), _vitess * (Vector.y / norm));
	}
	inline bool checkCollision(const sf::Uint8* pixels, const sf::FloatRect& rect)
	{
		// loop over all pixels within the player's rectangle and check if they're green
		for (int x = rect.left; x < rect.left + rect.width; x++) {
			for (int y = rect.top; y < rect.top + rect.height; y++) {
				if (x >= 0 && x < SCREEN_WIDTH && y >= 0 && y < SCREEN_HEIGHT)// so the game doesnt crash when collison out of screen
				{
					int index = (x + y * 1200) * 4;
					if (pixels[index] == 0 && pixels[index + 1] == 255 && pixels[index + 2] == 0) { // if green
						return true; // collision detected
					}
				}
			}
		}
		return false; // no collision detected
	}

	sf::Vector2f calculateVelocityWind(float angle, float power, sf::Vector2f startingPos, float t, float windSpeed, float windDirection)
	{
		// Limit the angle to the valid range
		angle = std::fmax(std::fmin(angle, max_angle), min_angle);
		// Convert the angle to radians
		float radians = angle * M_PI / 180.0f;
		// Calculate the initial velocity of the projectile
		float v = power * max_velocity / 100.0f;
		float vx = v * std::cos(radians);
		float vy = -v * std::sin(radians);
		// Calculate the trajectory of the projectile at time t, taking into account wind speed and direction
		float x = startingPos.x + (vx + windSpeed * std::cos(windDirection)) * t;
		float y = startingPos.y + (vy + windSpeed * std::sin(windDirection)) * t + 0.5f * g * t * t;
		return sf::Vector2f(x, y);
	}


	sf::Vector2f calculateVelocity(float angle, float power, sf::Vector2f startingPos, float t /*float windSpeed, float windDirection*/)
	{
		// Limit the angle to the valid range
		angle = std::fmax(std::fmin(angle, max_angle), min_angle);
		// Convert the angle to radians
		float radians = angle * M_PI / 180.0f;
		// Calculate the initial velocity of the projectile
		float v = power * max_velocity / 100.0f;
		float vx = v * std::cos(radians);
		float vy = -v * std::sin(radians);
		// Calculate the trajectory of the projectile at time t, taking into account wind speed and direction
		float x = startingPos.x + (vx /*+ windSpeed *//** std::cos(windDirection)*/) * t;
		float y = startingPos.y + (vy /*+ windSpeed * std::sin(windDirection)*/)*t + 0.5f * g * t * t;
		return sf::Vector2f(x, y);
	}

	sf::Vector2f calculateEndPositionWind(float angle, float power, sf::Vector2f startingPos, float windSpeed, float windDirection)
	{
		// Calculate the time of flight for the projectile using the quadratic formula
		float a = 0.5f * g;
		float b = power * std::sin(angle * M_PI / 180.0f);
		float c = startingPos.y - 0.5f * g * startingPos.x * startingPos.x / (power * std::cos(angle * M_PI / 180.0f)) * (power * std::cos(angle * M_PI / 180.0f)) / (power * std::cos(angle * M_PI / 180.0f));
		float discriminant = b * b - 4 * a * c;
		float t1 = (-b + std::sqrt(discriminant)) / (2 * a);
		float t2 = (-b - std::sqrt(discriminant)) / (2 * a);

		// Choose the positive time value (t1 or t2) that corresponds to the time of flight
		float t = t1 >= 0 ? t1 : t2;

		// Calculate the end position of the trajectory at time t
		sf::Vector2f endPos = calculateVelocityWind(angle, power, startingPos, t, windSpeed, windDirection);

		return endPos;
	}

	sf::Vector2f calculateEndPosition(float angle, float power, sf::Vector2f startingPos)
	{
		// Calculate the time of flight for the projectile using the quadratic formula
		float a = 0.5f * g;
		float b = power * std::sin(angle * M_PI / 180.0f);
		float c = startingPos.y - 0.5f * g * startingPos.x * startingPos.x / (power * std::cos(angle * M_PI / 180.0f)) * (power * std::cos(angle * M_PI / 180.0f));
		float discriminant = b * b - 4 * a * c;
		float t1 = (-b + std::sqrt(discriminant)) / (2 * a);
		float t2 = (-b - std::sqrt(discriminant)) / (2 * a);

		// Choose the positive time value (t1 or t2) that corresponds to the time of flight
		float t = t1 >= 0 ? t1 : t2;

		// Calculate the end position of the trajectory at time t
		sf::Vector2f endPos = calculateVelocity(angle, power, startingPos, t);

		return endPos;
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
	Projectile(sf::Vector2f _pos) {
	};
	Projectile() {};
	~Projectile() {};

	void DisplayArrow(sf::RenderWindow& _window)
	{
		sf::ConvexShape arrowRed;
		arrowRed.setPointCount(3);
		arrowRed.setPoint(0, sf::Vector2f(0.0f, 0.0f));
		arrowRed.setPoint(1, sf::Vector2f(20.0f, -40.0f));
		arrowRed.setPoint(2, sf::Vector2f(-20.0f, -40.0f));
		arrowRed.setFillColor(sf::Color::Red);

		sf::ConvexShape arrowBlue;
		arrowBlue.setPointCount(3);
		arrowBlue.setPoint(0, sf::Vector2f(0.0f, 0.0f));
		arrowBlue.setPoint(1, sf::Vector2f(10.0f, -20.0f));
		arrowBlue.setPoint(2, sf::Vector2f(-10.0f, -20.0f));
		arrowBlue.setFillColor(sf::Color::Blue);

		// Set the arrow's position and rotation based on the wind direction
		arrowRed.setPosition(1000.0f, 165.0f);
		arrowBlue.setPosition(1000.0f, 165.0f);
		arrowRed.setRotation(windDirection * 180.0f / M_PI);
		arrowBlue.setRotation(windDirection * 180.0f / M_PI);
		_window.draw(arrowRed);
		_window.draw(arrowBlue);
	};

	virtual void Update(sf::RenderWindow& _window, Terrain* terrain, Player* player)
	{
	};
	virtual void Display(sf::RenderWindow& _window, Terrain* terrain, Player* player)
	{
		
	};
	inline bool getDelProjectile() { return deleteProjectile; }
	inline void setDelProjectile(bool _new) { deleteProjectile = _new; }

	virtual inline sf::RectangleShape getProjectile() { return projectile; }
	//inline void setDelProjectile(bool _new) { deleteProjectile = _new; }
	bool isActive = false;
    virtual sf::Vector2f getPreviousPosition() const { return m_previousPosition; }
	float windSpeed = 10.0f;
	float windDirection = M_PI * 2.5;
	// Setter for previous position
	virtual void setPreviousPosition(sf::Vector2f previousPosition) { m_previousPosition = previousPosition; }
protected:
	sf::Vector2f posProjectile;
	sf::RectangleShape projectile;
	sf::Vector2f speed;
	sf::Vector2f angle = { 150,150 };
	bool deleteProjectile;
	bool exploded;
	sf::ConvexShape arrow;
	sf::Vector2f m_previousPosition;
};
