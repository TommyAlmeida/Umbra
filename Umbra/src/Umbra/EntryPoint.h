#pragma once
#include <stdio.h>

#ifdef UB_PLATFORM_WINDOWS

extern Umbra::Application* Umbra::CreateApplication();

int main(int argc, char** argv) {
	printf("Umbra engine has started");

	auto app = Umbra::CreateApplication();
	app->Run();
	delete app;

	printf("Umbra engine has ended");
}

#endif