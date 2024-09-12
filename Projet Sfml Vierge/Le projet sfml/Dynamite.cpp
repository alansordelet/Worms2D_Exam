#include "Dynamite.h"

Dynamite::Dynamite(sf::Vector2f _pos, Projectile* _missiles, Player* _player, Terrain* _terrain, Camera* _camera)
{
	Missiles = _missiles;
	player = _player;
	camera = _camera;
	weapon.setSize(sf::Vector2f(20, 20));
	weapon.setFillColor(sf::Color::Black);
	terrain = _terrain;
}

void Dynamite::Update(sf::RenderWindow& _window)
{
	if (player->Players.size() > 0)
	weapon.setPosition(player->Players[player->getnextP()]->GetObjectPos());
}

void Dynamite::Display(sf::RenderWindow& _window)
{
	if (player->getSelectedbool() == true && camera->getWC() == 2)
	{
		_window.draw(powerLevel);
		_window.draw(weapon);
	}

	std::vector<Projectile*>::iterator it = dynamite.begin();
	while (it != dynamite.end()) {
		if ((*it)->getDelProjectile() == true) {
			delete* it;
			it = dynamite.erase(it);
			camera->setpassTurn(true);
		}
		else {
			++it;
		}
	}

	for (Projectile* dMissiles : dynamite)
	{
		dMissiles->Update(_window, terrain, player);
		dMissiles->Display(_window, terrain, player);
	}
}
