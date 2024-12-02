#pragma once
#include "Color.h"
#include "VertexShader.h"
#include <glm/glm.hpp>
#include <vector>
#include <string>

class Model
{
public:
	Model() = default;
	Model(const vertexbuffer_t& vertices, const color4_t& color) : m_vb{ vertices }, m_color{ color } {};

	void Draw();
	bool Load(const std::string& filename);

	void SetColor(const color4_t& color) { m_color = color; }

private:
	vertexbuffer_t m_vb;
	color4_t m_color{ 255, 255, 255, 255 };
};