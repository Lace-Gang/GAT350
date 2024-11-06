#pragma once

#include<memory>
#include<iostream>
#include "Material.h"
#include "Transform.h"
#include "Ray.h"
//#include "Triangle.h"


class SceneObject
{
public:
	SceneObject() = default;
	SceneObject(std::shared_ptr<class Material> material) : m_material{ material } {}
	SceneObject(const Transform& transform, std::shared_ptr<class Material> material) :
		m_transform{ transform },
		m_material{ material } {}

	virtual void Update() {}
	virtual bool Hit(const ray_t& ray, raycastHit_t& raycastHit, float minDistance, float maxDistance) = 0;
	//virtual bool Load(const std::string& filename) = 0;

	std::weak_ptr<class Material> GetMaterial() { return m_material; }

	Transform& GetTransform() { return m_transform; }
	const Transform& GetTransform() const { return m_transform; }



	//friend class Model;
protected:
	std::shared_ptr<class Material> m_material;
	Transform m_transform;
};