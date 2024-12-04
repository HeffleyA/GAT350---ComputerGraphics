#include "Actor.h"
#include "Shader.h"

void Actor::Draw()
{
	Shader::uniforms.model = m_transform.GetMatrix();
	Shader::uniforms.material = *m_material;

	m_model->Draw();
}
