#include "Actor.h"
#include "Shader.h"

//void Actor::Draw(Framebuffer& framebuffer, const Camera& camera)
void Actor::Draw()
{
	//set vetex shader model matrix

	VertexShader::uniforms.model = m_transform.GetMatrix();

	//m_model->SetColor(m_color);
	//m_model->Draw(framebuffer, m_transform.GetMatrix(), camera);
	m_model->Draw();
}
