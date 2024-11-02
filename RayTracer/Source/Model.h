#pragma once

#include "Color.h"
#include "SceneObject.h"

#include <iostream>
#include <glm/glm.hpp>
#include <vector>

using vertex_t = glm::vec3;
using vertices_t = std::vector<vertex_t>;

class Model : public SceneObject
{
public:
	Model(std::shared_ptr<Material> material) : SceneObject{ material } {}
	Model(const vertices_t& vertices, std::shared_ptr<Material> material) : SceneObject{ material }, m_vertices{ vertices } {}

	bool Load(const std::string& filename);
	bool Hit(const ray_t& ray, raycastHit_t& raycastHit, float minDistance, float maxDistance) override;

public:
	vertices_t m_vertices;
};