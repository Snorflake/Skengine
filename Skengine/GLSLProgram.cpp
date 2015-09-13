#include "GLSLProgram.h"
#include "Errors.h"

#include <fstream>
#include <vector>

namespace Skengine{
	GLSLProgram::GLSLProgram() : _programID(0), _vertexShaderID(0), _fragmentShaderID(0), _numAttrib(0)
	{
	}


	GLSLProgram::~GLSLProgram()
	{
	}

	void GLSLProgram::compileShaders(const std::string& vertexShaderFilePath, const std::string& fragmentShaderFilePath)
	{
		_programID = glCreateProgram();
		_vertexShaderID = glCreateShader(GL_VERTEX_SHADER);
		if (!_vertexShaderID)
			fatalError("Vertex Shader failed to be created!");

		_fragmentShaderID = glCreateShader(GL_FRAGMENT_SHADER);
		if (!_fragmentShaderID)
			fatalError("Fragment Shader failed to be created!");

		compileShader(vertexShaderFilePath, _vertexShaderID);
		compileShader(fragmentShaderFilePath, _fragmentShaderID);

	}

	void GLSLProgram::use()
	{
		glUseProgram(_programID);
		for (int i = 0; i < _numAttrib; i++)
		{
			glEnableVertexAttribArray(i);
		}
	}

	GLint GLSLProgram::getUniformLocation(const std::string& uniformName)
	{
		GLint location = glGetUniformLocation(_programID, uniformName.c_str());
		if (location == GL_INVALID_INDEX)
			fatalError("Uniform " + uniformName + " not found in shader!");
		return location;

	}
	void GLSLProgram::unuse()
	{
		glUseProgram(0);
		for (int i = 0; i < _numAttrib; i++)
		{
			glDisableVertexAttribArray(i);
		}
	}
	void GLSLProgram::linkShaders()
	{

		glAttachShader(_programID, _vertexShaderID);
		glAttachShader(_programID, _fragmentShaderID);

		glLinkProgram(_programID);

		GLint isLinked = 0;
		glGetProgramiv(_programID, GL_LINK_STATUS, &isLinked);
		if (isLinked == GL_FALSE)
		{
			GLint maxLength = 0;
			glGetProgramiv(_programID, GL_INFO_LOG_LENGTH, &maxLength);


			std::vector<char> errorLog(maxLength + 1);
			glGetProgramInfoLog(_programID, maxLength, &maxLength, &errorLog[0]);

			glDeleteProgram(_programID);

			glDeleteShader(_vertexShaderID);
			glDeleteShader(_fragmentShaderID);
			printf("%s\n", &(errorLog[0]));
			fatalError("Shaders failed to link!");
		}

		glDetachShader(_programID, _vertexShaderID);
		glDetachShader(_programID, _fragmentShaderID);
		glDeleteShader(_vertexShaderID);
		glDeleteShader(_fragmentShaderID);
	}
	void GLSLProgram::addAttrib(const std::string& attribName)
	{
		glBindAttribLocation(_programID, _numAttrib++, attribName.c_str());
	}
	void GLSLProgram::compileShader(const std::string& filePath, GLuint id){
		std::ifstream vertexFile(filePath);
		if (vertexFile.fail())
		{
			fatalError("Failed to open " + filePath);
			perror(filePath.c_str());
		}
		std::string fileContents = "";
		std::string line;
		while (std::getline(vertexFile, line))
		{
			fileContents += line + "\n";
		}
		vertexFile.close();

		const char* contPtr = fileContents.c_str();
		glShaderSource(id, 1, &contPtr, nullptr);

		glCompileShader(id);

		GLint success = 0;
		glGetShaderiv(id, GL_COMPILE_STATUS, &success);
		if (success == GL_FALSE)
		{
			GLint maxLength = 0;
			glGetShaderiv(id, GL_INFO_LOG_LENGTH, &maxLength);

			std::vector<char> errorLog(maxLength);
			glGetShaderInfoLog(id, maxLength, &maxLength, &errorLog[0]);
			glDeleteShader(id);
			printf("%s\n", &(errorLog[0]));
			fatalError("Shader" + filePath + " failed to compiler");
		}
	}
}