#pragma once
#include "Color.h"
#include <glm/glm.hpp>

struct light_t
{
	glm::vec3 position;
	glm::vec3 direction;
	color3_t color;
};