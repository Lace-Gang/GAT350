#pragma once
//#include "Light.h"
#include "Color.h"
#include "Light.h"

#include <array>
#include <vector>
//#define GLM_ENABLE_EXPERIMENTAL	
//
//#include<glm/glm.hpp>
//#include <SDL.h>
//#include <algorithm>
//#include <glm/gtx/color_space.hpp>

struct vertex_t
{
	glm::vec3 position;
	glm::vec3 normal;
	glm::vec2 uv;
};

using vertexbuffer_t = std::vector<vertex_t>;

struct vertex_output_t
{
	glm::vec4 position;
	glm::vec3 normal;
	color3_t color;
};

class VertexShader
{
public:
	static void Process(const vertex_t& ivertex, vertex_output_t& overtex);

public:
	struct uniforms_t 
	{
		//transformations (mvp)
		glm::mat4 model;
		glm::mat4 view;
		glm::mat4 projection;
		light_t light;
		//lights
		
		color3_t ambient;
	};

	static uniforms_t uniforms;
};


