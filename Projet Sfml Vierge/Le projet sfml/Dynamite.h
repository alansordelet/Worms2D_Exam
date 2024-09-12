#pragma once
#include"Weapons.h"
#include"DynamiteProjectile.h"
class Dynamite : public Weapons
{
public:
	Dynamite(sf::Vector2f _pos, Projectile* _missiles, Player* _player, Terrain* _terrain, Camera* _camera);
	Dynamite() {};
	~Dynamite() {};

	void Update(sf::RenderWindow& _window);
	void Events(sf::Event _event)
	{
		if (_event.type == sf::Event::KeyReleased && _event.key.code == sf::Keyboard::Space)
		{
			if (player->getSelectedbool() == true && camera->getWC() == 2 && camera->getTurn() == false && camera->SelectingPlayer == false && player->weaponFired == false)
			{
				dynamite.push_back(new DynamiteProjectile(sf::Vector2f(player->Players[player->getnextPlayer()]->GetObjectPos().x /*- (weapon.getGlobalBounds().width / 2)*/, player->Players[player->getnextPlayer()]->GetObjectPos().y /*- (weapon.getGlobalBounds().height / 2)*/)));
				player->weaponFired = true;
			}
			
		}
	};
	void Display(sf::RenderWindow& _window);

private:
	sf::Vector2f PosBazooka;
	sf::RectangleShape powerLevel;
	bool isFiring = false;
	bool placed = false;
	float dynamitetimer;
	Camera* camera;
};

