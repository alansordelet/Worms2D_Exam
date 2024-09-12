#pragma once
#include"tools.h"
#include"Terrain.h"
#include"Objects.h"
#include"Player.h"
#include"Enemy.h"
#include"Bazooka.h"
#include"Dynamite.h"
#include"LilUzi.h"
#include"Projectile.h"
#include"Camera.h"
#include"PlayerSelection.h"
#include"Grenade.h"
#include"StateManager.h"
class Game
{
public :
	Game() {};
	~Game() {};

	void initGame(StateManager* _sm);
	void GameEvents(sf::Event _event)
	{
		objectUzi->Events(_event); 
		objectGrenade->Events(_event);
		objectBazooka->Events(_event);
		objectDynamite->Events(_event);
	};
	void UpdateGame(sf::RenderWindow& _window);
	void DrawGame(sf::RenderWindow& _window);
	Terrain* terrain;
private :
	Camera camera;
	Player* objectPlayer;
	Enemy* objectEnemy;
	Projectile* objectProjectiles;
	Bazooka* objectBazooka;
	Dynamite* objectDynamite;
	LilUzi* objectUzi;
	Grenade* objectGrenade;
	Weapons* objectWeapons;
	PlayerSelection* selection;
};

