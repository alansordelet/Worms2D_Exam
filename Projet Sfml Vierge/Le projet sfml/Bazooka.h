#pragma once
#include"Weapons.h"
#include"BazookaProjectile.h"
#include"SoundManager.h"


class Bazooka : public Weapons
{
public:
	Bazooka(sf::Vector2f _pos, Projectile* _missiles, Player* _player, Terrain* _terrain, Camera* _camera);
	Bazooka() {};
	~Bazooka() {};

	void Update(sf::RenderWindow& _window);
	void Events(sf::Event _event)
	{
		if (_event.type == sf::Event::KeyReleased && _event.key.code == sf::Keyboard::Space)
		{
			if (player->getSelectedbool() == true && camera->getWC() == 1 && camera->getTurn() == false && camera->SelectingPlayer == false && player->weaponFired == false)
			{
				bazookaMissiles.push_back(new BazookaProjectile(sf::Vector2f(tools::iRand(weapon.getPosition().x - 5, weapon.getPosition().x + 5), tools::iRand(weapon.getPosition().y + 10, weapon.getPosition().y + 20) - (weapon.getGlobalBounds().height / 2)), angle, power));
				sounds.playSoundQuick("bazooka");
				player->weaponFired = true;
			}
			
			power = 0;
			thisweapon = false;
		}
	};
	void Display(sf::RenderWindow& _window);
	inline sf::RectangleShape getProjectile() {
		for (size_t i = 0; i < bazookaMissiles.size(); i++)
		{
			return bazookaMissiles[i]->getProjectile();
		}
	}
private:
	sf::Vector2f PosBazooka;
	sf::RectangleShape powerLevel;
	bool isFiring = false;
	bool thisweapon = false;
	Camera* camera;
	bool playsound = false;
	SoundManager sounds;
};



