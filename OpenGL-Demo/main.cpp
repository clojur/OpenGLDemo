
#include<GLEW/glew.h>
#include<GLFW/glfw3.h>
#include<GLM/glm.hpp>
#include<GLM/gtc/matrix_transform.hpp>
#include<GLM/gtc/type_ptr.hpp>
#include<SOIL/SOIL.h>
#include<iostream>

#include"Shader.h"
#include"Camera.h"


int main()
{
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

	GLFWwindow *window=glfwCreateWindow(800,600,"MyOGL",NULL,NULL);
	if (!window)
	{
		std::cout << "ERROR::GLFW::WINDOW_INIT_FAILED" << std::endl;
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);

	glewExperimental = GL_TRUE;
	if (glewInit() != GLEW_OK)
	{
		std::cout << "ERROR::GLEW::INIT_FAILED" << std::endl;
		glfwTerminate();
		return -1;
	}
	glViewport(0, 0, 800, 600);
	//生成纹理对象1
	GLuint texture_1;
	glGenTextures(1, &texture_1);
	glBindTexture(GL_TEXTURE_2D, texture_1);
	//设置环绕
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	//设置过滤
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	//生成纹理
	int width, height;
	unsigned char* image1 = SOIL_load_image("E:\\OSG\\OpenGL\\picture\\container.jpg", &width, &height, 0, SOIL_LOAD_RGB);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0,GL_RGB,GL_UNSIGNED_BYTE, image1);
	glGenerateMipmap(GL_TEXTURE_2D);
	//释放图片和纹理
	SOIL_free_image_data(image1);
	glBindTexture(GL_TEXTURE_2D,0);
	//生成纹理对象2
	GLuint texture_2;
	glGenTextures(1, &texture_2);
	glBindTexture(GL_TEXTURE_2D, texture_2);
	//设置环绕
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T,GL_REPEAT);
	//设置过滤方式
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	//生成纹理
	unsigned char* image2 = SOIL_load_image("E:\\OSG\\OpenGL\\picture\\face.png", &width, &height, 0, SOIL_LOAD_RGB);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB,GL_UNSIGNED_BYTE,image2);
	glGenerateMipmap(GL_TEXTURE_2D);
	//释放资源
	SOIL_free_image_data(image2);
	glBindTexture(GL_TEXTURE_2D, 0);
	//设置顶点数组
	GLfloat vertexArray[] = {
		//位置			//颜色			//纹理
		0.5f,0.5f,-0.5f, 0.2f,0.0f,0.0f, 1.0f,1.0f,//后面
		0.5f,-0.5f,-0.5f, 0.0f,0.3f,0.0f, 1.0f,0.0f,
		-0.5f,-0.5f,-0.5f, 0.0f,0.2f,0.1f, 0.0f,0.0f,
		-0.5f,0.5f,-0.5f, 0.0f,0.0f,0.2f, 0.0f,1.0f,

		0.5f,0.5f,0.5f, 0.2f,0.0f,0.0f, 1.0f,1.0f,//前面
		0.5f,-0.5f,0.5f, 0.0f,0.3f,0.0f, 1.0f,0.0f,
		-0.5f,-0.5f,0.5f, 0.0f,0.2f,0.1f, 0.0f,0.0f,
		-0.5f,0.5f,0.5f, 0.0f,0.0f,0.2f, 0.0f,1.0f,

		-0.5f,-0.5f,-0.5f, 0.2f,0.0f,0.0f, 1.0f,1.0f,//底面
		-0.5f,-0.5f,0.5f, 0.0f,0.3f,0.0f, 1.0f,0.0f,
		0.5f,-0.5f,0.5f, 0.0f,0.2f,0.1f, 0.0f,0.0f,
		0.5f,-0.5f,-0.5f, 0.0f,0.0f,0.2f, 0.0f,1.0f,

		- 0.5f,0.5f,-0.5f, 0.2f,0.0f,0.0f, 1.0f,1.0f,//顶面
		-0.5f,0.5f,0.5f, 0.0f,0.3f,0.0f, 1.0f,0.0f,
		0.5f,0.5f,0.5f, 0.0f,0.2f,0.1f, 0.0f,0.0f,
		0.5f,0.5f,-0.5f, 0.0f,0.0f,0.2f, 0.0f,1.0f,

		0.5f,-0.5f,-0.5f, 0.2f,0.0f,0.0f, 1.0f,1.0f,//右面
		0.5f,0.5f,-0.5f, 0.0f,0.3f,0.0f, 1.0f,0.0f,
		0.5f,0.5f,0.5f, 0.0f,0.2f,0.1f, 0.0f,0.0f,
		0.5f,-0.5f,0.5f, 0.0f,0.0f,0.2f, 0.0f,1.0f,

		-0.5f,-0.5f,-0.5f, 0.2f,0.0f,0.0f, 1.0f,1.0f,//左面
		-0.5f,0.5f,-0.5f, 0.0f,0.3f,0.0f, 1.0f,0.0f,
		-0.5f,0.5f,0.5f, 0.0f,0.2f,0.1f, 0.0f,0.0f,
		-0.5f,-0.5f,0.5f, 0.0f,0.0f,0.2f, 0.0f,1.0f

	};
	//设置索引数组
	GLuint indexArray[] = {
		0,1,3,1,2,3,
		4,5,7,5,6,7,
		8,9,10,8,10,11,
		12,13,14,12,14,15,
		16,17,18,18,19,16,
		20,21,22,22,23,20
	};
	//设置每个箱子的位置
	glm::vec3 cubePosition[] = {
		glm::vec3(0.0f,0.0f,0.0f),
		glm::vec3(-3.0f,-2.0f,-5.0f),
		glm::vec3(1.0f,2.0f,-3.0f),
		glm::vec3(3.0f,-1.0f,-5.0f),
		glm::vec3(3.0f,2.0f,-3.0f),
		glm::vec3(-4.0f,2.0f,-4.0f),
		glm::vec3(-0.0f,-2.0f,-3.0f),
		glm::vec3(2.0f,-2.6f,-3.0f),
		glm::vec3(-2.0f,0.0f,-1.5f),
		glm::vec3(-6.0f,-4.0f,-8.0f),
	};
	//顶点属性
	GLuint VBO, VAO,EBO;
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);
	glGenVertexArrays(1, &VAO);

	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER,VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertexArray), vertexArray, GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indexArray), indexArray, GL_STATIC_DRAW);
	

	glVertexAttribPointer(0, 3, GL_FLOAT,GL_FALSE,8 * sizeof(GLfloat), (GLvoid*)0);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(1,3,GL_FLOAT,GL_FALSE,8*sizeof(GLfloat),(GLvoid*)(3*sizeof(GLfloat)));
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)(6 * sizeof(GLfloat)));
	glEnableVertexAttribArray(2);

	Shader Shader("E:\\OSG\\OpenGL3.0_Test\\ShaderFile\\vShader.vs","E:\\OSG\\OpenGL3.0_Test\\ShaderFile\\fShader.fs");
	Camera Manipulator(window);
	Manipulator.run();
	glEnable(GL_DEPTH_TEST);GLfloat r=0.0;
	while (!glfwWindowShouldClose(window))
	{
		Manipulator.currentFrame = glfwGetTime();
		glfwPollEvents();
		Manipulator.do_movement();
		Manipulator.lastFrame = Manipulator.currentFrame;
		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);

		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, texture_1);
		glUniform1i(glGetUniformLocation(Shader.shaderProgram, "Texture1"), 0);
		glActiveTexture(GL_TEXTURE1);
		glBindTexture(GL_TEXTURE_2D, texture_2);
		glUniform1i(glGetUniformLocation(Shader.shaderProgram, "Texture2"), 1);

		glm::mat4 model;
		
		glm::mat4 view;
		view = Manipulator.GetViewMatrix();
		glUniformMatrix4fv(glGetUniformLocation(Shader.shaderProgram, "view"), 1, GL_FALSE, glm::value_ptr(view));
		glm::mat4 perspective;
		perspective = glm::perspective(45.0f, 800.0f / 600.0f, 0.1f, 100.0f);
		glUniformMatrix4fv(glGetUniformLocation(Shader.shaderProgram, "projection"), 1, GL_FALSE, glm::value_ptr(perspective));
		
		Shader.run();
		glBindVertexArray(VAO);
		for (int i = 0; i < sizeof(cubePosition)/sizeof(glm::vec3); ++i)
		{
			glm::mat4 tran, rota;
			tran = glm::translate(tran, cubePosition[i]);
			rota = glm::rotate(rota, glm::radians(i*13.0f), glm::vec3(1.0f, 0.0f, 1.0f));
			model = tran*rota;
			glUniformMatrix4fv(glGetUniformLocation(Shader.shaderProgram, "model"), 1, GL_FALSE, glm::value_ptr(model));
			glDrawElements(GL_TRIANGLES, sizeof(indexArray)/4,GL_UNSIGNED_INT,nullptr);
		}
		glBindVertexArray(0);

		glfwSwapBuffers(window);
	}
	glDeleteBuffers(1,&VBO);
	glDeleteVertexArrays(1,&VAO);
	glDeleteBuffers(1, &EBO);
	glfwTerminate();
	return 0;
}