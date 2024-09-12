#include <iostream>
#include "SFML/Graphics.hpp"
#include "Game.h"
#include"StateManager.h"
#include"Menu.h"
#include"Victory.h"

using namespace sf;
using namespace std;



int main()
{
	RenderWindow window(sf::VideoMode(SCREEN_WIDTH, SCREEN_HEIGHT), "SFML works!");
	Game game;
	srand(time(NULL));
	StateManager sm;
	Menu menu(&sm);
    game.initGame(&sm);	

	while (window.isOpen())
	{
		tools::restartClock();
		Event event;
		while (window.pollEvent(event))
		{
			if (event.type == Event::Closed)
				window.close();
			menu.EventMenu(event);
			game.GameEvents(event);
		}
		if (sm.getState() == State::MENU)
		{

			menu.update(window, event);
		}
		if (sm.getState() == State::GAME)
		{
			game.UpdateGame(window);
		}

		window.clear();
		if (sm.getState() == State::MENU)
		{
			menu.display(window);
		}
		if (sm.getState() == State::GAME)
		{
			game.DrawGame(window);
		}
		if (sm.getState() == State::VICTORY)
		{
			drawVictory(window);
		}
		
		window.display();
	}
	delete[] game.terrain->pixels;
	return 0;
}
