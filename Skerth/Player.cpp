#include "Player.h"
#include <SDL\SDL.h>
Player::Player()
{
}


Player::~Player()
{
}

void Player::init(int speed, glm::vec2 pos,Skengine::InputManager* inputManager)
{
	_speed = speed;
	_position = pos;
	_color.r = 0;
	_color.g = 0;
	_color.b = 200;
	_color.a = 255;
	_inputManager = inputManager;
}

void Player::update(const std::vector<std::string>& levelData,
	std::vector<Human*>& humans,
	std::vector<Zombie*>& zombies)
{
	if (_inputManager->isKeyPressed(SDLK_w))
	{
		_position.y += _speed;
	}
	else if (_inputManager->isKeyPressed(SDLK_s))
	{
		_position.y -= _speed;
	}
	if (_inputManager->isKeyPressed(SDLK_a))
	{
		_position.x -= _speed;
	}
	else if (_inputManager->isKeyPressed(SDLK_d))
	{
		_position.x += _speed;
	}

	collideWithLevel(levelData);
}