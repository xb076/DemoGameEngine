#pragma once

#include "Engine.h"

class Sandbox2D : public Engine::Layer
{
public:
	Sandbox2D();
	virtual ~Sandbox2D() = default;

	virtual void OnAttach() override;
	virtual void OnDetach() override;

	void OnUpdate(Engine::Timestep ts) override;
	virtual void OnImGuiRender() override;
	void OnEvent(Engine::Event& e) override;
private:
	Engine::OrthographicCameraController m_CameraController;
	
	// Temp
	Engine::ShaderLibrary m_ShaderLibrary;
	Engine::Ref<Engine::Shader> m_Shader;
	Engine::Ref<Engine::VertexArray> m_VertexArray;

	Engine::Ref<Engine::VertexArray> m_SquareVA;
	Engine::Ref<Engine::Shader> m_FlatColorShader;
	
	Engine::Ref<Engine::Texture2D> m_CheckerboardTexture, m_LogoTexture;

	glm::vec4 m_SquareColor = { .2f, .3f, .8f, 1.0f };


	struct ProfileResult
	{
		const char* Name;
		float Time;
	};

	std::vector<ProfileResult> m_ProfileResults;
};