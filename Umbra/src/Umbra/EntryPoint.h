#pragma once
#include <stdio.h>

#ifdef UB_PLATFORM_WINDOWS

extern Umbra::Application* Umbra::CreateApplication();

int main(int argc, char** argv) {
	
	Umbra::Log::Init();

	UB_CORE_INFO("Engine has started {0}", 1);

	auto app = Umbra::CreateApplication();
	app->Run();
	delete app;

}

#endif