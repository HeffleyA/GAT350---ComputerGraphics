#pragma once
#include "Color.h"

class Material
{
public:
	Material() = default;
	Material(const color3_t& color) : m_color{ color } {}

	color3_t GetColor() { return m_color; }

private:
	color3_t m_color;
};