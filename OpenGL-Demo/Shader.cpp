#include "Shader.h"



Shader::Shader(const GLchar* vertexFilePath, const GLchar* fragmentFilePath)
{
	std::string vertexShaderCode;
	std::string fragmentShaderCode;

	std::ifstream vertexShaderFile;
	std::ifstream fragmentShaderFile;

	std::stringstream vs;
	std::stringstream fs;
	try {
		vertexShaderFile.open(vertexFilePath);
		fragmentShaderFile.open(fragmentFilePath);
		vs << vertexShaderFile.rdbuf();
		fs << fragmentShaderFile.rdbuf();
		vertexShaderFile.close();
		fragmentShaderFile.close();
	}
	catch (std::exception e) {
		std::cout << "Read file ERROR" << std::endl;
	}
	vertexShaderCode = vs.str();
	fragmentShaderCode = fs.str();

	const GLchar *vc = vertexShaderCode.c_str();
	GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShader, 1, &vc, NULL);
	glCompileShader(vertexShader);
	GLint success;
	GLchar infoLog[512];
	glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(vertexShader, sizeof(infoLog), NULL,infoLog);
		std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED" << infoLog << std::endl;
	}
	
	const GLchar *fc = fragmentShaderCode.c_str();
	GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader, 1, &fc, NULL);
	glCompileShader(fragmentShader);
	glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(fragmentShader, sizeof(infoLog), NULL, infoLog);
		std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED" << infoLog << std::endl;
	}

	this->shaderProgram = glCreateProgram();
	glAttachShader(this->shaderProgram, vertexShader);
	glAttachShader(this->shaderProgram, fragmentShader);
	glLinkProgram(this->shaderProgram);
	glGetProgramiv(this->shaderProgram, GL_LINK_STATUS, &success);
	if (!success)
	{
		glGetProgramInfoLog(this->shaderProgram, sizeof(infoLog), NULL, infoLog);
		std::cout << "ERROR::PROGRAM::LINK_FAILED" <<infoLog<< std::endl;
	}
	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);
}


Shader::~Shader()
{
}

void Shader::run()
{
	glUseProgram(this->shaderProgram);
}
