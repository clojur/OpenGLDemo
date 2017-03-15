#pragma once
#include<GLEW/glew.h>
#include<sstream>
#include<fstream>
#include<iostream>
class Shader
{
public:
	Shader(const GLchar* vertexFilePath,const GLchar* fragmentFilePath);
	~Shader();
	void run();
	GLuint shaderProgram;
};

