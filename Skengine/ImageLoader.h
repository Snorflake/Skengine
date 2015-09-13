#pragma once
#include "GLTexture.h"
#include <string>
namespace Skengine{
	class ImageLoader
	{
	public:
		static GLTexture loadPNG(const std::string& filePath);
	};
}

