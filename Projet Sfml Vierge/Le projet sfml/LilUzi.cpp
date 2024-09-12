#include "LilUzi.h"

LilUzi::LilUzi(sf::Vector2f _pos, Projectile* _missiles, Player* _player, Terrain* _terrain, Camera* _camera)
{
	Missiles = _missiles;
	player = _player;
	camera = _camera;
	weapon.setSize(sf::Vector2f(15, 30));
	weapon.setFillColor(sf::Color::Black);
	terrain = _terrain;

}

void LilUzi::Update(sf::RenderWindow& _window)
{
	timerUzi += tools::GetTimeDelta();

	if (timerUzi > 0.08 && isFiring == true)
	{
		nbofShoot += 1;
		Uzibullets.push_back(new UziProjectile(sf::Vector2f(tools::iRand(weapon.getPosition().x - 5, weapon.getPosition().x + 5), tools::iRand(weapon.getPosition().y+10, weapon.getPosition().y + 20) - (weapon.getGlobalBounds().height / 2)), angle));
		timerUzi = 0;
	}
	if (nbofShoot > 15)
	{
		isFiring = false;
		nbofShoot = 0;
	}

	float length = 30.f;
	float height = 20.0f;
	if (player->Players.size() > 0)
	{
		sf::Vector2f rectPos = player->Players[player->getnextPlayer()]->GetObjectPos() - sf::Vector2f(height * std::sin(angle * M_PI / 180.0f), height * std::cos(angle * M_PI / 180.0f));
		weapon.setPosition(rectPos);
	}
	
	weapon.setRotation(90.0f - angle);
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
}

void LilUzi::Display(sf::RenderWindow& _window)
{

	if (player->getSelectedbool() == true && camera->getWC() == 3 && camera->getTurn() == false && camera->SelectingPlayer == false)
	{
		_window.draw(weapon);
	}

	std::vector<Projectile*>::iterator it = Uzibullets.begin();
	while (it != Uzibullets.end()) {
		if ((*it)->getDelProjectile() == true) {
			delete* it;
			it = Uzibullets.erase(it);
			camera->setpassTurn(true);
		}
		else {
			++it;
		}
	}

	for (Projectile* dMissiles : Uzibullets)
	{
		dMissiles->Update(_window, terrain, player);
		dMissiles->Display(_window, terrain, player);
	}
}
