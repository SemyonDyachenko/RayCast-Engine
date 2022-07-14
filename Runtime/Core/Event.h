#ifndef EVENT_H
#define EVENT_H

#include "Core.h"
#include <string>


namespace RayCast {

	enum class EventType
	{
		None = 0,
		MouseScrolled
	};

	class RAYCAST_API Event
	{
	public:
		virtual ~Event() = default;

		bool Handled = false;

		virtual EventType GetEventType() const = 0;
		virtual const char* GetName() const = 0;
		virtual int GetCategoryFlags() const = 0;
		virtual std::string ToString() const { return GetName(); }

	};

	class MouseScrollEvent : public Event {
	public:
		MouseScrollEvent(const float xOffset, const float yOffset)
			: m_XOffset(xOffset), m_YOffset(yOffset)
		{

		}

		EventType GetEventType() const  override {
			return EventType::MouseScrolled;
		}

		const char* GetName() const override {
			return "Mouse Scroll";
		}

		int GetCategoryFlags() const override {
			return 0;
		}

		float GetXOffset() const { return m_XOffset; }
		float GetYOffset() const { return m_YOffset; }

	private:
		float m_XOffset, m_YOffset;
	};

}

#endif