#pragma once
#include<GLM/glm.hpp>
#include<GLM/gtc/matrix_transform.hpp>
#include<GLFW\glfw3.h>
class MouseCamera
{
public:
	MouseCamera();
	~MouseCamera();
	 float currentFrame;
	 float lastFrame;
	 double lastX;
	 double lastY;
	 double dx;
	 double dy;
	 bool first;

	//static void key_callback(GLFWwindow* window,int key,int scancode,int action,int model);
	//static void mouse_button_callback(GLFWwindow* window, int button, int action, int model);
	//static void mouse_movement_callback(GLFWwindow* window, double Xpos, double Ypos);
	glm::mat4 GetViewMatrix();
	glm::mat4 GetProjectionMatrix();
	//void run();
	//void do_action();
	void SetCamera(glm::vec3 eye,glm::vec3 center,glm::vec3 up);
	void SetViewMatrix();
	void SetProjectonMatrix();
	float GetDistance();

	void roll(float angle);
	void yaw(float angle);
	void pitch(float angle);
	void slide(float du, float dv, float dn);
	void setShape(float viewAngle, float aspect, float near, float far);

	void RotateX(float angle);

	void RotateY(float angle);

private:
	glm::vec3 eye, center, up,front;
	glm::vec3 n, u, v;
	float viewAngle, aspect, Znear, Zfar;
	glm::mat4 viewMatrix;
	glm::mat4 projectionMatrix;
};

