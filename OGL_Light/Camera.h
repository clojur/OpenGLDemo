#pragma once
#include<GLM/glm.hpp>
#include<GLM/gtc/matrix_transform.hpp>
enum class  CamAction {
		FORWARD,
		BACK,
		LEFT,
		RIGHT
	};
class Camera
{
public:
	Camera();
	Camera(const glm::vec3 &camPos);
	void ProcessKeyBoard(CamAction action,float deltaTime);
	void ProcessMouseMovement(double xoffset,double yoffset);
	void SetCamSpeed(float userSpeed);
	glm::mat4 GetViewMatrix();
	~Camera();
glm::vec3 m_camPos;
	
private:
	
	glm::vec3 m_camFront;
	glm::vec3 m_camUp;
	glm::vec3 m_camRight;
	float m_camSpeed;
	float m_yaw;
	float m_pitch;
};

