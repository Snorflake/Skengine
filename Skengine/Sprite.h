#pragma once
#include <GL\glew.h>
#include "GLTexture.h"
#include <string>
namespace Skengine{
	class Sprite
	{
	public:
		Sprite();
		~Sprite();

		void init(float x, float y, float w, float h, std::string texturePath);

		void draw();

	private:
		float _x, _y, _w, _h;
		GLuint _vboID;
		GLTexture _texture;

	};
}
