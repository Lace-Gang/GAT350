#include "Shader.h"
#include "Framebuffer.h"
#include "Rasterizer.h"

Framebuffer* Shader::framebuffer{ nullptr };

void Shader::Draw(const vertexbuffer_t& vb)
{
	// vertex shader
	std::vector<vertex_output_t> overtices;
	overtices.reserve(vb.size());
	//reserve: reserve capacity (push_back will push back INTO reserved capasity) <-- less memory work
	//resize set capacity (push_back will ADD more capacity to what is already there from the resize) <--no
	//not doing either is more memory work

	for (auto& vertex : vb)
	{
		vertex_output_t overtex;
		VertexShader::Process(vertex, overtex);

		overtices.push_back(overtex);
	}

	// primitive assembly (triangle)
	for (int i = 0; i < overtices.size(); i += 3)
	{
		vertex_output_t& v0 = overtices[i];
		vertex_output_t& v1 = overtices[i + 1];
		vertex_output_t& v2 = overtices[i + 2];

		glm::vec2 s0, s1, s2;
		if (!ToScreen(v0, s0)) continue;
		if (!ToScreen(v1, s1)) continue;
		if (!ToScreen(v2, s2)) continue;

		// rasterization
		Rasterizer::Triangle(*framebuffer, s0, s1, s2, v0, v1, v2);

		//framebuffer->DrawTriangle(s0.x, s0.y, s1.x, s1.y, s2.x, s2.y, { 255, 255, 255, 255 }); //<-- this line does work for me :)
	}
}

bool Shader::ToScreen(const vertex_output_t& vertex, glm::vec2& screen)
{
	// prevent / 0
	if (vertex.position.w == 0) return false;

	// convert projection space to ndc (-1 <-> 1)
	glm::vec3 ndc = vertex.position / vertex.position.w;

	// don't draw if outside near and far clip plane
	if (ndc.z < -1 || ndc.z > 1) return false;

	screen.x = (ndc.x + 1) * (framebuffer->m_width * 0.5f);
	screen.y = (1 - ndc.y) * (framebuffer->m_height * 0.5f);

	return true;
}