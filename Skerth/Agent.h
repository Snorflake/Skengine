#pragma once
#include <glm\glm.hpp>
#include <Skengine\SpriteBatch.h>
const float AGENT_WIDTH = 60;
const float AGENT_RADIUS = AGENT_WIDTH / 2;

class Zombie;
class Human;

class Agent
{
public:
	Agent();
	virtual ~Agent();
	virtual void update(const std::vector<std::string>& levelData,
						std::vector<Human*>& humans,
						std::vector<Zombie*>& zombies) = 0;

	bool collideWithLevel(const std::vector<std::string>& levelData);

	bool collideWithAgent(Agent* agent);

	void draw(Skengine::SpriteBatch& spriteBatch);

	glm::vec2 getPosition() const { return _position; }
protected:
	void checkTilePosition(const std::vector<std::string>& levelData,std::vector<glm::vec2>& collidetilePositions,
							float x, float y);

	void collideWithTile(glm::vec2 tilePos);
	glm::vec2 _position;
	float _speed;
	Skengine::Color _color;

};

