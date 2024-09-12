#pragma once
#include"Weapons.h"
#include"GrenadeProjectile.h"
class Grenade : public Weapons
{
public:
	Grenade(sf::Vector2f _pos, Projectile* _missiles, Player* _player, Terrain* _terrain, Camera* _camera);
	Grenade() {};
	~Grenade() {};

	void Update(sf::RenderWindow& _window);
	void Events(sf::Event _event)
	{
		if (_event.type == sf::Event::KeyReleased && _event.key.code == sf::Keyboard::Space)
		{
			if (player->getSelectedbool() == true && camera->getWC() == 4 && camera->getTurn() == false && camera->SelectingPlayer == false && player->weaponFired == false)
			{
				grenades.push_back(new GrenadeProjectile(sf::Vector2f(player->Players[player->getnextPlayer()]->GetObjectPos().x - (weapon.getGlobalBounds().width / 2), player->Players[player->getnextPlayer()]->GetObjectPos().y - (weapon.getGlobalBounds().height / 2)), angle, power));
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
};

