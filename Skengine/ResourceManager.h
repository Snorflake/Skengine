#pragma once
#include "TextureCache.h"
namespace Skengine{
	class ResourceManager
	{
	public:

		static GLTexture getTexture(std::string filePath);
	private:
		static TextureCache _textureCache;

	};
}
