#include "Model.h"
#include "Framebuffer.h"

void Model::Draw(Framebuffer& framebuffer, const glm::mat4& model)
{
	for (int i = 0; i < m_vertices.size(); i += 3)
	{
		vertex_t p1 = model * glm::vec4{ m_vertices[i + 0], 1 };
		vertex_t p2 = model * glm::vec4{ m_vertices[i + 1], 1 };
		vertex_t p3 = model * glm::vec4{ m_vertices[i + 2], 1 };

		framebuffer.DrawTriangle((int)p1.x, (int)p1.y, (int)p2.x, (int)p2.y, (int)p3.x, (int)p3.y, m_color);
	}
}
