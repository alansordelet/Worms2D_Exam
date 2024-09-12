#include "PlayerSelection.h"

bool reverseBool2(bool value)
{
	return !value;
}
PlayerSelection::PlayerSelection(Player* _player, Camera* _camera)
{
	camera = _camera;
	player = _player;	
}

PlayerSelection::PlayerSelection()
{

}

PlayerSelection::~PlayerSelection()
{

}

void PlayerSelection::UpdatePlayerSelection(sf::RenderWindow& _window)
{
	selectTimer += tools::GetTimeDelta();

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::M) && selectTimer > 0.1)
	{
		camera->setTurn(reverseBool2(camera->getTurn()));
		selectTimer = 0;
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::N) && selectTimer > 0.1 && camera->SelectingPlayer == true)
	{	 		
		if (player->getnextPlayer() < player->Players.size() - 1)
			player->addnextPlayer(1);
		else
			player->setnextPlayer(0);

		selectTimer = 0;
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter) && selectTimer > 0.1)
	{
		player->setSelectedbool(true);
		camera->SelectingPlayer = false;
		selectTimer = 0;
	}
	if (camera->getWC() == 0)
		player->weaponSelected = false;
	else
		player->weaponSelected = true;
	if (camera->getTurn() == false)
	{
		if (camera->SelectingPlayer == false)
		player->myTurn = true;
		if (player->Players.size() > 0)
		camera->setPosCamera(player->Players[player->getnextPlayer()]->GetObjectPos());
		camera->RandomisePlayer = false;
	}
	else if (camera->getTurn() == true)
	{
		player->weaponFired = false;
		player->myTurn = false;
	}
	if (camera->getTurn() == true)
		player->weaponFired = false;
}

void PlayerSelection::DrawPlayerSelection(sf::RenderWindow& _window)
{
	float accumulatedHealth = 0.0f;
	for (int i = 0; i < player->Players.size(); i++)
	{
		float enemyHealth = player->Players[i]->gethealth();
		accumulatedHealth += enemyHealth;
		
	}	
	Allplayerhealth.setSize(sf::Vector2f(accumulatedHealth, 15));
	Allplayerhealth.setFillColor(sf::Color::Blue);
	Allplayerhealth.setPosition(sf::Vector2f(850,220));
	_window.draw(Allplayerhealth);
}
