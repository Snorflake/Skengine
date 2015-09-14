#pragma once
#include "Human.h"
#include <Skengine\InputManager.h>
class Player : public Human
{
public:
	Player();
	~Player();

	void init(int speed, glm::vec2 pos, Skengine::InputManager* inputManager);

	void update(const std::vector<std::string>& levelData,
		std::vector<Human*>& humans,
		std::vector<Zombie*>& zombies);

private:
	Skengine::InputManager* _inputManager;
};

