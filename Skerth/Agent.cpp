#include "Agent.h"

#include <Skengine\ResourceManager.h>
#include "Level.h"
#include <algorithm>

Agent::Agent()
{
}


Agent::~Agent()
{
}

bool Agent::collideWithLevel(const std::vector<std::string>& levelData)
{
	std::vector<glm::vec2> collidetilePositions;

	//Check the four corners
	//First corner
	checkTilePosition(levelData, collidetilePositions, _position.x, _position.y);

	//second corner
	checkTilePosition(levelData, collidetilePositions, _position.x + AGENT_WIDTH, _position.y);

	//third corner
	checkTilePosition(levelData, collidetilePositions, _position.x, _position.y + AGENT_WIDTH);


	//fourth corner
	checkTilePosition(levelData, collidetilePositions, _position.x + AGENT_WIDTH, _position.y + AGENT_WIDTH);

	if (collidetilePositions.size() == 0)
		return false;

	for (int i = 0; i < collidetilePositions.size(); i++)
		collideWithTile(collidetilePositions[i]);

	return true;
}
bool Agent::collideWithAgent(Agent* agent)
{
	//Circular collision
	const float MIN_DISTANCE = AGENT_RADIUS * 2;

	glm::vec2 centerPosA = _position + glm::vec2(AGENT_RADIUS);
	glm::vec2 centerPosB = agent->getPosition() + glm::vec2(AGENT_RADIUS);

	glm::vec2 distVec = centerPosA - centerPosB;
	float distance = glm::length(distVec);
	float collisionDepth = MIN_DISTANCE - distance;

	if (collisionDepth > 0)
	{

		glm::vec2 collisionDepthVec = glm::normalize(distVec) * collisionDepth;
		_position += collisionDepthVec / 2.f;
		agent->_position -= collisionDepthVec / 2.f;
		return true;
	}


	return false;
}
void Agent::draw(Skengine::SpriteBatch& spriteBatch)
{
	static int textureID = Skengine::ResourceManager::getTexture("Textures/circle.png").id; //Texture caching (works)
	glm::vec4 destRect(_position.x,_position.y,AGENT_WIDTH,AGENT_WIDTH); //height? its a square #define AGENT_HEIGHT AGENT_WIDTH whatever
	glm::vec4 uv(0,0,1,1);

	spriteBatch.draw(destRect, uv, textureID, 0, _color);
}

void Agent::checkTilePosition(const std::vector<std::string>& levelData,std::vector<glm::vec2>& collidetilePositions,
	float x, float y)
{
	glm::vec2 cornerPos = glm::vec2(floor(x / (float)TILE_WIDTH),
		floor(y / (float)TILE_WIDTH));

	if (cornerPos.x < 0 || cornerPos.x >= levelData[0].length() ||
		cornerPos.y < 0 || cornerPos.y >= levelData.size())
		return;
	if (levelData[cornerPos.y][cornerPos.x] != '.')
	{
		collidetilePositions.push_back(cornerPos  * (float)TILE_WIDTH + glm::vec2(TILE_WIDTH / 2));
	}
}
//AABB
void Agent::collideWithTile(glm::vec2 tilePos)
{
	const float TILE_RADIUS = (float)TILE_WIDTH / 2;
	const float MIN_DISTANCE = AGENT_RADIUS + TILE_RADIUS;
	glm::vec2 centerPlayerPos = _position + glm::vec2(AGENT_RADIUS);
	glm::vec2 distVec = centerPlayerPos - tilePos;
	float xdepth = MIN_DISTANCE - abs(distVec.x);
	float ydepth = MIN_DISTANCE - abs(distVec.y);


	if (xdepth > 0 || ydepth > 0)
	{
		//COLLIDING
		if (std::max(xdepth,0.f) < std::max(ydepth, 0.f))
		{
			if (distVec.x > 0)
			_position.x += xdepth;
			else
				_position.x -= xdepth;
		}
		else
		{
			if (distVec.y > 0)
				_position.y += ydepth;
			else
				_position.y -= ydepth;
		}
	}

}