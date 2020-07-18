#pragma once

#ifdef ENGINE_PLATFORM_WINDOWS

extern Engine::Application* Engine::CreateApplication();

int main(int argc, char* argv[])
{
	//Engine::Log::Init();
	//LOG_CORE_WARN("Initialized Log!");
	//int a = 5;
	//LOG_APP_INFO("Hello! Var={0}", a);


	//auto app = Engine::CreateApplication();
	//app->Run();
	//delete app;

	Engine::Log::Init();

	ENGINE_PROFILE_BEGIN_SESSION("Startup", "EngineProfile-Startup.json");
	auto app = Engine::CreateApplication();
	ENGINE_PROFILE_END_SESSION();

	ENGINE_PROFILE_BEGIN_SESSION("Runtime", "EngineProfile-Runtime.json");
	app->Run();
	ENGINE_PROFILE_END_SESSION();

	ENGINE_PROFILE_BEGIN_SESSION("Shutdown", "EngineProfile-Shutdown.json");
	delete app;
	ENGINE_PROFILE_END_SESSION();

	return 0;
}



#endif
