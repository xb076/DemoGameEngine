#pragma once

#ifdef ENGINE_PLATFORM_WINDOWS

extern Engine::Application* Engine::CreateApplication();

int main(int argc, char* argv[])
{
	/*Sandbox* sandbox = new Sandbox();
	sandbox->Run();
	delete sandbox;*/
	printf("Engine starting ...\n");

	auto app = Engine::CreateApplication();
	app->Run();
	delete app;

	return 0;
}



#endif
