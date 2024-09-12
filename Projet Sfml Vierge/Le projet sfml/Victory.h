#pragma once
#include"tools.h"

void drawVictory(sf::RenderWindow& _window)
{
	sf::Text t;
	sf::Font f;
	f.loadFromFile("..\\Ressources\\Basic.ttf");
	t.setString("Victory");
	t.setFont(f);
	t.setPosition(sf::Vector2f(200, 200));
	t.setCharacterSize(50);
	t.setFillColor(sf::Color::White);
	_window.draw(t);
}