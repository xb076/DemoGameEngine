#pragma once

#include "Engine.h"

namespace Engine {

	class EditorLayer : public Layer
	{
	public:
		EditorLayer();
		virtual ~EditorLayer() = default;

		virtual void OnAttach() override;
		virtual void OnDetach() override;

		void OnUpdate(Timestep ts) override;
		virtual void OnImGuiRender() override;
		void OnEvent(Event& e) override;

	private:
		OrthographicCameraController m_CameraController;

		// Temp
		ShaderLibrary m_ShaderLibrary;
		Ref<Shader> m_Shader;
		Ref<VertexArray> m_VertexArray;

		Ref<VertexArray> m_SquareVA;
		Ref<Shader> m_FlatColorShader;
		Ref<Framebuffer> m_Framebuffer;

		Ref<Texture2D> m_CheckerboardTexture, m_LogoTexture;

		glm::vec4 m_SquareColor = { .2f, .3f, .8f, 1.0f };

		bool m_ViewportFocused = false, m_ViewportHovered = false;
		glm::vec2 m_ViewportSize = { 0.0f, 0.0f };

		struct ProfileResult
		{
			const char* Name;
			float Time;
		};

		std::vector<ProfileResult> m_ProfileResults;
	};

}

