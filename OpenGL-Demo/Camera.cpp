#include "Camera.h"

bool Camera::keys[512] = { false };
bool Camera::first = true;
double Camera::yaw = -90.0;
double Camera::pitch = 0.0;
double Camera::old_x = 0.0;
double Camera::old_y = 0.0;
glm::vec3 Camera::camFront=glm::vec3(0.0, 0.0, -1.0);
Camera::Camera(GLFWwindow * window)
{
	this->window = window;
	this->camPos = glm::vec3(0.0, 0.0, 3.0);
	
	this->camUp = glm::vec3(0.0,1.0,0.0);
	this->view = glm::lookAt(camPos, camPos + camFront, camUp);
	lastFrame = 0.0;
	currentFrame = 0.0;
	first = true;
}

Camera::~Camera()
{
}

void Camera::run()
{
	glfwSetKeyCallback(window, Key_CallBack);
	glfwSetCursorPosCallback(window, Mouse_CallBack);
	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
}
void Camera::Key_CallBack(GLFWwindow * window, int key, int scancode, int action, int model)
{
	if (GLFW_PRESS == action)
		Camera::keys[key] = true;
	if (GLFW_RELEASE == action)
		Camera::keys[key] = false;	
}

void Camera::Mouse_CallBack(GLFWwindow * window, double Xpos, double Ypos)
{
	if (Camera::first)
	{
		Camera::old_x = Xpos;
		Camera::old_y = Ypos;
		Camera::first = false;
	}
	double sensitivity = 0.05;
	double xoffset = Xpos - old_x;
	double yoffset = old_y - Ypos;
	old_x = Xpos;
	old_y = Ypos;
	Camera::yaw+=xoffset * sensitivity;
	Camera::pitch+=yoffset * sensitivity;
	if (Camera::pitch > 89.0)
		Camera::pitch = 89.0;
	if (Camera::yaw >= 360.0)
		Camera::yaw = 0.0;
	glm::vec3 front;
	front.x = cos(glm::radians(yaw))*cos(glm::radians(pitch));
	front.y = sin(glm::radians(pitch));
	front.z = sin(glm::radians(yaw));
	Camera::camFront = glm::normalize(front);
}

void Camera::do_movement()
{
	camSpeed = (currentFrame - lastFrame);
	if (keys[GLFW_KEY_W])
		camPos +=camFront*camSpeed;
	if (keys[GLFW_KEY_S])
		camPos -= camFront*camSpeed;
	if (keys[GLFW_KEY_A])
		camPos -= glm::normalize(glm::cross(camFront, camUp))*camSpeed;
	if(keys[GLFW_KEY_D])
		camPos+= glm::normalize(glm::cross(camFront, camUp))*camSpeed;
	if (keys[GLFW_KEY_ESCAPE])
		glfwSetWindowShouldClose(window,GL_TRUE);
}

glm::mat4 Camera::GetViewMatrix()
{
	view = glm::lookAt(camPos, camPos+Camera::camFront, camUp);

	return view;
}

