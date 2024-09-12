#pragma once
#include"Projectile.h"
class GrenadeProjectile : public Projectile
{
public:

	// Function to calculate the initial velocity of the projectile based on the angle and power level
	GrenadeProjectile(sf::Vector2f _pos, float _angle, float _power) {
		projectile.setSize(sf::Vector2f(10, 10));
		projectile.setFillColor(sf::Color::Blue);
		posProjectile = _pos;
		projectile.setPosition(posProjectile);
		angle = _angle;
		power = _power;
	};
	~GrenadeProjectile() {};

	void Update(sf::RenderWindow& _window, Terrain* terrain, Player* player)
	{
		sf::FloatRect projectileBounds = projectile.getGlobalBounds();
		if (checkCollision(terrain->pixels, projectileBounds)) {
			currentPos = currentPos;
			explodetimer += tools::GetTimeDelta();
		}
		else
		{
			currentPos = calculateVelocity(angle, power, posProjectile, t);
		}
		projectile.setPosition(currentPos);
		//sf::FloatRect projectileBounds = projectile.getGlobalBounds();
		if (checkCollision(terrain->pixels, projectileBounds))
			projectile.setFillColor(sf::Color::Yellow);
		else
			projectile.setFillColor(sf::Color::Red);
	};
	void Display(sf::RenderWindow& _window, Terrain* terrain, Player* player)
	{
		sf::FloatRect projectileBounds = projectile.getGlobalBounds();
		if (explodetimer > 2) {
			// Calculate the radius of the explosion based on the distance from the center of the explosion
			float maxRadius = 100;
			float radius = 50;
			float distX = 0;
			float distY = 0;
			// Loop over all pixels and check if they're within the explosion radius
			for (int x = 0; x < 1200; x++) {
				for (int y = 0; y < 799; y++) {
					int index = (x + y * 1200) * 4;
					if (terrain->pixels[index] == 0 && terrain->pixels[index + 1] == 255 && terrain->pixels[index + 2] == 0) {
						distX = currentPos.x - x;
						distY = currentPos.y - y;
						radius = std::sqrt(distX * distX + distY * distY);
						if (radius < maxRadius) {
							// Set the pixel to sky
							terrain->pixels[index] = 0;
							terrain->pixels[index + 1] = 255;
							terrain->pixels[index + 2] = 255;
							terrain->pixels[index + 3] = 255;
							for (size_t i = 0; i < player->Players.size(); i++)
							{
								if (isPositionInRadius(player->Players[i]->GetObjectPos(), currentPos, radius))
								{
									if (player->Players[i]->gothit == true)
									{
										player->Players[i]->addhealth(-0.25);
										player->Players[i]->getHit(currentPos, player->Players[i]->GetObjectPos(), (200 * tools::GetTimeDelta()), (200 * tools::GetTimeDelta()));
										player->Players[i]->healthbar.setSize(sf::Vector2f(player->Players[i]->health, 15));
										player->Players[i]->gothit = false;
									}
								}

							}
						}
						else
						{
							for (size_t i = 0; i < player->Players.size(); i++)
								player->Players[i]->gothit = true;
						}
					}
				}
			}
			terrain->texture.update(terrain->pixels);
			terrain->terrainS.setTexture(terrain->texture);
			explodetimer = 0;
			setDelProjectile(true);
		}
		_window.draw(projectile);
		t += time_step;
	};
	inline bool getDelProjectile() { return deleteProjectile; }
	inline void setDelProjectile(bool _new) { deleteProjectile = _new; }

private:
	sf::Vector2f startingPos = { 100, 500 };
	// Initial angle and power of the projectile
	float angle = 45.0f;
	float power = 50.0f;
	float t = 0.0f;
	float explodetimer = 0.0f;
	sf::Vector2f currentPos;
	// Velocity of the projectile
	sf::Vector2f velocity = { 0, 0 };
	bool thisone = false;
};