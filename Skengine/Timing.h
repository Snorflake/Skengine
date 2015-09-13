#pragma once

namespace Skengine
{
	class FpsLimiter
	{
	public:
		FpsLimiter();

		void init(float maxFPS);

		void setMaxFPS(float maxFPS);

		void begin();
		//will return current FPS
		float end();
	private:
		void calculateFPS();
		float _maxFPS;
		float _fps;
		float _frameTime;
		unsigned int _startTicks;
	};

}