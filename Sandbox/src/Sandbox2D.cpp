#include "Sandbox2D.h"
#include <imgui/imgui.h>

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "Platform/OpenGL/OpenGLShader.h"
#include "Platform/OpenGL/OpenGLTexture.h"

Sandbox2D::Sandbox2D()
	: Layer("Sandbox2D"), m_CameraController(1280.0f / 720.0f)
{
}

void Sandbox2D::OnAttach()
{

	m_SquareVA = Engine::VertexArray::Create();

	float squareVertices[3 * 4] = {
		-0.5f, -0.5f, 0.0f,
		 0.5f, -0.5f, 0.0f,
		 0.5f,  0.5f, 0.0f,
		-0.5f,  0.5f, 0.0f
	};

	Engine::Ref<Engine::VertexBuffer> squareVB;
	squareVB = Engine::VertexBuffer::Create(squareVertices, sizeof(squareVertices));

	squareVB->SetLayout({
		{ Engine::ShaderDataType::Float3, "a_Position" }
		});
	m_SquareVA->AddVertexBuffer(squareVB);

	uint32_t squareIndices[6] = { 0, 1, 2, 2, 3, 0 };
	Engine::Ref<Engine::IndexBuffer> squareIB;
	squareIB = Engine::IndexBuffer::Create(squareIndices, sizeof(squareIndices) / sizeof(uint32_t));
	m_SquareVA->SetIndexBuffer(squareIB);

	m_FlatColorShader = Engine::Shader::Create("assets/shaders/FlatColor.glsl");

}

void Sandbox2D::OnDetach()
{
	
}

void Sandbox2D::OnUpdate(Engine::Timestep ts)
{
	
	// Update
	m_CameraController.OnUpdate(ts);

	Engine::RenderCommand::SetClearColor({ 0.1f, 0.1f, 0.1f, 1 });
	Engine::RenderCommand::Clear();

	Engine::Renderer::BeginScene(m_CameraController.GetCamera());

	static glm::mat4 scale = glm::scale(glm::mat4(1.0f), glm::vec3(0.1f));

	std::dynamic_pointer_cast<Engine::OpenGLShader>(m_FlatColorShader)->Bind();
	std::dynamic_pointer_cast<Engine::OpenGLShader>(m_FlatColorShader)->UploadUniformFloat4("u_Color", m_SquareColor);

	Engine::Renderer::Submit(m_FlatColorShader, m_SquareVA, glm::scale(glm::mat4(1.0f), glm::vec3(1.5f)));

	//Engine::Renderer::Submit(m_Shader, m_VertexArray);

	Engine::Renderer::EndScene();
}

void Sandbox2D::OnImGuiRender()
{
	ImGui::Begin("Setting");
	ImGui::ColorEdit4("Square Color", glm::value_ptr(m_SquareColor));
	ImGui::End();
}

void Sandbox2D::OnEvent(Engine::Event& e)
{
	m_CameraController.OnEvent(e);
}