#pragma once
#include"tools.h"
#include"Camera.h"
#include"Player.h"

class PlayerSelection
{
public :
	PlayerSelection(Player* _player, Camera* _camera);
	PlayerSelection();
	~PlayerSelection();

	void UpdatePlayerSelection(sf::RenderWindow& _window);
	void DrawPlayerSelection(sf::RenderWindow& _window);
private:
	Camera* camera;
	Player* player;
	sf::RectangleShape Allplayerhealth;
	float selectTimer = 0;
};

