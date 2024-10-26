#pragma once
#include <vector>
#include <memory>

#include "Sphere.h"

#include "Framebuffer.h"
#include "Camera.h"
#include "SceneObject.h"

class Scene
{
public:
	Scene() = default;

	void Render(Framebuffer& framebuffer, const Camera& camera);

	void AddObject(std::unique_ptr<SceneObject> object) { m_objects.push_back(std::move(object)); }


	friend class Tracer;

private:
	std::vector<std::unique_ptr<SceneObject>> m_objects;
};