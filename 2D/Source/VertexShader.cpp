#include "VertexShader.h"

VertexShader::uniforms_t VertexShader::uniforms =
{
	glm::mat4{ 1 }, //model
	glm::mat4{ 1 }, //view
	glm::mat4{ 1 }, //projection
	color3_t{ 1 }
};

void VertexShader::Process(const vertex_t& ivertex, vertex_output_t& overtex)
{
	glm::mat4 mvp = uniforms.projection * uniforms.view * uniforms.model;
	overtex.position = mvp * glm::vec4{ ivertex.position, 1 };
	glm::mat4 mv = uniforms.view * uniforms.model;
	overtex.normal = glm::normalize(glm::mat3{ mv } * ivertex.normal);

#pragma region light
	//glm::vec3 light_position{ 10, 10, -10 };
	//// transform to view space
	//// it is already in world space
	//light_position = uniforms.view * glm::vec4{ uniforms.light.position, 1 };
	//glm::vec3 vposition = mv * glm::vec4{ ivertex.position, 1 };
	//glm::vec3 light_dir = glm::normalize(light_position - vposition); // normalize light direction

	//float intensity = std::max(0.0f, glm::dot(light_dir, overtex.normal));
	//color3_t light_color{ 1, 1, 0 };
	//color3_t diffuse = uniforms.light.color * intensity;

	//overtex.color = uniforms.ambient + diffuse;
#pragma endregion

	glm::vec3 light_position = uniforms.view * glm::vec4{ uniforms.light.position, 1 };
	glm::vec3 light_direction = uniforms.view * glm::vec4{ -uniforms.light.direction, 0 };
	glm::vec3 vposition = mv * glm::vec4{ ivertex.position, 1 };

	//point light
	glm::vec3 light_dir = glm::normalize(light_position - vposition);

	//directional light
	//glm::vec3 light_dir = glm::normalize(light_direction);

	float intensity = std::max(0.0f, glm::dot(light_dir, overtex.normal));

	//color
	color3_t diffuse = uniforms.light.color * intensity;
	overtex.color = uniforms.ambient + diffuse;
}
