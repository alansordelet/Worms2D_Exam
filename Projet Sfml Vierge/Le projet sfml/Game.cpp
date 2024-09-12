#include "Game.h"

void Game::initGame(StateManager* _sm)
{
	camera.initCamera(_sm);
	
	terrain = new Terrain();
	objectPlayer = new Player(terrain);	
	objectWeapons = new Weapons();
	objectProjectiles = new Projectile();	
	objectBazooka = new Bazooka(objectPlayer->GetObjectPos(), objectProjectiles, objectPlayer, terrain, &camera);
	objectDynamite = new Dynamite(objectPlayer->GetObjectPos(), objectProjectiles, objectPlayer, terrain, &camera);
	objectUzi = new LilUzi(objectPlayer->GetObjectPos(), objectProjectiles, objectPlayer, terrain, &camera);
	objectGrenade = new Grenade(objectPlayer->GetObjectPos(), objectProjectiles, objectPlayer, terrain, &camera);
	objectEnemy = new Enemy(terrain, objectBazooka, objectDynamite, objectUzi, objectGrenade, objectPlayer, &camera);
	selection = new PlayerSelection(objectPlayer, &camera);
}

void Game::UpdateGame(sf::RenderWindow& _window)
{
	camera.initsoundgame();
	objectPlayer->Update(_window);
	objectEnemy->Update(_window);
	objectBazooka->Update(_window);
	objectDynamite->Update(_window);
	objectUzi->Update(_window);
	objectGrenade->Update(_window);
	camera.UpdateCamera();
	selection->UpdatePlayerSelection(_window);
}

void Game::DrawGame(sf::RenderWindow& _window)
{	
	camera.DisplayCameraGame(_window);
	terrain->DrawTerrain(_window);
	objectPlayer->Display(_window);
	objectEnemy->Display(_window);
	objectBazooka->Display(_window);
	objectDynamite->Display(_window);
	objectUzi->Display(_window);
	objectGrenade->Display(_window);
	camera.DisplayCameraHUD(_window);
	objectProjectiles->DisplayArrow(_window);
	selection->DrawPlayerSelection(_window);
	objectEnemy->DisplayAllhealth(_window);
}

