#pragma once
#include<GLEW\glew.h>
#include<iostream>
#include<fstream>
#include<sstream>
class Shader
{
public:
	Shader(const GLchar* vertexShaderPath,const GLchar* fragShaderPath);
	~Shader();
	void UseShaderProgram();
	GLuint shaderProgram;
};

