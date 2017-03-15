#include "MouseCamera.h"

#include <iostream>

MouseCamera::MouseCamera()
{
	front = glm::vec3(0.0, 0.0, -1.0);
	eye = glm::vec3(0.0, 0.0, 3.0);
	center = glm::vec3(0.0,0.0,0.0);
	up = glm::vec3(0.0, 1.0,0.0);
	

	currentFrame = 0.0;
	lastFrame = 0.0;
	lastX = 0.0;
	lastY = 0.0;
	dx = 0.0;
	dy = 0.0;
	first = true;
	
	SetCamera(eye, center, up);
}


MouseCamera::~MouseCamera()
{
}

//void MouseCamera::key_callback(GLFWwindow * window, int key, int scancode, int action, int model)
//{
//	if (action == GLFW_PRESS)
//		keys[key] = true;
//	if (action == GLFW_RELEASE)
//		keys[key] = false;
//}
//
//void MouseCamera::mouse_button_callback(GLFWwindow * window, int button, int action, int model)
//{
//	if (action == GLFW_PRESS)
//		mouses[button] = true;
//	if (action == GLFW_RELEASE)
//		mouses[button] = false;
//}

//void MouseCamera::mouse_movement_callback(GLFWwindow * window, double Xpos, double Ypos)
//{
//	if (first)
//	{
//		lastX = Xpos;
//		lastY = Ypos;
//		first = false;
//	}
//	dx = Xpos - lastX;
//	dy = lastY - Ypos;
//	lastX = Xpos;
//	lastY = Ypos;
//}

glm::mat4 MouseCamera::GetViewMatrix()
{
	return viewMatrix;
}

glm::mat4 MouseCamera::GetProjectionMatrix()
{
	return projectionMatrix;
}

//void MouseCamera::do_action()
//{
//	float camSpeed = currentFrame - lastFrame;
//	if (keys[GLFW_KEY_ESCAPE])
//		glfwSetWindowShouldClose(m_window, GL_TRUE);
//	if (keys[GLFW_KEY_W])
//		eye += front*camSpeed;
//	if (keys[GLFW_KEY_S])
//		eye -= front*camSpeed;
//	if (keys[GLFW_KEY_A])
//		eye -= glm::normalize(glm::cross(front,up))*camSpeed;
//	if(keys[GLFW_KEY_D])
//		eye+= glm::normalize(glm::cross(front,up))*camSpeed;
//	//if (mouses[GLFW_MOUSE_BUTTON_RIGHT])
//	//{
//	//	std::cout << dy << std::endl;
//	//	roll(dy);
//	//}
//	//if (mouses[GLFW_MOUSE_BUTTON_LEFT])
//	//	;
//	//if (mouses[GLFW_MOUSE_BUTTON_MIDDLE])
//	//	slide(-dx*0.001, dy*0.001, 0.0);
//
//	SetCamera(eye, eye + front, up);
//}

void MouseCamera::SetCamera(glm::vec3 eye, glm::vec3 center, glm::vec3 up)
{
	this->eye = eye;
	this->center = center;
	this->up = up;

	n = glm::normalize(this->eye - this->center);
	u = glm::normalize(glm::cross(up, n));
	v = glm::normalize(glm::cross(n, u));
	this->SetViewMatrix();
}

void MouseCamera::SetViewMatrix()
{
	
	viewMatrix[0][0] = u.x;
	viewMatrix[0][1] = u.y;
	viewMatrix[0][2] = u.z;
	viewMatrix[1][0] = v.x;
	viewMatrix[1][1] = v.y;
	viewMatrix[1][2] = v.z;
	viewMatrix[2][0] = n.x;
	viewMatrix[2][1] = n.y;
	viewMatrix[2][2] = n.z;
	viewMatrix[3][0] =-glm::dot(eye,u) ;
	viewMatrix[3][1] =-glm::dot(eye,v) ;
	viewMatrix[3][2] =-glm::dot(eye,n) ;
	//viewMatrix[3][0] = -eye.x;
	//viewMatrix[3][1] = -eye.y;
	//viewMatrix[3][2] = -eye.x;
}

void MouseCamera::SetProjectonMatrix()
{
}

float MouseCamera::GetDistance()
{
	return glm::length(this->center-this->eye);
}

void MouseCamera::roll(float angle)
{
	float cs = cos(glm::radians(angle));
	float sn = sin(glm::radians(angle));
	glm::vec3 t(u);
	glm::vec3 s(v);
	this->u = cs*t - sn*s;
	this->v = sn*t + cs*s;
	this->SetViewMatrix();
}

void MouseCamera::yaw(float angle)
{
	float cs = cos(glm::radians(angle));
	float sn = sin(glm::radians(angle));
	this->n =cs*n-sn*u ;
	this->u =sn*n+cs*u ;
	this->SetViewMatrix();
}

void MouseCamera::pitch(float angle)
{
	float cs = cos(glm::radians(angle));
	float sn = sin(glm::radians(angle));
	this->v =cs*v-sn*n ;
	this->n =sn*v+cs*n ;
	this->SetViewMatrix();
}

/*摄像机绕三个轴平移的计算函数*/
void MouseCamera::slide(float du, float dv, float dn)
{
	this->eye += du*u+dv*v+dn*n;
	this->center+= du*u + dv*v + dn*n;
	//glm::vec3 newDir = glm::normalize(eye - center);
	//glm::vec3 newRigth = glm::normalize(glm::cross(v, newDir));
	//glm::vec3 newUp = glm::normalize(glm::cross(newDir, newRigth));
	SetCamera(eye, center, up);
}

void MouseCamera::setShape(float viewAngle, float aspect, float near, float far)
{
	this->projectionMatrix = glm::perspective(viewAngle, aspect, near, far);
}

void MouseCamera::RotateX(float angle)
{
	float d = this->GetDistance();
	int cnt = 100;
	float theta = angle / cnt;
	float slide_d = -2 * d*sin(theta*3.14159265 / 360);
	yaw(theta / 2);
	for (; cnt != 0; --cnt)
	{
		slide(slide_d, 0, 0);
		yaw(theta);
	}
	yaw(-theta / 2);
}

void MouseCamera::RotateY(float angle)
{
	float d = GetDistance();
	int cnt = 100;
	float theta = angle / cnt;
	float slide_d = 2 * d*sin(theta*3.14159265 / 360);
	pitch(theta / 2);
	for (; cnt != 0; --cnt)
	{
		slide(0, slide_d, 0);
		pitch(theta);
	}
	pitch(-theta / 2);
}
