#pragma once
#include <GL\glew.h>
#include "vertex.h"
#include <glm\glm.hpp>
#include <vector>
namespace Skengine{

enum class GlyphSortType
{
	NONE,
	FRONT_TO_BACK,
	BACK_TO_FRONT,
	TEXTURE
};
struct Glyph
{

	GLuint texture;
	float depth;
	Vertex topLeft;
	Vertex bottomLeft;
	Vertex topRight;
	Vertex bottomRight;
};
class RenderBatch
{
public:
	RenderBatch(GLuint Offset, GLuint NumVerticies, GLuint Texture) : offset(Offset),
		numverticies(NumVerticies),
		texture(Texture)
	{
	}
	GLuint offset;
	GLuint numverticies;
	GLuint texture;
};
class SpriteBatch
{
public:
	SpriteBatch();
	~SpriteBatch();

	void init();

	void begin(GlyphSortType sortType = GlyphSortType::TEXTURE);
	void end();

	void draw(const glm::vec4& destRect, const glm::vec4& uvRect, GLuint texture, float depth, Color color);

	void renderBatch();



private:
	void createRenderBatches();
	void createVertexArray();
	void sortGlyphs();

	static bool compareFrontToBack(Glyph*a, Glyph* b);
	static bool compareBackToFront(Glyph*a, Glyph* b);
	static bool compareTexture(Glyph*a, Glyph* b);




	GlyphSortType _sortType;
	GLuint _vbo;
	GLuint _vao;
	std::vector<Glyph*> _glyphs;
	std::vector<RenderBatch> _renderBatches;

};
}
