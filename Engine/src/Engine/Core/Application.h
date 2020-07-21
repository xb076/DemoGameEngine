#pragma once

#include "Core.h"
#include "Window.h"
#include "LayerStack.h"
#include "Engine/Events/Event.h"
#include "Engine/Events/ApplicationEvent.h"

#include "Engine/ImGui/ImGuiLayer.h"

#include "Engine/Core/Timestep.h"

namespace Engine {

	class ENGINE_API Application
	{
	public:
		Application(const std::string& name = "Engine App");
		virtual ~Application();

		void Run();

		void OnEvent(Event& e);

		void PushLayer(Layer* layer);
		void PushOverlay(Layer* layer);

		inline static Application& Get() { return *s_Instance; }
		inline Window& GetWindow() { return *m_Window; }

		void Close();
		ImGuiLayer* GetImGuiLayer() { return m_ImGuiLayer; }

	private:
		bool OnWindowClose(WindowCloseEvent& e);
		bool OnWindowResize(WindowResizeEvent& e);

		Scope<Window> m_Window;
		ImGuiLayer* m_ImGuiLayer;
		bool m_Running = true;
		bool m_Minimized = false;
		LayerStack m_LayerStack;
		Timestep m_Timestep;
		float m_LastFrameTime = 0.0f;


		static Application* s_Instance;

	};


	Application* CreateApplication();

}




