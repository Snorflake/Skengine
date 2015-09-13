#pragma once
#include <glm\glm.hpp>
#include <glm\gtc\matrix_transform.hpp>

namespace Skengine{
	class Camera2D
	{
	public:
		Camera2D();
		~Camera2D();

		void init(int screenWidth, int screenHeight);

		void update();

		glm::vec2 screenToWorld(glm::vec2 screenCoords);

		//Setters
		void setPosition(const glm::vec2& position)	{ _position = position; _needsMatrixUpdate = true; }
		void setScale(float scale) { _scale = scale; _needsMatrixUpdate = true; }

		//Getters
		glm::vec2 getPosition()	{ return _position; }
		float getScale() { return _scale; }
		glm::mat4 getCameraMatrix() { return _cameraMatrix; }

	private:
		int _screenWidth, _screenHeight;
		bool _needsMatrixUpdate;
		float _scale;
		glm::vec2 _position;
		glm::mat4 _cameraMatrix;
		glm::mat4 _orthoMatrix;
	};
}
