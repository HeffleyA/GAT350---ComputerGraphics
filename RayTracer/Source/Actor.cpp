#include "Actor.h"

void Actor::Draw(Framebuffer& framebuffer, const Camera& camera)
{
	m_model->SetColor(m_color);
	m_model->Draw(framebuffer, m_transform.GetMatrix(), camera);
}
