#include "Agent.h"

#include <Skengine\ResourceManager.h>

Agent::Agent()
{
}


Agent::~Agent()
{
}


void Agent::draw(Skengine::SpriteBatch& spriteBatch)
{
	static int textureID = Skengine::ResourceManager::getTexture("Textures/circle.png").id; //Texture caching (works)
	glm::vec4 destRect(_position.x,_position.y,AGENT_WIDTH,AGENT_WIDTH); //height? its a square #define AGENT_HEIGHT AGENT_WIDTH whatever
	glm::vec4 uv(0,0,1,1);

	spriteBatch.draw(destRect, uv, textureID, 0, _color);
}