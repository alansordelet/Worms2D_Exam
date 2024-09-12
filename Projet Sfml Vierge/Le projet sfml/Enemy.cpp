#include"Enemy.h"
sf::Vector2f findClosestElement(sf::Vector2f pos1, sf::Vector2f pos2)
{
	float distance = std::sqrt((pos1.x - pos2.x) * (pos1.x - pos2.x) +
		(pos1.y - pos2.y) * (pos1.y - pos2.y));
	if (distance <= 0.0f)
	{
		return pos1;
	}
	else if (distance <= 0.5f)
	{
		return sf::Vector2f((pos1.x + pos2.x) / 2.f, (pos1.y + pos2.y) / 2.f);
	}
	else
	{
		if (std::abs(pos1.x - pos2.x) < std::abs(pos1.y - pos2.y))
		{
			return pos1;
		}
		else
		{
			return pos2;
		}
	}
}

int randomy(int min, int max)
{
	srand(time(NULL)); // initialisation du générateur de nombres aléatoires
	return min + rand() % (max - min + 1);
}

sf::FloatRect convertLineToFloatRect(sf::Vector2f startPos, sf::Vector2f endPos)
{
	float minX = std::min(startPos.x, endPos.x);
	float minY = std::min(startPos.y, endPos.y);
	float maxX = std::max(startPos.x, endPos.x);
	float maxY = std::max(startPos.y, endPos.y);

	sf::FloatRect rect(minX, minY, maxX - minX, maxY - minY);
	return rect;
}

Enemy::Enemy(Terrain* _terrain, Bazooka* _weaponProjectiles, Dynamite* _weaponProjectiles2, LilUzi* _weaponProjectiles3, Grenade* _weaponProjectiles4, Player* _player, Camera* _camera)
{
	terrain = _terrain;
	eBazookaProjectiles = _weaponProjectiles;
	eDynamiteProjectiles = _weaponProjectiles2;
	eUziProjectiles = _weaponProjectiles3;
	eGrenadeProjectiles = _weaponProjectiles4;
	player = _player;
	camera = _camera;
	for (int i = 0; i < AllEnemies.size(); i++)
	{
		AllEnemies[i]->Enemies.setSize(sf::Vector2f(100, 100));
		AllEnemies[i]->Enemies.setPosition(tools::frand(100, 600), tools::frand(100, 522));
		AllEnemies[i]->Enemies.setFillColor(sf::Color::Red);
		AllEnemies[i]->healthbar.setFillColor(sf::Color::Yellow);
	}
	for (int i = 0; i < 4; i++)
	{
		AllEnemies.push_back(new Enemy(sf::Vector2f(tools::frand(100, 1000), tools::frand(100, 522)), enemyhealth));
	}
	aistate = CHECKING_POS;
}

Enemy::~Enemy()
{

}

