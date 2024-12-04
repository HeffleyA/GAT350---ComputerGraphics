#pragma once
#include "VertexShader.h"
#include "FragmentShader.h"

class Shader
{
public:
	static void Draw(const vertexbuffer_t& vb);
	static bool ToScreen(const vertex_output_t& vertex, glm::vec2& screen);

public:
	enum eFrontFace
	{
		CW,
		CCW
	};

	enum eCullMode
	{
		FRONT,
		BACK,
		NONE
	};

	static class Framebuffer* framebuffer;
	static eFrontFace front_face;
	static eCullMode cull_mode;
};