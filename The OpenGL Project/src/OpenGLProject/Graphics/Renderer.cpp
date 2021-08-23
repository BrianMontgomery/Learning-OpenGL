#include "OpenGLProject/Graphics/Renderer.h"
#include "OpenGLProject/Base/Base.h"
#include "OpenGLProject/Utility/Instrumentor.h"

//#include "OpenGLProject/Graphics/Renderer2D.h"


Scope<Renderer::SceneData> Renderer::s_SceneData = CreateScope<Renderer::SceneData>();

void Renderer::Init()
{
	OPENGLPROJECT_PROFILE_FUNCTION();

	RenderCommand::Init();
	//Renderer2D::Init();
}

void Renderer::Shutdown()
{
	//Renderer2D::Shutdown();
}

void Renderer::OnWindowResize(uint32_t width, uint32_t height)
{
	RenderCommand::SetViewport(0, 0, width, height);
}

void Renderer::BeginScene(OrthographicCamera& camera)
{
	s_SceneData->ViewProjectionMatrix = camera.GetViewProjectionMatrix();
}

void Renderer::EndScene()
{
}

void Renderer::Submit(const Ref<Shader>& shader, const Ref<VertexArray>& vertexArray, const glm::mat4& transform)
{
	shader->bind();
	shader->setMat4("u_ViewProjection", s_SceneData->ViewProjectionMatrix);
	shader->setMat4("u_Transform", transform);

	vertexArray->Bind();
	RenderCommand::DrawIndexed(vertexArray);
}