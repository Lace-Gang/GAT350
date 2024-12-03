#include "VertexShader.h"

VertexShader::uniforms_t VertexShader::uniforms =
{
	//constructor for the identity matrix: glm::mat4(1)
	glm::mat4{1}, //model
	glm::mat4{1}, //view
	glm::mat4{1}, //projection
	color3_t{1}
	//using () and using {} here are equivalent
};


void VertexShader::Process(const vertex_t& ivertex, vertex_output_t& overtex)
{

	glm::mat4 mvp = uniforms.projection * uniforms.view * uniforms.model;
	overtex.position = mvp * glm::vec4{ ivertex.position, 1 }; //including transformations (with the 1)
	glm::mat4 mv = uniforms.view * uniforms.model; //model view
	overtex.normal = glm::vec3{ glm::normalize(glm::mat3{ mv } *ivertex.normal) };

	//glm::vec3 light_position{ 10, 10, -10 };

	//color3_t diffuse = light_color * intensity;
	//overtex.color = uniforms.ambient + diffuse;

	//POINT
	//glm::vec3 light_position = uniforms.light.position;
	//transform to view space (it is already in world space)
	//light_position = uniforms.view * glm::vec4{ light_position, 1 };
	glm::vec3 light_position = uniforms.view * glm::vec4{ uniforms.light.position, 1 };
	glm::vec3 light_direction = uniforms.view * glm::vec4{ -uniforms.light.direction, 0 };

	glm::vec3 vposition = mv * glm::vec4{ ivertex.position, 1 };
	//glm::vec3 light_dir = glm::normalize(light_position - vposition); //vector pointing at the light (head - tail) AND NORMALIZED
	glm::vec3 light_dir = glm::normalize(light_direction);

	float intensity = std::max(0.0f, glm::dot(light_dir, overtex.normal));
	////color3_t light_color{ 1, 0, 0 };

	//DIFFUSE
	//glm::vec3 light_dir = uniforms.light.direction;
	//light_dir = uniforms.view * glm::vec4{ light_dir, 0 }; //vec4 must have 0. If the value is changed to one, the directional light will stop working
	//
	//light_dir = glm::normalize(light_dir * glm::vec3{ -1 });
	//float intensity = std::max(0.0f, glm::dot(light_dir, overtex.normal));


	color3_t diffuse = uniforms.light.color * intensity;
	overtex.color = uniforms.ambient + diffuse;
}

