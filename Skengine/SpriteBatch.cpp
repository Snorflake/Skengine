#include "SpriteBatch.h"
#include <algorithm>
namespace Skengine{


SpriteBatch::SpriteBatch() : 
	_vbo(0),
	_vao(0)
{
}


SpriteBatch::~SpriteBatch()
{
}


void SpriteBatch::init()
{
	createVertexArray();
}

void SpriteBatch::begin(GlyphSortType sortType /* GlyphSortType::TEXTURE*/)
{
	//honestly no clue what's even going on
	_sortType = sortType;
	_renderBatches.clear();
	for (int i = 0; i < _glyphs.size(); i++)
	{
		delete _glyphs[i]; //prevents memory leaks
	}
	_glyphs.clear();
}

void SpriteBatch::end()
{
	sortGlyphs();
	createRenderBatches();
}

void SpriteBatch::draw(const glm::vec4& destRect, const glm::vec4& uvRect, GLuint texture, float depth, Color color)
{ //This works because it draws the level. And everything else ive tested.
	//has it ever drawn more than 1 sprite at a time
	//It doesn't bug. wat
	//i havent encountered bugs
	//but have you been able to drawn two different sprites?
	//well... idk
	// but it doesnt matter
	// its a different batch to the level.
	//try removing the level drawing ad see what happens
	Glyph* newGlyph = new Glyph();
	newGlyph->texture = texture;
	newGlyph->depth = depth;

	newGlyph->topLeft.color = color;
	newGlyph->topLeft.setPosition(destRect.x, destRect.y + destRect.w);
	newGlyph->topLeft.setUV(uvRect.x, uvRect.y + uvRect.w);
	newGlyph->topLeft.color = color;

	newGlyph->bottomLeft.setPosition(destRect.x, destRect.y);
	newGlyph->bottomLeft.setUV(uvRect.x, uvRect.y );
	newGlyph->bottomLeft.color = color;

	newGlyph->bottomRight.setPosition(destRect.x + destRect.z, destRect.y);
	newGlyph->bottomRight.setUV(uvRect.x + uvRect.z, uvRect.y);
	newGlyph->bottomRight.color = color;

	newGlyph->topRight.setPosition(destRect.x + destRect.z, destRect.y + destRect.w);
	newGlyph->topRight.setUV(uvRect.x + uvRect.z, uvRect.y + uvRect.w);
	newGlyph->topRight.color = color;

	_glyphs.push_back(newGlyph);
	
}

void SpriteBatch::renderBatch()
{
	//glBindVertexArray(_vao);
	for (int i = 0; i < _renderBatches.size(); i++)
	{
		glBindTexture(GL_TEXTURE_2D, _renderBatches[i].texture);
		glDrawArrays(GL_TRIANGLES, _renderBatches[i].offset, _renderBatches[i].numverticies);
	}
	//glBindVertexArray(0);
}

void SpriteBatch::createRenderBatches()
{
	std::vector<Vertex> verticies;
	verticies.resize(_glyphs.size() * 6);
	if (_glyphs.empty())
	{
		return;
	}
	int offset = 0;
	int cv = 0; //current vertex
	_renderBatches.emplace_back(offset, 6, _glyphs[0]->texture);
	verticies[cv++] = _glyphs[0]->topLeft;
	verticies[cv++] = _glyphs[0]->bottomLeft;
	verticies[cv++] = _glyphs[0]->bottomRight;
	verticies[cv++] = _glyphs[0]->bottomRight;
	verticies[cv++] = _glyphs[0]->topRight;
	verticies[cv++] = _glyphs[0]->topLeft;
	offset += 6;

	for (int cg = 1; cg < _glyphs.size(); cg++)
	{
		if (_glyphs[cg]->texture != _glyphs[cg - 1]->texture)
			_renderBatches.emplace_back(offset, 6, _glyphs[0]->texture);
		else
			_renderBatches.back().numverticies += 6;
		verticies[cv++] = _glyphs[cg]->topLeft;
		verticies[cv++] = _glyphs[cg]->bottomLeft;
		verticies[cv++] = _glyphs[cg]->bottomRight;
		verticies[cv++] = _glyphs[cg]->bottomRight;
		verticies[cv++] = _glyphs[cg]->topRight;
		verticies[cv++] = _glyphs[cg]->topLeft;
		offset += 6;
	}

	glBindBuffer(GL_ARRAY_BUFFER, _vbo);

	glBufferData(GL_ARRAY_BUFFER, verticies.size() * sizeof(Vertex), nullptr, GL_DYNAMIC_DRAW);
	glBufferSubData(GL_ARRAY_BUFFER, 0, verticies.size() * sizeof(Vertex), verticies.data());

	glBindBuffer(GL_ARRAY_BUFFER, 0);
}
void SpriteBatch::createVertexArray()
{
	if (_vao == 0)
		glGenVertexArrays(1, &_vao);

	if (_vbo == 0)
		glGenBuffers(1, &_vbo);

	glBindBuffer(GL_ARRAY_BUFFER, _vbo);

	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
	glEnableVertexAttribArray(2);

	//Position attrib pointer
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, position));
	//Color attrib pointer
	glVertexAttribPointer(1, 4, GL_UNSIGNED_BYTE, GL_TRUE, sizeof(Vertex), (void*)offsetof(Vertex, color));
	//UV Atrrib pointer
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, uv));

	glBindVertexArray(0);


}

void SpriteBatch::sortGlyphs()
{
	switch (_sortType)
	{
		case GlyphSortType::BACK_TO_FRONT:
			std::stable_sort(_glyphs.begin(), _glyphs.end(), compareBackToFront);
			break;
		case GlyphSortType::FRONT_TO_BACK:
			std::stable_sort(_glyphs.begin(), _glyphs.end(), compareFrontToBack);
			break;
		case GlyphSortType::TEXTURE:
			std::stable_sort(_glyphs.begin(), _glyphs.end(), compareTexture);
			break;
	}
}

bool SpriteBatch::compareFrontToBack(Glyph*a, Glyph* b)
{
	return a->depth < b->depth;
}
bool SpriteBatch::compareBackToFront(Glyph*a, Glyph* b)
{

	return a->depth > b->depth;
}
bool SpriteBatch::compareTexture(Glyph*a, Glyph* b)
{
	return a->texture < b->texture;
}
}