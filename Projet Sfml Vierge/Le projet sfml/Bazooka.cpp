#include "Bazooka.h"
Bazooka::Bazooka(sf::Vector2f _pos, Projectile* _missiles, Player* _player, Terrain* _terrain, Camera* _camera)
{
	sounds.loadSound("bazooka", "bazooka.wav");
	Missiles = _missiles;
	player = _player;
	camera = _camera;
	powerLevel.setSize(sf::Vector2f(20, 0));
	weapon.setSize(sf::Vector2f(20, 50));
	powerLevel.setFillColor(sf::Color::Red);
	weapon.setFillColor(sf::Color::Black);
	terrain = _terrain;
}

void Bazooka::Update(sf::RenderWindow& _window)
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
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
	{
		if (player->getSelectedbool() == true && angle < 180 && camera->getTurn() == false && camera->SelectingPlayer == false)
		angle += 50.0f * tools::GetTimeDelta();
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
	{
		if (player->getSelectedbool() == true && angle > -180 && camera->getTurn() == false && camera->SelectingPlayer == false)
		angle -= 50.0f * tools::GetTimeDelta();
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
	{
		if (player->getSelectedbool() == true)
		power += 50.0f * tools::GetTimeDelta();	
	}
	for (auto& n : bazookaMissiles)
	{
		
		//std::cout << n->calculateEndPositionWind(angle, power, PosBazooka, n->windSpeed, n->windDirection).x;
	}
}

void Bazooka::Display(sf::RenderWindow& _window)
{	
	if (player->getSelectedbool() == true && camera->getWC() == 1 && camera->getTurn() == false && camera->SelectingPlayer == false && player->weaponFired == false)
	{
		_window.draw(powerLevel);
		_window.draw(weapon);
	}
	
	std::vector<Projectile*>::iterator it = bazookaMissiles.begin();
	while (it != bazookaMissiles.end()) {
		if ((*it)->getDelProjectile() == true) {
			delete* it;
			it = bazookaMissiles.erase(it);
			camera->setpassTurn(true);
		}
		else {
			++it;
		}
	}
	

	for (Projectile* bMissiles : bazookaMissiles)
	{		
		bMissiles->Update(_window, terrain, player);
		bMissiles->Display(_window, terrain, player);
	}
}

