#include "Level.h"
#include <fstream>
#include <Skengine\Errors.h>

Level::Level(const std::string& fileName)
{
	std::ifstream file(fileName);

	if (file.fail())
		Skengine::fatalError("Failed to open " + fileName);

	
	std::string temp;
	file >> temp >> _numHumans;

	while (std::getline(file, temp))
	{
		_levelData.push_back(temp);
	}

	_spriteBatch.init();
	_spriteBatch.begin();
	glm::vec4 uvRect(0, 0, 1, 1);
	Skengine::Color whiteColor;
	whiteColor.r = 255;
	whiteColor.g = 255;
	whiteColor.b = 255;
	whiteColor.a = 255;

	for (int y = 0; y < _levelData.size(); y++)
	{
		for (int x = 0; x < _levelData[y].size(); x++)
		{
			char tile = _levelData[y][x];

			//Get dest rect
			glm::vec4 destRect(x * TILE_WIDTH,y * TILE_WIDTH,TILE_WIDTH,TILE_WIDTH);

			switch (tile)
			{
				case 'B':
				case 'R':
					
					_spriteBatch.draw(destRect, uvRect, Skengine::ResourceManager::getTexture("Textures/red_bricks.png").id, 0, whiteColor);
				break;
				case 'G':

					_spriteBatch.draw(destRect, uvRect, Skengine::ResourceManager::getTexture("Textures/glass.png").id, 0, whiteColor);
					break;
				case 'L':

					_spriteBatch.draw(destRect, uvRect, Skengine::ResourceManager::getTexture("Textures/light_bricks.png").id, 0, whiteColor);
					break;
				case '@':
					_startPlayerPosition.x = x * TILE_WIDTH;
					_startPlayerPosition.y = y * TILE_WIDTH;
					printf("%.0f, %.0f\n", _startPlayerPosition.x, _startPlayerPosition.y);
					break;				
				case 'Z':
					_zombieStartPositions.emplace_back(x * TILE_WIDTH, y * TILE_WIDTH);
						break;
				case '.':
						break;
				default:
					printf("Unexpected Symbol %c at (%i %i)\n", tile, x, y);
					break;

			}
		}
	}



	_spriteBatch.end();


}


Level::~Level()
{
}


void Level::draw()
{
	_spriteBatch.renderBatch();
}