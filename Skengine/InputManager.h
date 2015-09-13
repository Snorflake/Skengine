#pragma once
#include <unordered_map>
#include "BitVec.h"
#include <glm\glm.hpp>
namespace Skengine
{
	class InputManager
	{
	public:
		InputManager();
		~InputManager();

		void pressKey(unsigned int keyID);
		void releaseKey(unsigned int keyID);

		bool isKeyPressed(unsigned int keyID);

		void setMouseCoords(float x, float y);

		glm::vec2 getMouseCoords() const { return _mouseCoords;  }

	private:
		std::unordered_map<unsigned int, char> _keyMap;
		glm::vec2 _mouseCoords;
		BitVec _bitVec;
	};

}