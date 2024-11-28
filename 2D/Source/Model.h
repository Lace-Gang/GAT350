#pragma once

#include "Color.h"

#include <iostream>
#include <glm/glm.hpp>
#include <vector>
#include <array>
#include "VertexShader.h"

//using vertex_t = glm::vec3;
//using vertices_t = std::vector<vertex_t>;

class Model
{
public:
	Model() = default;
	Model(const vertexbuffer_t& vertices, const color4_t color) : m_vb{ vertices }, m_color{ color } {};

	//void Draw(class Framebuffer& framebuffer, const glm::mat4& model, const class Camera& camera);
	void Draw();

	bool Load(const std::string& filename);

	//void SetColor(color_t color);
	void SetColor(const color4_t& color) { m_color = color; }

private:
	vertexbuffer_t m_vb;
	//color_t m_color = { 255, 255, 255, 255 };
	color4_t m_color = { 0, 0, 0, 1 };
};