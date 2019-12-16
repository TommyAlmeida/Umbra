#include "ubpch.h"
#include "Umbra/Graphics/Window.h"
#include "WinFrame.h"
#include <Umbra\Events\General\WindowEvent.h>
#include <Umbra\Events\KeyEvent.h>
#include <Umbra\Events\MouseEvent.h>

namespace Umbra {
	
	static uint8_t s_GLFWWindowCount = 0;

	static void GLFWErrorCallback(int error, const char* description)
	{
		UB_CORE_ERROR("GLFW Error ({0}): {1}", error, description);
	}


	WinFrame::WinFrame(const WindowOptions& options)
	{
		Init(options);
	}

	WinFrame::~WinFrame()
	{
		Shutdown();
	}

	Scope<Window> Window::Create(const WindowOptions& options) 
	{
		return CreateScope<WinFrame>(options);
	}

	void WinFrame::OnUpdate()
	{
		glfwPollEvents();
		//TODO: We need to swap buffers or we will have troubles
	}

	void WinFrame::SetVSync(bool enabled)
	{
		enabled ? glfwSwapInterval(1) : glfwSwapInterval(0);
		wf_Data.VSync = enabled;
	}

	bool WinFrame::IsVSync() const
	{
		return wf_Data.VSync;
	}

	void WinFrame::Init(const WindowOptions& options)
	{
		wf_Data.Title = options.Title;
		wf_Data.Width = options.Width;
		wf_Data.Height = options.Height;

		UB_CORE_INFO("Creating window {0} ({1}, {2})", options.Title, options.Width, options.Height);

		if (s_GLFWWindowCount == 0) 
		{
			int success = glfwInit();

			UB_CORE_FATAL("{0}: Could not intialize GLFW!", success);
			glfwSetErrorCallback(GLFWErrorCallback);
		}

		{
			gl_Window = glfwCreateWindow((int)options.Width, (int)options.Height, wf_Data.Title.c_str(), nullptr, nullptr);
			++s_GLFWWindowCount;
		}

		glfwSetWindowUserPointer(gl_Window, &wf_Data);
		SetVSync(true);

		glfwSetWindowSizeCallback(gl_Window, [](GLFWwindow* window, int width, int height)
			{
				WindowData& data = *(WindowData*) glfwGetWindowUserPointer(window);
				data.Width = width;
				data.Height = height;

				WindowResizeEvent event(width, height);
				data.EventCallback(event);
			});

		glfwSetWindowCloseCallback(gl_Window, [](GLFWwindow* window)
			{
				WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
				WindowCloseEvent event;
				data.EventCallback(event);
			});

		glfwSetKeyCallback(gl_Window, [](GLFWwindow* window, int key, int scancode, int action, int mods)
			{
				WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

				switch (action)
				{
				case GLFW_PRESS:
				{
					KeyPressedEvent event(key, 0);
					data.EventCallback(event);
					break;
				}
				case GLFW_RELEASE:
				{
					KeyReleasedEvent event(key);
					data.EventCallback(event);
					break;
				}
				case GLFW_REPEAT:
				{
					KeyPressedEvent event(key, 1);
					data.EventCallback(event);
					break;
				}
				}
			});

		glfwSetCharCallback(gl_Window, [](GLFWwindow* window, unsigned int keycode)
			{
				WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

				KeyTypedEvent event(keycode);
				data.EventCallback(event);
			});

		glfwSetMouseButtonCallback(gl_Window, [](GLFWwindow* window, int button, int action, int mods)
			{
				WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

				switch (action)
				{
				case GLFW_PRESS:
				{
					MouseButtonPressedEvent event(button);
					data.EventCallback(event);
					break;
				}
				case GLFW_RELEASE:
				{
					MouseButtonReleasedEvent event(button);
					data.EventCallback(event);
					break;
				}
				}
			});

		glfwSetCursorPosCallback(gl_Window, [](GLFWwindow* window, double xPos, double yPos)
			{
				WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

				MouseMovedEvent event((float)xPos, (float)yPos);
				data.EventCallback(event);
			});
	}

	void WinFrame::Shutdown()
	{
		glfwDestroyWindow(gl_Window);
		--s_GLFWWindowCount;

		if (s_GLFWWindowCount == 0)
		{
			glfwTerminate();
		}
	}
}