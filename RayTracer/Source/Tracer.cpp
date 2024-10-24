#include "Tracer.h"
#include "Scene.h"

color3_t Tracer::Trace(Scene& scene, const ray_t& ray)
{
	color3_t color{ 0 };

	// check for object hit in scene
	for (auto& object : scene.m_objects)
	{
		if (object->Hit(ray))
		{
			return { 1, 0, 0 };
		}
	}

	//sky
	glm::vec3 direction = glm::normalize(ray.direction);
	float t = (direction.y + 1) * 0.5f;
	color = Lerp(color3_t{ 1, 1, 1 }, color3_t{ 0.5f, 0.7f, 1.0f }, t);

	return color;
}
