#include "Camera2D.h"

namespace Skengine{
	Camera2D::Camera2D() :
		_position(0.f, 0.f),
		_cameraMatrix(1.f),
		_scale(1.f),
		_needsMatrixUpdate(true),
		_screenWidth(800),
		_screenHeight(600),
		_orthoMatrix(1.f)
	{
	}


	Camera2D::~Camera2D()
	{
	}

	void Camera2D::update()
	{
		if (_needsMatrixUpdate)
		{
			glm::vec3 translate(-_position.x + _screenWidth / 2, -_position.y + _screenHeight / 2, 0.f);
			_cameraMatrix = glm::translate(_orthoMatrix, translate);

			glm::vec3 scale(_scale, _scale, 0.f);
			_cameraMatrix = glm::scale(glm::mat4(1.f), scale) * _cameraMatrix;

			_needsMatrixUpdate = false;
		}
	}
	glm::vec2 Camera2D::screenToWorld(glm::vec2 screenCoords)
	{
		//invert y
		screenCoords.y = _screenHeight - screenCoords.y;
		//0 is center
		screenCoords -= glm::vec2(_screenWidth / 2, _screenHeight / 2);
		//scale the coords
		screenCoords /= _scale;
		//translate with camera keksition
		screenCoords += _position;
		return screenCoords;
	}
	void Camera2D::init(int screenWidth, int screenHeight)
	{
		_screenWidth = screenWidth;
		_screenHeight = screenHeight;
		_orthoMatrix = glm::ortho(0.f, (float)_screenWidth, 0.f, (float)_screenHeight);
	}
}