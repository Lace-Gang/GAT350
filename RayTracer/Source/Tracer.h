#pragma once

#include "Color.h"
#include "Scene.h"
#include "Ray.h"


class Tracer
{
public:
	static color3_t Trace(Scene& scene, const ray_t& ray, float minDistance, float maxDistance);

private:

};