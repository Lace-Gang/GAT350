#pragma once

#define GLM_ENABLE_EXPERIMENTAL
#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>
#include <glm/gtx/euler_angles.hpp>

struct Transform
{
	glm::vec3 position{ 0 };
	glm::vec3 rotation{ 0 };
	glm::vec3 scale{ 1 };

	Transform() = default;
	Transform(const glm::vec3& position, const glm::vec3& rotation = glm::vec3{ 0 }, const glm::vec3& scale = glm::vec3{ 1 })
		: position { position }, rotation{ rotation }, scale{ scale } {}

	glm::mat4 GetMatrix()
	{
		//mxs = matrix scale, mxt = matrix translate, mxr = matrix rotation
		glm::mat4 mxs = glm::scale(scale); 
		glm::mat4 mxt = glm::translate(position);
		//order of operations are very important. Especially with rotaion
		glm::mat4 mxr = glm::eulerAngleYXZ(glm::radians(rotation.y), glm::radians(rotation.x), glm::radians(rotation.z));

		//The order of these translations IS IN REVERSE!
		//Always rotation and scale (either before is fine) and	THEN you can do translate, but that MUST be last in execution.
		//which means tranlate must be first in the code
		glm::mat4 mx = mxt * mxs * mxr;

		return mx;
	}
};