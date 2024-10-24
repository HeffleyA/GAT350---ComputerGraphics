#include "Scene.h"
#include "Framebuffer.h"
#include "Camera.h"
#include "Tracer.h"

void Scene::Render(Framebuffer& framebuffer, const Camera& camera)
{
	for (int y = 0; y < framebuffer.m_height; y++)
	{
		for (int x = 0; x < framebuffer.m_width; x++)
		{
			glm::vec2 pixel{ x, y };
			glm::vec2 point = pixel / glm::vec2{ framebuffer.m_width, framebuffer.m_height };
			point.y = 1 - point.y;

			ray_t ray = camera.GetRay(point);

			color3_t color = Tracer::Trace(*this, ray);
			framebuffer.DrawPoint(x, y, ColorConvert(color));
		}
	}
}
