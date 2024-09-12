#pragma once
#include"tools.h"
#include"Objects.h"
#include"Projectile.h"
#include"Player.h"
#include"Camera.h"
enum WeaponChoice
{
	BAZOOKA,
	DYNAMITE
};

class Weapons : public Objects
{
public : 
	Weapons();
	~Weapons();

	
    void Events(sf::Event _event) {};
	void Update(sf::RenderWindow& _window);
	void Display(sf::RenderWindow& _window);
	std::vector<Projectile*> bazookaMissiles;
	std::vector<Projectile*> dynamite;
	std::vector<Projectile*> Uzibullets;
	std::vector<Projectile*> grenades;
protected :
	float attackRadius;
	int attackDMG;
	float power;
	float angle;
	float shoottimer;
	
	Projectile* Missiles;
	Player* player;
	sf::RectangleShape weapon;
	
};



