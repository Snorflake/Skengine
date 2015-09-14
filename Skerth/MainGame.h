#pragma once

#include <SDL\SDL.h>
#include <GL\glew.h>
#include <Skengine\Sprite.h>
#include <Skengine\GLSLProgram.h>
#include <vector>
#include <Skengine\SpriteBatch.h>
#include <Skengine\GLTexture.h>
#include <Skengine\Window.h>
#include <Skengine\Camera2D.h>
#include "Level.h"
#include <Skengine\InputManager.h>
#include <Skengine\Timing.h>
#include "Player.h" //Includes Agent & Humans
#include "Zombie.h"

enum class GAME_STATE
{
	PLAY,
	EXIT
};
class MainGame
{
public:
	MainGame();
	~MainGame();

	void run();
	
private:
	void initSystems();
	void initLevel();
	void initShaders();
	void gameLoop();
	void processInput();
	void drawGame();
	Skengine::Window _window;

	Skengine::InputManager _inputManager;

	Skengine::GLSLProgram _textureProgram;

	Skengine::Camera2D _camera;

	Skengine::SpriteBatch _agentSpriteBatch;

	std::vector<Level*> _levels;
	std::vector<Human*> _humans;
	std::vector<Zombie*> _zombies;
	Player* _player;

	GAME_STATE _currentState;

	int _fps;
	int _currentLevel;


	int _screenWidth, _screenHeight;
};

