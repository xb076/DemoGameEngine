#pragma once

#ifdef ENGINE_PLATFORM_WINDOWS

extern Engine::Application* Engine::CreateApplication();

int main(int argc, char* argv[])
{
	/*Sandbox* sandbox = new Sandbox();
	sandbox->Run();
	delete sandbox;*/
	Engine::Log::Init();
	LOG_CORE_WARN("Initialized Log!");
	int a = 5;
	LOG_APP_INFO("Hello! Var={0}", a);


	auto app = Engine::CreateApplication();
	app->Run();
	delete app;

	return 0;
}



#endif
