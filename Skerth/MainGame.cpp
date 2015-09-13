#include "MainGame.h"
#include <iostream>
#include <string>
#include <Skengine\Skengine.h>
#include <Skengine\Errors.h>
#include <Skengine\ResourceManager.h>
#include <Skengine\ImageLoader.h>
#include <Skengine\Timing.h>

MainGame::MainGame() : _screenWidth(1024), _screenHeight(768), _currentState(GAME_STATE::PLAY), _fps(0), _currentLevel(0), _player(nullptr)
{

}
MainGame::~MainGame()
{
	for (int i = 0; i < _levels.size(); i++)
		delete _levels[i];
}
void MainGame::run()
{
	initSystems();
	initLevel();
	gameLoop();
}

void MainGame::initSystems()
{
	Skengine::init();
	_window.create("Skerth Zombies", _screenWidth, _screenHeight, Skengine::NONE);
	glClearColor(.7f, .7f, .7f, 1.f);
	initShaders();

	_agentSpriteBatch.init();
	_camera.init(_screenWidth, _screenHeight);


}
void MainGame::initLevel()
{
	_levels.push_back(new Level("Levels/level1.txt"));
	_currentLevel = 0;

	_player = new Player();
	_player->init(1, _levels[_currentLevel]->getStartPlayerPos(), &_inputManager);
	//shit. only one texture is being drawn.

	_humans.push_back(_player);
}
void MainGame::gameLoop()
{
	Skengine::FpsLimiter fpsLimiter;
	fpsLimiter.setMaxFPS(60);
	while (_currentState == GAME_STATE::PLAY)
	{
		fpsLimiter.begin();



		processInput();
		_camera.setPosition(_player->getPosition());
		_camera.update();
		for (int i = 0; i < _humans.size(); i++)
		{
			_humans[i]->update();
		}
		//Add Zombies
		drawGame();

		_fps = fpsLimiter.end();
	}
}
void MainGame::drawGame()
{
	glClearDepth(1.f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	_textureProgram.use();
	
	glActiveTexture(GL_TEXTURE0); 
	GLint textureUniform = _textureProgram.getUniformLocation("mySampler");
	glUniform1i(textureUniform, 0); 

	glm::mat4 projectionMatrix = _camera.getCameraMatrix();
	GLint pUniform = _textureProgram.getUniformLocation("P");
	glUniformMatrix4fv(pUniform, 1, GL_FALSE, &(projectionMatrix[0][0]));

	_levels[_currentLevel]->draw(); 
	_agentSpriteBatch.begin();
	for (int i = 0; i < _humans.size(); i++)
	{
		_humans[i]->draw(_agentSpriteBatch);
	}
	_agentSpriteBatch.end(); 
	_agentSpriteBatch.renderBatch();
	_textureProgram.unuse();
	_window.swapBuffer();
}
void MainGame::initShaders()
{
	_textureProgram.compileShaders("Shaders/textureShading.vert", "Shaders/textureShading.frag"); //no IN your project
	_textureProgram.addAttrib("vertexPosition");
	_textureProgram.addAttrib("vertexColor");
	_textureProgram.addAttrib("vertexUV");
	_textureProgram.linkShaders();
}


void MainGame::processInput()
{
	SDL_Event event;
	const float CAMERA_SPEED = 10.f;
	const float SCALE_SPEED = 0.1f;
	while (SDL_PollEvent(&event))
	{
		switch (event.type)
		{
		case SDL_MOUSEMOTION:
			//printf("%i %i\n", event.motion.x, event.motion.y);
			_inputManager.setMouseCoords(event.motion.x, event.motion.y);
			break;
		case SDL_KEYDOWN:
			_inputManager.pressKey(event.key.keysym.sym);
			break;
		case SDL_MOUSEBUTTONDOWN:
			_inputManager.pressKey(event.button.button);
			break;
		case SDL_MOUSEBUTTONUP:
			_inputManager.releaseKey(event.button.button);
			break;
		case SDL_KEYUP:
			_inputManager.releaseKey(event.key.keysym.sym);
			break;
		}
	}

}