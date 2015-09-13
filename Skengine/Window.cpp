#include "Window.h"
#include "Errors.h"

namespace Skengine{
	Window::Window()
	{
	}


	Window::~Window()
	{
	}


	int Window::create(std::string windowName, int screenWidth, int screenHeight, unsigned int currentFlags)
	{

		Uint32 flags = SDL_WINDOW_OPENGL;
		if (currentFlags & INVISIBLE)
		{
			flags |= SDL_WINDOW_HIDDEN;
		}
		if (currentFlags & FULLSCREEN)
		{
			flags |= SDL_WINDOW_FULLSCREEN_DESKTOP;
		}
		if (currentFlags & BORDERLESS)
		{
			flags |= SDL_WINDOW_BORDERLESS;
		}
		_sdlWindow = SDL_CreateWindow(windowName.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, screenWidth, screenHeight, flags);
		if (!_sdlWindow)
			fatalError("SDL Window could not be created!");

		SDL_GLContext glContext = SDL_GL_CreateContext(_sdlWindow);
		if (!glContext)
			fatalError("SDL_GL Context could not be created!");

		GLenum error = glewInit();
		if (error != GLEW_OK)
			fatalError("Could not initialize glew!");

		glClearColor(50.f / 255, 50.f / 255, 50.f / 255, 0);

		printf("***   OpenGL Version: %s   ***\n", glGetString(GL_VERSION));

		SDL_GL_SetSwapInterval(0); // 1 = VSYNC, 0 = IMMEDIATE

		//Enable alpha blending
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

		return 0;
	}


	void Window::swapBuffer()
	{
		SDL_GL_SwapWindow(_sdlWindow);
	}
}