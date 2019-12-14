#pragma once

#include "Core.h"

namespace Umbra {
	class UMBRA_API Application
	{
	public:
		Application();
		virtual ~Application();

		void Run();

	};

	//TODO: To be defined on the client
	Application* CreateApplication();
}
