#pragma once

#include "Umbra\Core.h"
#include <Umbra\Events\Event.h>
#include <Umbra\Events\General\WindowEvent.h>
#include <Umbra\Graphics\Window.h>

namespace Umbra {
	class UMBRA_API Application
	{
	public:
		Application();
		virtual ~Application();

		void Run();

		void OnEvent(Event& e);

		inline Window& GetWindow() { return *window; }

		inline static Application& Get() { return *Instance; }
	private:
		std::unique_ptr<Window> window;
		bool a_Running;

		static Application* Instance;

		bool OnWindowClose(WindowCloseEvent& e);
		bool OnWindowResize(WindowResizeEvent& e);
	};

	//To be defined on the client
	Application* CreateApplication();
}
