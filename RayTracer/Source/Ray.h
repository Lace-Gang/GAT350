#pragma once
#include <glm/glm.hpp>
#include <memory>


struct ray_t
{
	glm::vec3 origin;
	glm::vec3 direction;

	ray_t() = default;
	ray_t(const glm::vec3& origin, const glm::vec3& direction) : origin{ origin }, direction{ direction } {}
	//const allows us to pass in literals ray-_t(0, 2) vs needing to pass in variable names

	//for cost reasons, please always provide vectors already normalized
	glm::vec3 at(float t) { return origin + direction * t; }
	glm::vec3 operator * (float t) const { return origin + direction * t; }

};


struct raycastHit_t
{
	float distance{ 0 };

	glm::vec3 point{ 0 };
	glm::vec3 normal{ 0 };

	std::weak_ptr<class Material> material;
};