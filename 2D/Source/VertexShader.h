#pragma once
#include "Light.h"
#include "Color.h"
#include <array>

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
		// transformations (mvp)
		glm::mat4 model;
		glm::mat4 view;
		glm::mat4 projection;
		// lights
		color3_t ambient;
		light_t light;
	};

	static uniforms_t uniforms;
};


