#pragma once
#include <SDL\SDL.h>
#include <GL\glew.h>
#include <string>

namespace Skengine{
	enum WindowFlags
	{
		NONE = 0,
		INVISIBLE = 0x1,
		FULLSCREEN = 0x2,
		BORDERLESS = 0x4
	};
	class Window
	{
	public:
		Window();
		~Window();

		int create(std::string windowName, int screenWidth, int screenHeight, unsigned int currentFlags);

		int getScreenWidth() { return _screenWidth; }
		int getScreenHeight() { return _screenHeight; }

		void swapBuffer();
	private:
		SDL_Window* _sdlWindow;
		int _screenWidth;
		int _screenHeight;
	};

}