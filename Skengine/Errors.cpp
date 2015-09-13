#include "Errors.h"
#include <SDL\SDL.h>
#include <cstdlib>

namespace Skengine{
	void fatalError(std::string errorString)
	{
		printf("%s\nEnter any key to quit...", errorString.c_str());
		int tmp;
		std::cin >> tmp;
		SDL_Quit();
		exit(1);
	}
}