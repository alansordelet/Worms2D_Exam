#include "menu.h"


bool reverseBoolplease(bool value)
{
	return !value;
}
WritingState ws;


Menu::Menu()
{

}

Menu::Menu(StateManager* _sm)
{
	sm = _sm;
	
	viewmenu.setSize(SCREEN_WIDTH, SCREEN_HEIGHT);
	viewmenu.setCenter(sf::Vector2f(600, 400));
	menuTimer = 0.f;
	optionactive = false;
	inEmptyMenu = true;
	isDragging = false;

	menuTexture.loadFromFile("..\\Ressources\\wallpaper.png");
	menuTexture2.loadFromFile("..\\Ressources\\background.jpg");
	

	playerInputT.setFont(f);
	playerPortInputT.setFont(f);
	playerUsernameInputT.setFont(f);

	volumeBar.setSize(sf::Vector2f(200.f, 20.f));
	volumeBar.setFillColor(sf::Color::White);
	volumeBar.setPosition(100.f, 100.f);

	volumeButton.setRadius(10.f);
	volumeButton.setFillColor(sf::Color::Red);
	volumeButton.setPosition(volumeBar.getPosition().x, volumeBar.getPosition().y + volumeBar.getSize().y / 2.f);


	menuPosition = sf::Vector2f(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2);
	
}

void Menu::init()
{
}

void Menu::update(sf::RenderWindow& _window, sf::Event& _event)
{
	if (playMusic == false)
	{
		sounds.loadSound("MenuMusic", "MenuMusic.wav");
		sounds.playSoundQuick("MenuMusic");
		sounds.setSoundLoop("MenuMusic", true);
		playMusic = true;
	}
	sf::Vector2i mousePos = sf::Mouse::getPosition(_window);

	if (optionactive == true)
	updateOptions(_window, _event);
}

void Menu::setFullscreen(sf::RenderWindow& _window)
{
	if (fullscreen)
	{
		_window.create(sf::VideoMode(SCREEN_WIDTH, SCREEN_HEIGHT), "Medieval_RTS", sf::Style::Default);
		fullscreen = false;
	}
	else
	{
		_window.create(sf::VideoMode(SCREEN_WIDTH, SCREEN_HEIGHT), "Medieval RTS", sf::Style::Fullscreen);
		fullscreen = true;
	}
}

void Menu::setVsynch(sf::RenderWindow& _window)
{
	if (vsynch)
	{
		_window.setVerticalSyncEnabled(false);
		vsynch = false;
	}
	else
	{
		_window.setVerticalSyncEnabled(true);
		vsynch = true;
	}
}

float Menu::soundAlgo(sf::Vector2f _x)
{
	float result;

	result = (_x.x - volumeBar.getPosition().x) * 100 / 200;

	return result;
}

void Menu::setSoundVolume(sf::RenderWindow& _window, sf::Event& _event)
{
	sf::Vector2i mousePosI = sf::Mouse::getPosition(_window);
	Vector2f mousePosF = (_window.mapPixelToCoords(mousePosI, viewmenu));

	// = volumeButton.getPosition();

	if (volumeBar.getGlobalBounds().contains(mousePosF))
	{
		if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
		{
			isDragging = true;
		}
		else
		{
			isDragging = false;
		}
	}

	if (isDragging)
	{
		float newX = std::max(volumeBar.getPosition().x, std::min(mousePosF.x, volumeBar.getPosition().x + volumeBar.getSize().x));
		volumeButton.setPosition(newX, volumeButton.getPosition().y);
	}
	soundAlgo(volumeButton.getPosition());
}

void Menu::updateOptions(sf::RenderWindow& _window, sf::Event& _event)
{
	sf::Vector2i mousePosI = sf::Mouse::getPosition(_window);
	Vector2f mousePos = (_window.mapPixelToCoords(mousePosI, viewmenu));

	setSoundVolume(_window, _event);

}

void Menu::updateLobbyHost(sf::RenderWindow& _window)
{

}

void Menu::updateLobbyClient(sf::RenderWindow& _window)
{
	

}

void Menu::EventMenu(sf::Event& _event)
{

}

