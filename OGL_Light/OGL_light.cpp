#include<windows.h>
#include<GLEW\glew.h>
#include<GLFW\glfw3.h>

#include<GLM/glm.hpp>
#include<GLM/gtc/matrix_transform.hpp>
#include<GLM/gtc/type_ptr.hpp>
#include<iostream>

#include"Shader.h"
#include"Camera.h"

Camera camera(glm::vec3(0.0f,0.0f,3.0f));

bool flag[512] = { false };
bool keys[512] = { false };
float oldx = 0.0;
float oldy = 0.0;
float dx = 0.0;
float dy = 0.0;
float deltaTime = 0.0;
float currentFrame = 0.0;
float lastFrame = 0.0;
bool first = true;

void key_callback(GLFWwindow* window, int key, int scancode, int action, int model)
{
	if (key >= 0 && key < 512)
	{
		if (action == GLFW_PRESS)
			keys[key] = true;
		else if (action == GLFW_RELEASE)
			keys[key] = false;
		else
			;
		if (action==GLFW_PRESS&&key==GLFW_KEY_ESCAPE)
			glfwSetWindowShouldClose(window, GL_TRUE);
	}
}
void mouse_movent(GLFWwindow* window, double Xpos, double Ypos)
{
	if (first)
	{
		oldx = Xpos;
		oldy = Ypos;
		first = false;
	}
	dx = Xpos - oldx;
	dy = oldy - Ypos;
	oldx = Xpos;
	oldy = Ypos;
	camera.ProcessMouseMovement(dx, dy);
}
void mouse_callback(GLFWwindow* window, int button, int action, int model)
{
	//if (action == GLFW_PRESS)
	//	flag[button] = true;
	//if (action == GLFW_RELEASE)
	//	flag[button]=false;
	if(action == GLFW_PRESS&&button==GLFW_MOUSE_BUTTON_LEFT)
		glfwSetCursorPosCallback(window, mouse_movent);
	if (action == GLFW_RELEASE&&button == GLFW_MOUSE_BUTTON_LEFT)
		glfwSetCursorPosCallback(window, NULL);
}

void do_action()
{
	if (keys[GLFW_KEY_W])
		camera.ProcessKeyBoard(CamAction::FORWARD, deltaTime);
	if (keys[GLFW_KEY_S])
		camera.ProcessKeyBoard(CamAction::BACK, deltaTime);
	if (keys[GLFW_KEY_A])
		camera.ProcessKeyBoard(CamAction::LEFT, deltaTime);
	if (keys[GLFW_KEY_D])
		camera.ProcessKeyBoard(CamAction::RIGHT, deltaTime);
}

GLfloat vertexArray[] = {
	-0.5f,-0.5f,0.5f, 0.0,0.0,1.0,//前
	0.5f,-0.5f,0.5f, 0.0,0.0,1.0,
	0.5f,0.5f,0.5f, 0.0,0.0,1.0,
	-0.5f,0.5f,0.5f,0.0,0.0,1.0,

	-0.5f,-0.5f,-0.5f, 0.0,0.0,-1.0,//后
	0.5f,-0.5f,-0.5f, 0.0,0.0,-1.0,
	0.5f,0.5f,-0.5f, 0.0,0.0,-1.0,
	-0.5f,0.5f,-0.5f, 0.0,0.0,-1.0,

	-0.5f,-0.5f,0.5f,-1.0,0.0,0.0,//左
	-0.5f,0.5f,0.5f,-1.0,0.0,0.0,
	-0.5f,0.5f,-0.5f,-1.0,0.0,0.0,
	-0.5f,-0.5f,-0.5f,-1.0,0.0,0.0,

	0.5f,-0.5f,0.5f,1.0,0.0,0.0,//右
	0.5f,0.5f,0.5f,1.0,0.0,0.0,
	0.5f,0.5f,-0.5f,1.0,0.0,0.0,
	0.5f,-0.5f,-0.5f,1.0,0.0,0.0,

	-0.5f,0.5f,0.5f,0.0,1.0,0.0,//上
	0.5f,0.5f,0.5f,0.0,1.0,0.0,
	0.5f,0.5f,-0.5f,0.0,1.0,0.0,
	-0.5f,0.5f,-0.5f,0.0,1.0,0.0,

	-0.5f,-0.5f,0.5f,0.0,-1.0,0.0,//下
	0.5f,-0.5f,0.5f,0.0,-1.0,0.0,
	0.5f,-0.5f,-0.5f,0.0,-1.0,0.0,
	-0.5f,-0.5f,-0.5f,0.0,-1.0,0.0
};
GLuint vertexIndex[] = {
	0,1,2,2,3,0,
	4,5,6,6,7,4,
	8,9,10,10,11,8,
	12,15,14,14,13,12,
	16,17,18,18,19,16,
	20,23,22,22,21,20
};

