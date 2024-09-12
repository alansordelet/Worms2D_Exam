#pragma once
#include"Weapons.h"
#include"UziProjectile.h"
class LilUzi : public Weapons
{
public:
	LilUzi(sf::Vector2f _pos, Projectile* _missiles, Player* _player, Terrain* _terrain, Camera* _camera);
	LilUzi() {};
	~LilUzi() {};

	void Update(sf::RenderWindow& _window);
	void Events(sf::Event _event)
	{
		if (_event.type == sf::Event::KeyReleased && _event.key.code == sf::Keyboard::Space)
		{
			if (player->getSelectedbool() == true && camera->getWC() == 3 && camera->getTurn() == false && camera->SelectingPlayer == false && player->weaponFired == false)
			{
				isFiring = true;
				player->weaponFired = true;
			}

			power = 0;
			thisweapon = false;
		}
	};
	void Display(sf::RenderWindow& _window);

private:
	sf::Vector2f PosBazooka;
	sf::RectangleShape powerLevel;
	bool isFiring = false;
	bool thisweapon = false;
	Camera* camera;
	float timerUzi = 0;
	int nbofShoot = 0;
};

