
#include <iostream>
#include "Engine.h"

class ExampleLayer : public Engine::Layer
{
public:
	ExampleLayer() : Layer("Example")
	{
	}

	void OnUpdate() override
	{
		//LOG_APP_INFO("ExampleLayer::Update");

		if(Engine::Input::IsKeyPressed((int)ENGINE_KEY_TAB))
			LOG_APP_INFO("Tab Key is pressed!");
	}

	void OnEvent(Engine::Event& event) override
	{
		//LOG_APP_TRACE("{0}", event);
		if (event.GetEventType() == Engine::EventType::KeyPressed)
		{
			Engine::KeyPressedEvent& e = (Engine::KeyPressedEvent&)event;
			LOG_APP_TRACE("{0}", (char)e.GetKeyCode());
		}
	}

};


class Sandbox : public Engine::Application
{
public:
	Sandbox()
	{
		PushLayer(new ExampleLayer());
		PushOverlay(new Engine::ImGuiLayer());
	}
	~Sandbox()
	{}

};

Engine::Application* Engine::CreateApplication()
{
	return new Sandbox();
}