void Enemy::Update(sf::RenderWindow& _window)
{
	line.setPrimitiveType(sf::Lines);
	line.resize(5);

	for (int i = 0; i < AllEnemies.size(); i++)
	{
		std::vector<Enemy*>::iterator it = AllEnemies.begin();
		while (it != AllEnemies.end()) {
			if ((*it)->enemyhealth <= 0) {
				delete* it;
				it = AllEnemies.erase(it);
			}
			else {
				++it;
			}
		}
		if (camera->getTurn() == true)
		{
			if (camera->RandomisePlayer == false)
			{
				if (camera->getnextEnemy() < AllEnemies.size() - 1)
					camera->addnextEnemy(1);
				else
					camera->setnextEnemy(0);
				camera->RandomisePlayer = true;
			}

			AllEnemies[i]->Enemies.setOutlineColor(sf::Color::Red);
			if (camera->getnextEnemy() < AllEnemies.size() - 1)
			{
				AllEnemies[camera->getnextEnemy()]->Enemies.setOutlineColor(sf::Color::White);
				AllEnemies[camera->getnextEnemy()]->Enemies.setOutlineThickness(1.5);
				camera->setPosCamera(AllEnemies[camera->getnextEnemy()]->ObjectPos);
			}
			std::cout << camera->getnextEnemy() << std::endl;

			if (camera->getnextEnemy() < AllEnemies.size() - 1)
			{
				line[0].position = findClosestElement(AllEnemies[camera->getnextEnemy()]->ObjectPos, player->Players[player->getnextP()]->GetObjectPos());
				line[1].position = findClosestElement(player->Players[player->getnextP()]->GetObjectPos(), AllEnemies[camera->getnextEnemy()]->ObjectPos);
				
				if (checkCollision(terrain->pixels, convertLineToFloatRect(line[0].position, line[1].position)))
				{
					line[0].color = sf::Color::Red;
					line[1].color = sf::Color::Red;
				}
				else
				{
					line[0].color = sf::Color::Blue;
					line[1].color = sf::Color::Blue;
				}

			
		    }
			if (line[0].color == sf::Color::Red && aistate == CHECKING_POS)
			{
				int random = randomy(0, 2);
				if (random == 1)
					aistate = FIRING;
				else
					aistate = FIRING;
				random = 0;

			}
			if (aistate == MOVING)
			{
				if (camera->getnextEnemy() < AllEnemies.size() - 1)
				if (!tools::Circle_Collision(AllEnemies[camera->getnextEnemy()]->GetObjectPos(), player->Players[player->getnextPlayer()]->GetObjectPos(), 20, 20))
				{
					if (AllEnemies[camera->getnextEnemy()]->GetObjectPos().x < player->Players[player->getnextPlayer()]->GetObjectPos().x)
					{
						if (AllEnemies[camera->getnextEnemy()]->EnemyVelocity.x < 20)
							AllEnemies[camera->getnextEnemy()]->EnemyVelocity.x += 0.2;
					}
					else
					{
						if (AllEnemies[camera->getnextEnemy()]->EnemyVelocity.x > -20)
							AllEnemies[camera->getnextEnemy()]->EnemyVelocity.x -= 0.2;
					}
				}
				else
				{
					aistate = FIRING;

				}
			}
		}
		else
		{
			camera->RandomisePlayer = false;
			aistate = CHECKING_POS;
			isProjectilePushedBack = false;
		}

		if (aistate == FIRING)
		{
			sf::Vector2f startPos;
			if (camera->getnextEnemy() < AllEnemies.size() - 1)
			{
				 startPos = AllEnemies[camera->getnextEnemy()]->GetObjectPos();
			}
			
			sf::Vector2f targetPos = player->GetObjectPos();
			float windspeed = 0;
			float winddirection = 0;
			sf::Vector2f displacement = targetPos - startPos;
			displacement += sf::Vector2f(winddirection * windspeed, 0.0f);
			float angle = std::atan2(displacement.y, displacement.x) * 180.0f / M_PI;
			float distance = std::sqrt(std::pow(displacement.x, 2) + std::pow(displacement.y, 2));
			float power = 100;

			if (!isProjectilePushedBack) {
				int randomNum = randomy(1,2);
				std::cout << randomNum;
				if (randomNum == 1) {
					eBazookaProjectiles->bazookaMissiles.push_back(new BazookaProjectile(sf::Vector2f(startPos.x + 12,startPos.y - 40), randomy(30,90), power));			
					isProjectilePushedBack = true;
				}
				else if (randomNum == 2) {
					eDynamiteProjectiles->dynamite.push_back(new DynamiteProjectile(startPos));
					isProjectilePushedBack = true;
				}
			}
			aistate = CHECKING_POS;
		}

		if ((AllEnemies[i]->EnemyVelocity.y == 0.0000))
		{
			AllEnemies[i]->EnemyVelocity.x = 0;
		}
		AllEnemies[i]->EnemyVelocity.y += 90.81 * tools::GetTimeDelta();
		AllEnemies[i]->ObjectPos += AllEnemies[i]->EnemyVelocity * tools::GetTimeDelta();
		float topOfGreenPixels = terrain->getTopOfGreenPixels(AllEnemies[i]->GetObjectPos().x + 5, AllEnemies[i]->GetObjectPos().y + 5);

		sf::Vector2f nextPosition = AllEnemies[i]->ObjectPos + AllEnemies[i]->EnemyVelocity * tools::GetTimeDelta();
		if ((AllEnemies[i]->ObjectPos.y + 25 > topOfGreenPixels))
		{
			float interpolationFactor = 0.01f;
			AllEnemies[i]->ObjectPos.y = AllEnemies[i]->ObjectPos.y + (topOfGreenPixels - (AllEnemies[i]->ObjectPos.y + 25)) * interpolationFactor;
			AllEnemies[i]->EnemyVelocity.y = 0.0000000;
		}
		else
		{
			AllEnemies[i]->ObjectPos = nextPosition;
		}
		AllEnemies[i]->Enemies.setPosition(AllEnemies[i]->ObjectPos);
		healthbar.setSize(sf::Vector2f(AllEnemies[i]->enemyhealth, 15));
		AllEnemies[i]->healthbar.setPosition(sf::Vector2f(AllEnemies[i]->GetObjectPos().x - 12, AllEnemies[i]->GetObjectPos().y - 20));

		if (AllEnemies[i]->ObjectPos.x < 0.0f || AllEnemies[i]->ObjectPos.x > SCREEN_WIDTH ||
			AllEnemies[i]->ObjectPos.y < 0.0f || AllEnemies[i]->ObjectPos.y > SCREEN_HEIGHT - 50)
		{
			AllEnemies[i]->enemyhealth += -1;
		}
	}
}

