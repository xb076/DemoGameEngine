#include "pch.h"
#include "Application.h"

#include "Engine/Log.h"
#include "Input.h"
#include "Engine/Renderer/Renderer.h"


namespace Engine {

	Application* Application::s_Instance = nullptr;

	Application::Application() 
		: m_Camera(-1.6f, 1.6f, -.9f, .9f)
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
						
			for (Layer* layer : m_LayerStack)
				layer->OnUpdate();

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