void Menu::display(sf::RenderWindow& _window)
{
	_window.setView(viewmenu);
	menuTimer += tools::GetTimeDelta();
	sf::Vector2i mousePosI = sf::Mouse::getPosition(_window);
	Vector2f mousePos = (_window.mapPixelToCoords(mousePosI, viewmenu));
	sf::Sprite menuSprite;

	if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && menuTimer > 0.2)
	{
		if (mousePos.x >= 655.f && mousePos.x <= 810.f && mousePos.y >= 400 && mousePos.y <= 450)
		{
			playMusic = false;
			sounds.pauseSound("MenuMusic");		
			sm->ChangeState(GAME);
		}
		if (mousePos.x >= 655.f && mousePos.x <= 810.f && mousePos.y >= 500 && mousePos.y <= 550)
		{
			optionactive = reverseBoolplease(optionactive);
		}
		if ((mousePos.x >= 850 && mousePos.x <= 980 && mousePos.y >= 396 && mousePos.y <= 460) && optionactive == true)
		{
			setVsynch(_window);	
		}
		if ((mousePos.x >= 850 && mousePos.x <= 980 && mousePos.y >= 546 && mousePos.y <= 596) && optionactive == true)
		{
			setFullscreen(_window);
		}
		menuTimer = 0;
	}

	menuSprite.setTexture(menuTexture2, true);
	_window.draw(menuSprite);

	menuSprite.setTexture(menuTexture, true);
	menuSprite.setPosition(320, 90);
	menuSprite.setScale(0.2, 0.2);
	_window.draw(menuSprite);

	sf::RectangleShape rectPlay(sf::Vector2f(150, 50));
	sf::RectangleShape rectOption(sf::Vector2f(150, 50));

	font.loadFromFile("..\\Ressources\\Basic.ttf");
	text.setString("Play");
	text.setFont(font);
	text.setCharacterSize(34);
	text.setFillColor(sf::Color::Black);
	text2.setString("Option");
	text2.setFont(font);
	text2.setCharacterSize(34);
	text2.setFillColor(sf::Color::Black);

	if (mousePos.x >= 655.f && mousePos.x <= 810.f && mousePos.y >= 400 && mousePos.y <= 450)
	{
		rectPlay.setFillColor(sf::Color::Green);
	}
	else
	{
		rectPlay.setFillColor(sf::Color::White);		
	}
	if (mousePos.x >= 655.f && mousePos.x <= 810.f && mousePos.y >= 500 && mousePos.y <= 550)
	{
		rectOption.setFillColor(sf::Color::Green);
	}
	else
	{
		rectOption.setFillColor(sf::Color::White);
	}

	rectPlay.setPosition(sf::Vector2f(660,400));
	text.setPosition(sf::Vector2f(660,400));
	rectOption.setPosition(sf::Vector2f(660,500));
	text2.setPosition(sf::Vector2f(660,500));
	
	_window.draw(tOption);
	_window.draw(rectPlay);
	_window.draw(rectOption);
	_window.draw(text);
	_window.draw(text2);


	if(optionactive == true)
	displayOptions(_window);
}

void Menu::drawVolume(sf::RenderWindow& _window)
{
	_window.draw(volumeBar);
	_window.draw(volumeButton);
}

void Menu::displayOptions(sf::RenderWindow& _window)
{
	sf::RectangleShape FullscreenShape;
	FullscreenShape.setOrigin(FullscreenShape.getGlobalBounds().width / 2.f, FullscreenShape.getGlobalBounds().height / 2.f);
	FullscreenShape.setSize(sf::Vector2f(100.f, 75.f));
	FullscreenShape.setPosition(850.f, 546.f);
	_window.draw(FullscreenShape);


	sf::RectangleShape optionsShape;
	optionsShape.setOrigin(optionsShape.getGlobalBounds().width / 2.f, optionsShape.getGlobalBounds().height / 2.f);
	optionsShape.setSize(sf::Vector2f(100.f, 75.f));
	optionsShape.setFillColor(sf::Color::Magenta);
	optionsShape.setPosition(sf::Vector2f(850.f, 396.f));
	
	_window.draw(optionsShape);
	drawVolume(_window);
}

void Menu::destroy()
{
}
