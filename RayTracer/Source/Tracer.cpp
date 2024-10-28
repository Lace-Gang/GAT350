#include "Tracer.h"
#include "Scene.h"
#include "Material.h"

color3_t Tracer::Trace(Scene& scene, const ray_t& ray, float minDistance, float maxDistance)
{

	raycastHit_t raycastHit;
	float closestDiscance = maxDistance;
	bool isHit = false;

	for (auto& object : scene.m_objects)
	{
		//check for object hit
		if (object->Hit(ray, raycastHit, minDistance, closestDiscance))
		{
			isHit = true;

			closestDiscance = raycastHit.distance;

			//return{ 1,0,0 };
			//return object->GetMaterial().lock()->GetColor();
		}
	}

	if (isHit)
	{
		// object->GetMaterial().lock()->GetColor();
		//return raycastHit.material.lock()->GetColor();
		//return raycastHit.normal;
		color3_t attenuation;
		ray_t scatter;
		if (raycastHit.material.lock()->Scatter(ray, raycastHit, attenuation, scatter))
		{
			return attenuation * Trace(scene, scatter, minDistance, maxDistance);
		}
	}

	glm::vec3 direction = glm::normalize(ray.direction);

	float t = (direction.y + 1) * 0.5f;
	color3_t color = Lerp(color3_t{ 1, 1, 1 }, color3_t{ 0.5f, 0.7f, 1.0f }, t);

	return color;
}
