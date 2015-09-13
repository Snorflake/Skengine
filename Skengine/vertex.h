#pragma once

#include <GL\glew.h>
namespace Skengine{
	struct Position
	{
		float x; //0x4
		float y;
	};
	struct Color
	{
		GLubyte r; //0x1
		GLubyte g;
		GLubyte b;
		GLubyte a;
	};
	struct UV
	{
		float u, v;
	};
	struct Vertex
	{
		Position position; //size = 0x8
		Color color; //size = 0x4
		UV uv;

		void setColor(GLubyte r, GLubyte g, GLubyte b, GLubyte a)
		{
			color.r = r;
			color.g = g;
			color.b = b;
			color.a = a;
		}
		void setUV(float u, float v)
		{
			uv.u = u;
			uv.v = v;
		}
		void setPosition(float x, float y)
		{
			position.x = x;
			position.y = y;
		}
		//total = 0xC or 12₁₀
		//Must be a multiple of DECIMAL 4. PAD IT!
	};
}