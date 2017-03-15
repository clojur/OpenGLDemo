#include "Camera.h"



Camera::Camera()
{
	m_camFront = glm::vec3(0.0f,0.0f,-1.0f);
	m_camPos = glm::vec3(0.0f, 0.0f, 3.0f);
	m_camUp = glm::vec3(0.0f, 1.0f, 0.0f);
	m_camRight = glm::normalize(glm::cross(m_camFront, m_camUp));
	m_camSpeed = 3.0f;
	m_yaw = -90.0f;
	m_pitch = 0.0f;
}

Camera::Camera(const glm::vec3 & camPos):m_camPos(camPos)
{
	m_camFront = glm::vec3(0.0f, 0.0f, -1.0f);
	m_camUp = glm::vec3(0.0f, 1.0f, 0.0f);
	m_camSpeed = 3.0f;
	m_yaw = -90.0f;
	m_pitch = 0.0f;
}

void Camera::ProcessKeyBoard(CamAction action, float deltaTime)
{
	float speed = (deltaTime*m_camSpeed);
	m_camRight = glm::normalize(glm::cross(m_camFront, m_camUp));
	switch (action)
	{
	case CamAction::FORWARD:
	{
		m_camPos += m_camFront*speed;
		break;
	}
	case CamAction::BACK:
	{
		m_camPos -= m_camFront*speed;
		break;
	}
	case CamAction::LEFT:
	{ 
		m_camPos -= m_camRight*speed;
		break;
	}
	case CamAction::RIGHT:
	{
		m_camPos += m_camRight*speed;
		break;
	}
	default:
		break;
	}
}

void Camera::ProcessMouseMovement(double xoffset, double yoffset)
{
	float sensitivity = 0.05;
	glm::vec3 front;
	m_yaw += xoffset*sensitivity;
	m_pitch += yoffset*sensitivity;

	if (m_pitch >= 89.0)
		m_pitch = 89.0;
	if (m_yaw >= 360.0)
		m_yaw = 0.0f;
	front.x = cos(glm::radians(m_yaw))*cos(glm::radians(m_pitch));
	front.y = sin(glm::radians(m_pitch));
	front.z = sin(glm::radians(m_yaw));
	
	m_camFront = glm::normalize(front);
}

void Camera::SetCamSpeed(float userSpeed)
{
	m_camSpeed = userSpeed;
}

glm::mat4 Camera::GetViewMatrix()
{
	return glm::lookAt(m_camPos, m_camPos + m_camFront, m_camUp);
}

Camera::~Camera()
{
}
