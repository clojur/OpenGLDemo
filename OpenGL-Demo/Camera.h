#pragma once
#include<glm/glm.hpp>
#include<glm/gtc/matrix_transform.hpp>
#include<glm/gtc/type_ptr.hpp>

#include<glfw/glfw3.h>
class Camera
{
public:
	Camera(GLFWwindow* window);
	~Camera();
public:
	GLFWwindow *window;
	glm::mat4 view;
	static bool keys[512];
	glm::vec3 camPos;
	static glm::vec3 camFront;
	glm::vec3 camUp;
	float camSpeed;
	static double yaw;
	static double pitch;
	double lastFrame;
	double currentFrame;
	static double old_x;
	static double old_y;
	static bool first;

	void run();
	static void Key_CallBack(GLFWwindow* window,int key,int scancode,int action,int model);
	static void  Mouse_CallBack(GLFWwindow* window,double Xpos,double Ypos);
	void do_movement();
	glm::mat4 GetViewMatrix();
};

