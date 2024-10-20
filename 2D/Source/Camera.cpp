#include "Camera.h"
#include<glm/gtc/matrix_transform.hpp>

void Camera::SetView(const glm::vec3& eye, const glm::vec3& target, const glm::vec3& up)
{
	m_view = glm::lookAt(eye, target, up);
}

void Camera::setProjection(float fov, float aspectRatio, float near, float far)
{
	//we will be using perspective projection as opposed to orthographic projection
	m_projection = glm::perspective(glm::radians(fov), aspectRatio, near, far);
}

glm::vec3 Camera::modelToView(const glm::vec3& position) const
{
	//convert point from world space to view space
	return m_view * glm::vec4{ position, 1 };
}

glm::vec3 Camera::ViewToProjection(const glm::vec3& position) const
{
	//convert point from view space to projection space
	return m_projection * glm::vec4{ position, 1 };
}

glm::ivec2 Camera::ToScreen(const glm::vec3& position) const
{
	glm::vec4 clip = m_projection * glm::vec4{ position, 1 };
	glm::vec3 ndc = clip / clip.w;

	float x = (ndc.x + 1) * (m_width * 0.5f); //ndc needs to go from -1 to 1 --> 0 to 2
	float y = (1 - ndc.y) * (m_height * 0.5f); 

	return glm::ivec2(x, y);
}


