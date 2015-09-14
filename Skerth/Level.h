#pragma once
#include <vector>
#include <string>
#include <Skengine\SpriteBatch.h>
#include <Skengine\ResourceManager.h>

const int TILE_WIDTH = 64;
class Level
{
public:
	Level(const std::string& fileName);
	~Level();

	void draw();

	int getWidth() const { return _levelData[0].size(); }
	int getHeight() const { return _levelData.size(); }
	const std::vector<std::string>& getLevelData() const { return _levelData;  }
	int getNumHumans() const { return _numHumans;  }
	glm::vec2 getStartPlayerPos() const { return _startPlayerPosition;  }
	const std::vector<glm::vec2>& getStartZombiePositions() const { return _zombieStartPositions; }



private:
	std::vector<std::string> _levelData;
	int _numHumans;
	Skengine::SpriteBatch _spriteBatch; 
	glm::vec2 _startPlayerPosition;
	std::vector<glm::vec2> _zombieStartPositions;
};

