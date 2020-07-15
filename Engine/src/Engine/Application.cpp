#include "pch.h"
#include "Application.h"

#include "Engine/Log.h"
#include "glad/glad.h"
#include "Engine/Input.h"

namespace Engine {

	Application* Application::s_Instance = nullptr;

	Application::Application()
	{
		ENGINE_CORE_ASSERT(!s_Instance, "Application already exists!");
		s_Instance = this;
		m_Window = std::unique_ptr<Window>(Window::Create());
		m_Window->SetEventCallback(ENGINE_BIND_EVENT_FN(Application::OnEvent));

		m_ImGuiLayer = new ImGuiLayer();
		PushOverlay(m_ImGuiLayer);
	}

	Application::~Application()
	{

	}

	void Application::OnEvent(Event& e)
	{
		EventDispatcher dispatcher(e);
		dispatcher.Dispatch<WindowCloseEvent>(ENGINE_BIND_EVENT_FN(Application::OnWindowClose));

		for (auto it = m_LayerStack.end(); it != m_LayerStack.begin();)
		{
			(*--it)->OnEvent(e);
			if (e.m_Handled) break;
		}
	}

	void Application::PushLayer(Layer* layer)
	{
		if (nullptr != layer) { 
			m_LayerStack.PushLayer(layer);
			layer->OnAttach();
		}
	}
	void Application::PushOverlay(Layer* layer)
	{
		if (nullptr != layer) { 
			m_LayerStack.PushOverlay(layer);
			layer->OnAttach();
		}
	}

	void Application::Run()
	{
		while (m_Running)
		{
			glClearColor(1, 0, 1, 1);
			glClear(GL_COLOR_BUFFER_BIT);

			/*auto[x, y] = Input::GetMousePosition();
			LOG_CORE_TRACE("{0}, {1}", x, y);*/

			m_ImGuiLayer->Begin();
			for (Layer* layer : m_LayerStack)
				layer->OnImGuiRender();
			m_ImGuiLayer->End();


			m_Window->OnUpdate();
		}
	}

	bool Application::OnWindowClose(WindowCloseEvent& e)
	{
		m_Running = false;
		return true;
	}
}


