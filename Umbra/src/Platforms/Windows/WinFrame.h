#pragma once

#include "Umbra\Graphics\Window.h"
#include <GLFW/glfw3.h>

namespace Umbra {
	class WinFrame : public Window
	{
	public:
		WinFrame(const WindowOptions& options);
		virtual ~WinFrame();

		void OnUpdate() override;

		inline unsigned int GetWidth() const override { return wf_Data.Width; }
		inline unsigned int GetHeight() const override { return wf_Data.Height; }

		// Window attributes
		inline void SetEventCallback(const EventCallbackFn& callback) override { wf_Data.EventCallback = callback; }
		
		void SetVSync(bool enabled) override;
		bool IsVSync() const override;

	private:
		virtual void Init(const WindowOptions& options);
		virtual void Shutdown();

	protected:
		GLFWwindow* gl_Window;

		struct WindowData
		{
			std::string Title;
			unsigned int Width, Height;
			bool VSync;

			EventCallbackFn EventCallback;
		};

		WindowData wf_Data;
	};
}