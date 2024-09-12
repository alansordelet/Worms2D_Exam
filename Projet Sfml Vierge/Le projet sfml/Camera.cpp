#include "Camera.h"

template <typename T>
T newlerp(T a, T b, float t) {
	return a + (b - a) * t;
}

bool reverseBool(bool value)
{
	return !value;
}

void LimitViewCenter(sf::View& view, const sf::Vector2f screenSize)
{
	sf::Vector2f viewCenter = view.getCenter();
	sf::Vector2f viewSize = view.getSize();
	sf::Vector2f minViewCenter = viewSize / 2.f;
	sf::Vector2f maxViewCenter = screenSize - viewSize / 2.f;
	viewCenter.x = std::max(minViewCenter.x, std::min(viewCenter.x, maxViewCenter.x));
	viewCenter.y = std::max(minViewCenter.y, std::min(viewCenter.y, maxViewCenter.y));
	view.setCenter(viewCenter);
	view.setSize(viewSize);
}

Camera::Camera()
{
	ViewGame.setSize(600, 400);
	posCameraGame.x = 1920;
	posCameraGame.y = 1080;
}

Camera::~Camera()
{
}

void Camera::UpdateCamera()
{
	ViewGame.setSize(600, 400);
	newtimer += tools::GetTimeDelta();
	float posY = initialY + amplitude * std::sin(time * frequency);
	text.setPosition(220.0f, posY); 	
	time += 0.01f;

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Q))
	{
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::LShift))
		{
			posCameraGame.x -= 450 * tools::GetTimeDelta();
		}
		else
			posCameraGame.x -= 150 * tools::GetTimeDelta();
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Z))
	{
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::LShift))
		{
			posCameraGame.y -= 450 * tools::GetTimeDelta();
		}
		else
			posCameraGame.y -= 150 * tools::GetTimeDelta();
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
	{
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::LShift))
		{
			posCameraGame.x += 450 * tools::GetTimeDelta();
		}
		else
			posCameraGame.x += 150 * tools::GetTimeDelta();
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
	{
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::LShift))
		{
			posCameraGame.y += 450 * tools::GetTimeDelta();
		}
		else
			posCameraGame.y += 150 * tools::GetTimeDelta();
	}
	if ((sf::Keyboard::isKeyPressed(sf::Keyboard::Enter)) && newtimer > 0.3f && SelectingPlayer == false)
	{
		if (targetPosition.x == 900) {
			targetPosition.x = 1200;
		}
		newtimer = 0;
	}
	if ((sf::Keyboard::isKeyPressed(sf::Keyboard::Tab)) && newtimer > 0.3f && SelectingPlayer == false)
	{
		if (targetPosition.x == 900) {
			targetPosition.x = 1200;
		}
		else {
			targetPosition.x = 900;
		}
		newtimer = 0;
	}
	targetPosition.y = 0;

	if (targetPosition.x == 900)
		Selecting = true;
	if (targetPosition.x == 1200)
		Selecting = false;

	if (SelectingPlayer == false)
	{
		timerforPlayer += tools::GetTimeDelta();
	}

	if ((timerforPlayer > 15 )|| getpassTurn() == true)
	{
		if (getpassTurn() == false) // if hasnt shot 
		{
			if (nextTurn == true)// if it is my players turn
				SelectingPlayer = true; // so the player can select the player he wants
			else
				Selecting = false; // put weapon bar back to initial pos
				
			setTurn(reverseBool(nextTurn));
	    }
		
		timerforPlayer = 0;
	}
	if (getpassTurn() == true)// if has shot
	{
		timerlooking += tools::GetTimeDelta();
		timerforPlayer = 0; // reset Main timer
	}
	if (timerlooking > 3)// 3 secondsafter shot
	{
		if (nextTurn == true)// if it is my players turn
		SelectingPlayer = true; // if shot but was not my turn
		else
			Selecting = false;// if shot and was my turn
		setTurn(reverseBool(nextTurn));
		setpassTurn(false);
		timerlooking = 0;
	}
	
	float dt = 1.0f / 60.0f;
	sf::Vector2f currentPosition = weaponBar.getPosition();
	sf::Vector2f newPosition = newlerp(currentPosition, targetPosition, dt * 1);
	weaponBar.setPosition(newPosition);

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape) && newtimer > 0.3f && SelectingPlayer == false)
	{
		SelectingPlayer = true;
		targetPosition.x = 1200;
		sounds.stopSound("GameMusic");
		playmusic = false;
		sm->ChangeState(MENU);
		newtimer = 0;
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down) && newtimer > 0.3f && Selecting == true)
	{
		if (getWC() < 4)
			addorReduceWC(1);
		else
			setWC(0);

		newtimer = 0;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) && newtimer > 0.3f && Selecting == true)
	{
		if (getWC() > 0)
			addorReduceWC(-1);
		else
			setWC(4);

		newtimer = 0;
	}
	for (int i = 0; i < weapons.size(); i++)
	{
		if (i == getWC())
		{
			weapons[i].setOutlineColor(sf::Color::Blue);		
		}
		else
		{
			weapons[i].setOutlineColor(sf::Color::White);		
		}
		weapons[i].setOutlineThickness(3);
		weapons[i].setPosition(newPosition.x+ 75, 200 + (i * 75));
		
	} 
	uzisprite.setPosition(newPosition.x + 75, 425);
	grenadesprite.setPosition(newPosition.x + 75, 495);
	dynamitesprite.setPosition(newPosition.x + 75, 350);
	bazookasprite.setPosition(newPosition.x + 75, 255);

	ViewGame.setCenter(posCameraGame);
}

void Camera::DisplayCameraMinimap(sf::RenderWindow& _window)
{
	_window.setView(ViewMinimap);
}

void Camera::DisplayCameraGame(sf::RenderWindow& _window)
{
	LimitViewCenter(ViewGame, sf::Vector2f(SCREEN_WIDTH, SCREEN_HEIGHT));
	_window.setView(ViewGame);
}

void Camera::DisplayCameraHUD(sf::RenderWindow& _window)
{
	
	_window.setView(ViewHUD);
	
	_window.draw(weaponBar);
	for (const auto& rect : weapons) {
		_window.draw(rect);
	}
	_window.draw(uzisprite);
	_window.draw(grenadesprite);
	_window.draw(dynamitesprite);
	_window.draw(bazookasprite);
	stringtime = std::to_string(timerforPlayer);
	textTimer.setString("Timer : " + stringtime);
	textTimer.setPosition(-100, 100);
	if (SelectingPlayer)
	_window.draw(text);
	if (!SelectingPlayer)
	_window.draw(textTimer);
	
	
	
}