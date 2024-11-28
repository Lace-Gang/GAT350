#pragma once

#include "Transform.h"
#include "Model.h"

#include<memory>



class Actor
{
public:
	Actor(const Transform& transform, std::shared_ptr<Model> model) : m_transform{ transform }, m_model{ model }{}

	Transform& GetTransform() { return m_transform; }
	const Transform& GetTransform() const { return m_transform; }

	//void Draw(class Framebuffer& framebuffer, const class Camera& camera);
	void Draw();
	
	//void SetColor(const color_t& color) { m_color = color; };

private:
	Transform m_transform;
	std::shared_ptr<Model> m_model;
	//color_t m_color;
};