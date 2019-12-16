#include "ubpch.h"
#include "Application.h"

#include "Platforms/Windows/WinFrame.h"

namespace Umbra {
	Application* Application::Instance = nullptr;

	Application::Application()
	{
		Instance = this;
		window = Window::Create();
		window->SetEventCallback(UB_BIND_EVENT_FN(Application::OnEvent));
	}

	Application::~Application()
	{
	}

	void Application::Run()
	{
		while (a_Running) {
		
			window->OnUpdate();
		}
	}

	void Application::OnEvent(Event& e)
	{
		EventDispatcher dispatcher(e);

		dispatcher.Dispatch<WindowCloseEvent>(UB_BIND_EVENT_FN(Application::OnWindowClose));
		dispatcher.Dispatch<WindowResizeEvent>(UB_BIND_EVENT_FN(Application::OnWindowResize));
	}

	bool Application::OnWindowClose(WindowCloseEvent& e)
	{
		a_Running = false;
		return true;
	}

	bool Application::OnWindowResize(WindowResizeEvent& e)
	{
		return false;
	}
}