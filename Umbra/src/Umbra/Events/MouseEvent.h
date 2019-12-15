#pragma once

#include <sstream>
#include "Event.h"

namespace Umbra {
	class MouseMoveEvent : public Event
	{
	public:
		inline int GetMouseX() const { return e_mouseX; }
		inline int GetMouseY() const { return e_mouseY; }

		EVENT_CLASS_CATEGORY(EventCategoryMouse | EventCategoryInput)
		EVENT_CLASS_TYPE(MouseMoved)
	protected:
		MouseMoveEvent(float x, float y) {
			this->e_mouseX = x;
			this->e_mouseY = y;
		}
		
		float e_mouseX;
		float e_mouseY;
	};

	class MouseButtonEvent : public Event
	{
	public:
		inline int GetMouseButton() const { return e_mouseButton; }

		EVENT_CLASS_CATEGORY(EventCategoryMouseButton | EventCategoryInput)
	protected:
		MouseButtonEvent(int mouseButton)
			: e_mouseButton(mouseButton) {}

		int e_mouseButton;
	};

	class MouseButtonPressed : public MouseButtonEvent
	{
	public:
		MouseButtonPressed(int mouseButton, int repeatCount) 
			: MouseButtonEvent(mouseButton), e_RepeatCount(repeatCount) {}

		std::string ToString() const override
		{
			std::stringstream ss;
			ss << "MouseButtonPressentEvent: " << e_mouseButton << " (" << e_RepeatCount << " repeats)";

			return ss.str();
		}

		EVENT_CLASS_TYPE(MouseButtonPressed)
	protected:
		int e_RepeatCount;
	};

	class MouseButtonReleased : public MouseButtonEvent
	{
	public:
		MouseButtonReleased(int mouseButton)
			: MouseButtonEvent(mouseButton) {}

		std::string ToString() const override
		{
			std::stringstream ss;
			ss << "MouseButtonReleased: " << e_mouseButton;
			return ss.str();
		}

		EVENT_CLASS_TYPE(MouseButtonReleased)
	};
}