int main()
{
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

	GLFWwindow* window=glfwCreateWindow(800,600,"OGL_Light",nullptr,nullptr);

	if (!window)
	{
		std::cout << "Window Create Failed!" << std::endl;
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);

	glewExperimental = GL_TRUE;
	if (glewInit() != GLEW_OK)
	{
		std::cout << "GLEW Init Failed!" << std::endl;
		glfwTerminate();
		return -1;
	}
	glViewport(0, 0, 800, 600);
	GLuint ObjectVertexBuffers, ObjectVertexAttrib,IBO;
	glGenBuffers(1, &ObjectVertexBuffers);
	glBindBuffer(GL_ARRAY_BUFFER, ObjectVertexBuffers);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertexArray), vertexArray, GL_STATIC_DRAW);

	glGenVertexArrays(1, &ObjectVertexAttrib);
	glBindVertexArray(ObjectVertexAttrib);
	glGenBuffers(1, &IBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(vertexIndex), vertexIndex, GL_STATIC_DRAW);
	
	
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid*)0);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
	glEnableVertexAttribArray(1);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
	GLuint  LightVertexAttrib;
	glGenVertexArrays(1, &LightVertexAttrib);
	glBindVertexArray(LightVertexAttrib);
	glBindBuffer(GL_ARRAY_BUFFER,ObjectVertexBuffers);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBO);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (void*)0);
	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);

	glEnable(GL_DEPTH_TEST);
	Shader ModelShader("E:\\OSG\\OpenGL3.0_Test\\OpenGL-Demo\\OGL_Light\\shaderFile\\Objectvertex.vtxs","E:\\OSG\\OpenGL3.0_Test\\OpenGL-Demo\\OGL_Light\\shaderFile\\Objectfrag.frgs");
	Shader LightShader("E:\\OSG\\OpenGL3.0_Test\\OpenGL-Demo\\OGL_Light\\shaderFile\\Lightvertex.vtxs", "E:\\OSG\\OpenGL3.0_Test\\OpenGL-Demo\\OGL_Light\\shaderFile\\Lightfrag.frgs");
	//glfwSetMouseButtonCallback(window, mouse_callback);
	glfwSetKeyCallback(window, key_callback);
	glfwSetCursorPosCallback(window, mouse_movent);
	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
	while (!glfwWindowShouldClose(window))
	{
		currentFrame = glfwGetTime();
		deltaTime = currentFrame - lastFrame;
		glfwPollEvents();
		do_action();
		lastFrame = currentFrame;

		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		glm::mat4 Lightview;
		Lightview = glm::inverse(camera.GetViewMatrix());
		glm::vec3 lightPos(Lightview[3][0], Lightview[3][1], Lightview[3][2]);
		//glm::vec3 lightPos(0.0, 2.0, 5.0);
		ModelShader.UseShaderProgram();
		glUniform3f(glGetUniformLocation(ModelShader.shaderProgram, "ObjectColor"), 1.0f, 0.5f, 0.31f);
		glUniform3f(glGetUniformLocation(ModelShader.shaderProgram, "LightColor"), 1.0f, 1.0f, 1.0f);
		glUniform1f(glGetUniformLocation(ModelShader.shaderProgram, "AmbientStrength"), 0.3f);
		glUniform3f(glGetUniformLocation(ModelShader.shaderProgram, "lightPos"), lightPos.x, lightPos.y, lightPos.z);
		glUniform3f(glGetUniformLocation(ModelShader.shaderProgram, "viewPos"), camera.m_camPos.x, camera.m_camPos.y, camera.m_camPos.z);
		glm::mat4 view;
		view = camera.GetViewMatrix();
		//view = glm::lookAt(glm::vec3(0.0f, 0.0f, 10.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(glGetUniformLocation(ModelShader.shaderProgram, "view"), 1, GL_FALSE, glm::value_ptr(view));
		glm::mat4 model;
		model = glm::rotate(model, glm::radians(45.0f), glm::vec3(1.0, 1.0, 0.0));
		glUniformMatrix4fv(glGetUniformLocation(ModelShader.shaderProgram, "model"), 1, GL_FALSE, glm::value_ptr(model));
		glm::mat4 projection;
		projection = glm::perspective(45.0f, 800.0f / 600.0f, 0.1f, 100.0f);
		glUniformMatrix4fv(glGetUniformLocation(ModelShader.shaderProgram, "projection"), 1, GL_FALSE, glm::value_ptr(projection));
		glBindVertexArray(ObjectVertexAttrib);
		glDrawElements(GL_TRIANGLES, sizeof(vertexIndex) / sizeof(GLuint), GL_UNSIGNED_INT, nullptr);
		glBindVertexArray(0);

		LightShader.UseShaderProgram();
		
		//Lightview = glm::lookAt(glm::vec3(0.0f, 0.0f, 3.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(glGetUniformLocation(LightShader.shaderProgram, "view"), 1, GL_FALSE, glm::value_ptr(Lightview));
		
		glm::mat4 Lightmodel;
		Lightmodel = glm::translate(Lightmodel, lightPos);
		Lightmodel = glm::scale(Lightmodel, glm::vec3(0.1));
		glUniformMatrix4fv(glGetUniformLocation(LightShader.shaderProgram, "model"), 1, GL_FALSE, glm::value_ptr(Lightmodel));
		glm::mat4 Lightprojection;
		Lightprojection = glm::perspective(45.0f, 800.0f / 600.0f, 0.1f, 100.0f);
		glUniformMatrix4fv(glGetUniformLocation(LightShader.shaderProgram, "projection"), 1, GL_FALSE, glm::value_ptr(Lightprojection));
		glBindVertexArray(LightVertexAttrib);
		glDrawElements(GL_TRIANGLES, sizeof(vertexIndex) / sizeof(GLuint), GL_UNSIGNED_INT, nullptr);
		glBindVertexArray(0);
		glfwSwapBuffers(window);
	}
	glDeleteBuffers(1, &ObjectVertexBuffers);
	glDeleteVertexArrays(1, &ObjectVertexAttrib);
	glDeleteVertexArrays(1, &LightVertexAttrib);
	glfwTerminate();
	return 0;
}