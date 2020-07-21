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
	ENGINE_PROFILE_FUNCTION();

	m_CheckerboardTexture = Engine::Texture2D::Create("assets/textures/Checkerboard.png");

}

void Sandbox2D::OnDetach()
{
}

void Sandbox2D::OnUpdate(Engine::Timestep ts)
{
	ENGINE_PROFILE_FUNCTION();

	m_CameraController.OnUpdate(ts);
	Engine::Renderer2D::ResetStats();
	
	{
		ENGINE_PROFILE_SCOPE("Renderer Prep");

		Engine::RenderCommand::SetClearColor({ 0.1f, 0.1f, 0.1f, 1 });
		Engine::RenderCommand::Clear();
	}

	{
		static float rotation = 0.f;
		rotation += ts * 50.f;

		ENGINE_PROFILE_SCOPE("Renderer Draw");
		Engine::Renderer2D::BeginScene(m_CameraController.GetCamera());
		Engine::Renderer2D::DrawRotatedQuad({ 1.f,0.f }, { .8f,.8f }, glm::radians(rotation), { 0.8f,0.2f,0.3f,1.0f });
		Engine::Renderer2D::DrawQuad({ -1.f,0.f }, { .8f,.8f }, { 0.8f,0.2f,0.3f,1.0f });
		Engine::Renderer2D::DrawQuad({ 0.5f,-0.5f }, { .5f,.75f }, { 0.2f,0.3f,0.8f,1.0f });
		Engine::Renderer2D::DrawQuad({ -5.0f, -5.0f, -0.1f }, { 10.f,10.f }, m_CheckerboardTexture, 1.f);
		//Engine::Renderer2D::DrawQuad({ -.5f, -.5f, 0.f }, { 1.f,1.f }, m_CheckerboardTexture, 20.f);
		Engine::Renderer2D::DrawRotatedQuad({ 0.0f, 0.0f, -0.1f }, { 10.f,10.f }, glm::radians(rotation), m_CheckerboardTexture, 10.f);
		Engine::Renderer2D::EndScene();

		Engine::Renderer2D::BeginScene(m_CameraController.GetCamera());
		for (float y = -5.f; y < 5.f; y += 0.5f)
		{
			for (float x = -5.f; x < 5.f; x += 0.5f)
			{
				glm::vec4 color = { (x+5.f)/10.f, 0.4f, (y+5.f)/10.f, .5f};
				Engine::Renderer2D::DrawQuad({x, y}, {0.45f, 0.45f}, color);
			}
		}

		Engine::Renderer2D::EndScene();
	}

}

void Sandbox2D::OnImGuiRender()
{
	ENGINE_PROFILE_FUNCTION();

	ImGui::Begin("Setting");

	auto stats = Engine::Renderer2D::GetStats();
	ImGui::Text("Renderer2D Stats: ");
	ImGui::Text("Draw Calls: %d", stats.DrawCalls);
	ImGui::Text("Quad Counts: %d", stats.QuadCount);
	ImGui::Text("Vertices: %d", stats.GetTotalVertexCount());
	ImGui::Text("Indices: %d", stats.GetTotalIndexCount());

	ImGui::ColorEdit4("Square Color", glm::value_ptr(m_SquareColor));

	uint32_t textureID = m_CheckerboardTexture->GetRendererID();
	ImGui::Image((void*)textureID, ImVec2{128.f, 128.f});
	ImGui::End();


}

void Sandbox2D::OnEvent(Engine::Event& e)
{
	m_CameraController.OnEvent(e);
}



