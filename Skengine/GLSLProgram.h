#pragma once
#include <string>
#include <GL/glew.h>
namespace Skengine{
	class GLSLProgram
	{
	public:
		GLSLProgram();
		~GLSLProgram();

		void compileShaders(const std::string& vertexShaderFilePath, const std::string& fragmentShaderFilePath);
		void addAttrib(const std::string& attribName);
		void linkShaders();
		GLint getUniformLocation(const std::string& uniformName);
		void use();
		void unuse();

	private:

		int _numAttrib;
		void compileShader(const std::string& filePath, GLuint id);
		GLuint _programID;

		GLuint _vertexShaderID;

		GLuint _fragmentShaderID;
	};

}