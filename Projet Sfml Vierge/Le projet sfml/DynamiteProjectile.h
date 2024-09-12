#pragma once
#include"Projectile.h"
class DynamiteProjectile : public Projectile
{
public:
	DynamiteProjectile(sf::Vector2f _pos) {
		projectile.setSize(sf::Vector2f(30, 30));
		projectile.setFillColor(sf::Color::Magenta);
		currentPos = _pos;
		posProjectile = _pos;
		projectile.setPosition(posProjectile);
	};
	~DynamiteProjectile() {};


	void Update(sf::RenderWindow& _window, Terrain* terrain, Player* player) {
		projectile.setPosition(currentPos);
		explosiontimer += tools::GetTimeDelta();
	};
	void Events(sf::Event _event) {

	};
	void Display(sf::RenderWindow& _window, Terrain* terrain, Player* player) {
		sf::FloatRect projectileBounds = projectile.getGlobalBounds();
		if (explosiontimer > 3) {
			// Calculate the radius of the explosion based on the distance from the center of the explosion
			float maxRadius = 100;
			float radius = 0;
			float distX = 0;
			float distY = 0;
			// Loop over all pixels and check if they're within the explosion radius
			for (int x = 0; x < 1200; x++) {
				for (int y = 0; y < 799; y++) {
					int index = (x + y * 1200) * 4;

					// Check if the pixel is green and within the explosion radius
					if (terrain->pixels[index] == 0 && terrain->pixels[index + 1] == 255 && terrain->pixels[index + 2] == 0) {
						distX = posProjectile.x - x;
						distY = posProjectile.y - y;
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
										player->Players[i]->addhealth(-0.1);
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

			// Update the texture and sprite to display the new pixel values
			terrain->texture.update(terrain->pixels);
			terrain->terrainS.setTexture(terrain->texture);

			setDelProjectile(true);
			explosiontimer = 0;
		}

		_window.draw(projectile);
	};
	bool exploded = false;
private:
	sf::Vector2f startingPos = { 100, 500 };
	// Initial angle and power of the projectile
	float angle = 45.0f;
	float power = 50.0f;
	float explosiontimer = 0.0f;
	sf::Vector2f currentPos;
	// Velocity of the projectile
	sf::Vector2f velocity = { 0, 0 };
	bool thisone = false;
};