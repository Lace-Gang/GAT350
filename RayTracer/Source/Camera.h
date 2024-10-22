#pragma once

#define GLM_FORCE_DEPTH_ZERO_TO_ONE
//#define GLM_FORCE_LEFT_HAND
#include <glm/glm.hpp>

class Camera
{
public:
	Camera(int width, int height) : m_width{ width }, m_height { height } {}

	void SetView(const glm::vec3& eye, const glm::vec3& target, const glm::vec3& up = {0, 1, 0}); //defaults up to the typical up
	void setProjection(float fov, float aspectRatio, float near, float far);

	glm::vec3 modelToView(const glm::vec3& position) const;
	glm::vec3 ViewToProjection(const glm::vec3& position) const;

	glm::ivec2 ToScreen(const glm::vec3& position)const;


	//methods with the definition in here are automatically "inline"
	const glm::mat4& getView() { return m_view; }
	const glm::mat4& getProjection() { return m_projection; }
	
private:
	glm::mat4 m_view{ 1 };
	glm::mat4 m_projection{ 1 };

	//screen width/height
	int m_width{ 0 };
	int m_height{ 0 };


};