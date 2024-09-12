#include "Grenade.h"
Grenade::Grenade(sf::Vector2f _pos, Projectile* _missiles, Player* _player, Terrain* _terrain, Camera* _camera)
{
	Missiles = _missiles;
	player = _player;
	camera = _camera;
	powerLevel.setSize(sf::Vector2f(20, 0));
	weapon.setSize(sf::Vector2f(20, 20));
	powerLevel.setFillColor(sf::Color::Red);
	weapon.setFillColor(sf::Color::Black);
	terrain = _terrain;
}

void Grenade::Update(sf::RenderWindow& _window)
{
	float length = power / 100.0f * 100.0f;
	float height = 20.0f;
	sf::Vector2f rectPos;
	powerLevel.setSize(sf::Vector2f(length, height));
	if (player->Players.size() > 0)
	{
		rectPos = player->Players[player->getnextPlayer()]->GetObjectPos() - sf::Vector2f(height * std::sin(angle * M_PI / 180.0f), height * std::cos(angle * M_PI / 180.0f));

		powerLevel.setPosition(rectPos);
		weapon.setPosition(rectPos);
	}
	
	// Rotate the power level rectangle to match the angle
	powerLevel.setRotation(90.0f - angle);
	weapon.setRotation(90.0f - angle);
	sf::Vector2i mousepose = sf::Mouse::getPosition();
	sf::Vector2f curseurpos = sf::Vector2f((float)mousepose.x, (float)mousepose.y);
	shoottimer += tools::GetTimeDelta();
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) && camera->getTurn() == false && camera->SelectingPlayer == false)
	{
		if (player->getSelectedbool() == true && angle < 180)
			angle += 50.0f * tools::GetTimeDelta();
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down) && camera->getTurn() == false && camera->SelectingPlayer == false)
	{
		if (player->getSelectedbool() == true && angle > -180)
			angle -= 50.0f * tools::GetTimeDelta();
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
	{
		if (player->getSelectedbool() == true)
			power += 50.0f * tools::GetTimeDelta();
	}
}

void Grenade::Display(sf::RenderWindow& _window)
{
	if (player->getSelectedbool() == true && camera->getWC() == 4 && camera->getTurn() == false && camera->SelectingPlayer == false)
	{
		_window.draw(powerLevel);
		_window.draw(weapon);
	}

	std::vector<Projectile*>::iterator it = grenades.begin();
	while (it != grenades.end()) {
		if ((*it)->getDelProjectile() == true) {
			delete* it;
			it = grenades.erase(it);
			camera->setpassTurn(true);
		}
		else {
			++it;
		}
	}


	for (Projectile* bMissiles : grenades)
	{
		bMissiles->Update(_window, terrain, player);
		bMissiles->Display(_window, terrain, player);
	}
}