void Enemy::Display(sf::RenderWindow& _window)
{
	sf::FloatRect bazookaprojectileBounds;
	sf::FloatRect dynamiteprojectileBounds;
	sf::FloatRect UziprojectileBounds;
	sf::FloatRect grenadeprojectileBounds;
	for (size_t i = 0; i < eBazookaProjectiles->bazookaMissiles.size(); i++)
	{
		eBazookaProjectiles->bazookaMissiles[i]->getProjectile();

		bazookaprojectileBounds = eBazookaProjectiles->bazookaMissiles[i]->getProjectile().getGlobalBounds();
	}
	for (size_t i = 0; i < eDynamiteProjectiles->dynamite.size(); i++)
	{

		dynamiteprojectileBounds = eDynamiteProjectiles->dynamite[i]->getProjectile().getGlobalBounds();
	}
	for (size_t i = 0; i < eUziProjectiles->Uzibullets.size(); i++)
	{

		UziprojectileBounds = eUziProjectiles->Uzibullets[i]->getProjectile().getGlobalBounds();
	}
	for (size_t i = 0; i < eGrenadeProjectiles->grenades.size(); i++)
	{
		grenadeprojectileBounds = eGrenadeProjectiles->grenades[i]->getProjectile().getGlobalBounds();
	}

	for (size_t i = 0; i < AllEnemies.size(); i++)
	{

		if (isPositionInRadius(AllEnemies[i]->GetObjectPos(), sf::Vector2f(bazookaprojectileBounds.left, bazookaprojectileBounds.top), 30) ||
			isPositionInRadius(AllEnemies[i]->GetObjectPos(), sf::Vector2f(dynamiteprojectileBounds.left, dynamiteprojectileBounds.top), 30) ||
			isPositionInRadius(AllEnemies[i]->GetObjectPos(), sf::Vector2f(UziprojectileBounds.left, UziprojectileBounds.top), 30) ||
			isPositionInRadius(AllEnemies[i]->GetObjectPos(), sf::Vector2f(grenadeprojectileBounds.left, grenadeprojectileBounds.top), 30))
		{
			if (AllEnemies[i]->thisone == true)
			{
				
				if (bazookaprojectileBounds.width > 0 && bazookaprojectileBounds.height > 0)
				{
					AllEnemies[i]->addEnemyhealth(-30);
					AllEnemies[i]->getHit(sf::Vector2f(bazookaprojectileBounds.left, bazookaprojectileBounds.top), AllEnemies[i]->GetObjectPos(), (200 * tools::GetTimeDelta()), (200 * tools::GetTimeDelta()));
				}
				
				if (dynamiteprojectileBounds.width > 0 && dynamiteprojectileBounds.height > 0)
				{
					AllEnemies[i]->addEnemyhealth(-20);
					AllEnemies[i]->getHit(sf::Vector2f(dynamiteprojectileBounds.left, dynamiteprojectileBounds.top), AllEnemies[i]->GetObjectPos(), (200 * tools::GetTimeDelta()), (200 * tools::GetTimeDelta()));
				}
					
				if (UziprojectileBounds.width > 0 && UziprojectileBounds.height > 0)
				{
					AllEnemies[i]->addEnemyhealth(-10);
					AllEnemies[i]->getHit(sf::Vector2f(UziprojectileBounds.left, UziprojectileBounds.top), AllEnemies[i]->GetObjectPos(), (200 * tools::GetTimeDelta()), (200 * tools::GetTimeDelta()));
				}
					
				if (grenadeprojectileBounds.width > 0 && grenadeprojectileBounds.height > 0)
				{
					AllEnemies[i]->addEnemyhealth(-20);
					AllEnemies[i]->getHit(sf::Vector2f(grenadeprojectileBounds.left, grenadeprojectileBounds.top), AllEnemies[i]->GetObjectPos(), (200 * tools::GetTimeDelta()), (200 * tools::GetTimeDelta()));
				}
					
				AllEnemies[i]->thisone = false;
			}
			AllEnemies[i]->healthbar.setSize(sf::Vector2f(AllEnemies[i]->enemyhealth, 15));

		}
		else
		{
			AllEnemies[i]->thisone = true;
		}

	}

	for (int i = 0; i < AllEnemies.size(); i++)
	{
		_window.draw(AllEnemies[i]->Enemies);
		_window.draw(AllEnemies[i]->healthbar);
		
	}
	_window.draw(line);

	

	if (AllEnemies.empty())
	{
		_window.close();
	}
}
void Enemy::DisplayAllhealth(sf::RenderWindow& _window)
{
	float accumulatedHealth = 0.0f;
	for (int i = 0; i < AllEnemies.size(); i++)
	{
		float enemyHealth = AllEnemies[i]->getEnemyhealth();
		accumulatedHealth += enemyHealth;
	}
	Allenemyhealth.setSize(sf::Vector2f(accumulatedHealth, 15));
	Allenemyhealth.setFillColor(sf::Color::Red);
	Allenemyhealth.setPosition(sf::Vector2f(850, 240));
	_window.draw(Allenemyhealth);
}