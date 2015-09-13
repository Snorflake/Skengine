#include "TextureCache.h"
#include "ImageLoader.h"

namespace Skengine{
	TextureCache::TextureCache()
	{
	}


	TextureCache::~TextureCache()
	{
	}

	GLTexture TextureCache::getTexture(std::string filePath)
	{
		//lookup texture and see if its in the map
		auto mit = _textureMap.find(filePath);

		//check if its not in the map
		if (mit == _textureMap.end())
		{
			GLTexture newTexture = ImageLoader::loadPNG(filePath);

			//Insert into the map
			_textureMap.insert(make_pair(filePath, newTexture));


			return newTexture;
		}
		return mit->second;
	}
}