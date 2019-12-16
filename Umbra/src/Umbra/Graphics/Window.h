#pragma once
#include <functional>
#include <string>
#include "../Core.h"

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
		virtual ~Window();
		virtual void OnUpdate() = 0;

		virtual unsigned int GetWidth() const = 0;
		virtual unsigned int GetHeight() const = 0;

		virtual void SetVSync(bool enabled) = 0;
		virtual bool IsVSync() const = 0;

		static Window* Create(const WindowOptions& props = WindowOptions());
	};
}
