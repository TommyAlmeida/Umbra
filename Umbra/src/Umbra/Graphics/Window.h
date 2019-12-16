#pragma once
#include <functional>
#include <string>

#include "Umbra\Core.h"
#include <Umbra\Events\Event.h>

namespace Umbra {

	struct WindowOptions {
		std::string Title;
		unsigned int Width;
		unsigned int Height;

		WindowOptions(const std::string& title = "Umbra Engine", 
			unsigned int width = 1280,
			unsigned int height = 720
		) :  Title(title), Width(width), Height(height) {}
	};

	class UMBRA_API Window
	{
	public:
		using EventCallbackFn = std::function<void(Event&)>;

		virtual ~Window();
		virtual void OnUpdate() = 0;

		virtual unsigned int GetWidth() const = 0;
		virtual unsigned int GetHeight() const = 0;

		virtual void SetEventCallback(const EventCallbackFn& callback) = 0;

		virtual void SetVSync(bool enabled) = 0;
		virtual bool IsVSync() const = 0;

		static Scope<Window> Create(const WindowOptions& props = WindowOptions());
	};
}
