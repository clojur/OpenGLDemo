#include "Shader.h"

Shader::Shader(const GLchar * vertexShaderPath, const GLchar * fragShaderPath)
{
	std::ifstream vf,ff;
	std::stringstream vertexString, fragString;
	vertexString.exceptions(std::ifstream::badbit);
	fragString.exceptions(std::ifstream::badbit);
	try
	{
		vf.open(vertexShaderPath);
		ff.open(fragShaderPath);
		vertexString << vf.rdbuf();
		fragString << ff.rdbuf();
		vf.close();
		ff.close();
	}
	catch (std::ifstream::failure e)
	{
		std::cout << "ERROR::SHADER::Open File Faile!" << std::endl;
	}
	std::string VSstring = vertexString.str();
	std::string FSstring = fragString.str();
	const GLchar* vertexShaderCode = VSstring.c_str();
	const GLchar* fragShaderCode = FSstring.c_str();
	GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
	GLuint fragShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(vertexShader, 1, &vertexShaderCode, nullptr);
	glShaderSource(fragShader, 1, &fragShaderCode, nullptr);
	GLint success;
	GLchar infoLog[512];
	glCompileShader(vertexShader);
	glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(vertexShader, sizeof(infoLog), nullptr, infoLog);
		std::cout << "ERROR::SHADER::VERTEX::COMPILATION::FAILED" <<infoLog<< std::endl;
		getchar();
	}
	glCompileShader(fragShader);
	glGetShaderiv(fragShader, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(fragShader, sizeof(infoLog), nullptr, infoLog);
		std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION::FAILED" << infoLog << std::endl;
		getchar();
	}
	this->shaderProgram = glCreateProgram();
	glAttachShader(this->shaderProgram, vertexShader);
	glAttachShader(this->shaderProgram, fragShader);
	glLinkProgram(this->shaderProgram);
	glGetProgramiv(this->shaderProgram, GL_LINK_STATUS, &success);
	if (!success)
	{
		glGetProgramInfoLog(this->shaderProgram, sizeof(infoLog), nullptr, infoLog);
		std::cout << "ERROR::SHADER::PROGRAM::COMPILATION::FAILED" << infoLog << std::endl;
		getchar();
	}
	glDeleteShader(vertexShader);
	glDeleteShader(fragShader);
}

Shader::~Shader()
{
}

void Shader::UseShaderProgram()
{
	glUseProgram(this->shaderProgram);
}
