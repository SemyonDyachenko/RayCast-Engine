#pragma once

#include "../Entity/Entity.h"

namespace RayCast {

	class ClipboardUtils
	{
	public:

		static void AddEntityToClipboard(Entity* entity)
		{
			m_Entity = entity;
		}

		static bool HasEntity()
		{
			if (m_Entity)
				return true;

			return false;
		}

		static Entity* GetEntityFromClipboard()
		{
			if (m_Entity)
				return m_Entity;
			return nullptr;
		}

	private:
		static Entity* m_Entity;
	};

}