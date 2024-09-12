#include "Player.h"

Player::Player(Terrain* _terrain)
{
	terrain = _terrain;
	player.setSize(sf::Vector2f(25, 25));
	player.setPosition(tools::frand(100, 600), tools::frand(100, 522));
	player.setFillColor(sf::Color::Red);
	nextP = 0;
	playerSelected = false;

	for (int i = 0; i < 4; i++)
	{
		Players.push_back(new Player(sf::Vector2f(tools::frand(100, 1000), tools::frand(100, 522)), health));
	}
	for (int i = 0; i < Players.size(); i++)
	{
		Players[i]->player.setPosition(tools::frand(100, 600), tools::frand(100, 522));
		Players[i]->player.setFillColor(sf::Color::Blue);

	}
}

Player::~Player()
{

}

void Player::Update(sf::RenderWindow& _window)
{
	newtimer += tools::GetTimeDelta();

	for (int i = 0; i < Players.size(); i++)
	{
		std::vector<Player*>::iterator it = Players.begin();
		while (it != Players.end()) {
			if ((*it)->health < 0) {
				delete* it;
				it = Players.erase(it);
			}
			else {
				++it;
			}
		}

		Players[i]->player.setOutlineColor(sf::Color::Blue);
		Players[nextP]->player.setOutlineColor(sf::Color::White);
		Players[nextP]->player.setOutlineThickness(1.5);
		Players[i]->playerAcceleration.x = 0.0f;
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Q))
		{
			if (playerSelected == true)
			{
				if (myTurn == true)
				{
					if (Players[nextP]->playerVelocity.x > -50.f)
						Players[nextP]->playerAcceleration.x -= 75.f;;
				}
			}
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
		{
			if (playerSelected == true)
			{
				if (myTurn == true)
				{
					if (Players[nextP]->playerVelocity.x < 50.f)
						Players[nextP]->playerAcceleration.x += 75.f;
				}
			}
		}
		else
		{
			if ((Players[i]->playerVelocity.y == 0.0000))
			{
				Players[i]->playerVelocity.x = 0;
			}
		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space) && Players[nextP]->playerVelocity.y == 0)
		{
			if (playerSelected && myTurn && !isJumping && !weaponSelected)
			{				
				Players[nextP]->playerVelocity.y = -50.f;
				isJumping = true; 
			}
		}

		Players[i]->playerVelocity += Players[i]->playerAcceleration * tools::GetTimeDelta(); 
		Players[i]->playerVelocity.y += Players[i]->GRAVITY * tools::GetTimeDelta();

		Players[i]->ObjectPos += Players[i]->playerVelocity * tools::GetTimeDelta();
		sf::Vector2f nextPosition = Players[i]->ObjectPos + Players[i]->playerVelocity * tools::GetTimeDelta();

		float topOfGreenPixels = terrain->getTopOfGreenPixels(nextPosition.x + 5, nextPosition.y + 5);
		if ((nextPosition.y + 25 > topOfGreenPixels))
		{
			float interpolationFactor = 0.01f;
			Players[i]->ObjectPos.y = Players[i]->ObjectPos.y + (topOfGreenPixels - (Players[i]->ObjectPos.y + 25)) * interpolationFactor;
			Players[i]->playerVelocity.y = 0.0000000;
			isJumping = false;
		}
		else
		{
			Players[i]->ObjectPos = nextPosition;
		}
		Players[i]->player.setPosition(Players[i]->ObjectPos);

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::E) && newtimer > 0.1)
		{
			Players[nextP]->health -= 1;
			newtimer = 0;
		}
		healthbar.setSize(sf::Vector2f(Players[i]->health, 15));
		Players[i]->healthbar.setPosition(sf::Vector2f(Players[i]->GetObjectPos().x - 12, Players[i]->GetObjectPos().y - 20));


		if (Players[i]->ObjectPos.x < 0.0f || Players[i]->ObjectPos.x > SCREEN_WIDTH ||
			Players[i]->ObjectPos.y < 0.0f || Players[i]->ObjectPos.y > SCREEN_HEIGHT - 25)
		{
			Players[i]->health += -1;
		}

		
	}
}

void Player::Display(sf::RenderWindow& _window)
{
	//_window.draw(player);
	for (int i = 0; i < Players.size(); i++)
	{		
		_window.draw(Players[i]->player);
		_window.draw(Players[i]->healthbar);
	}
}
