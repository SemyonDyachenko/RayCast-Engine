#ifndef LAYER_H
#define LAYER_H

#include "Core.h"
#include <string>

namespace RayCast {

	class RAYCAST_API Layer {
	public:
		Layer() {};
		virtual ~Layer() = default;

		virtual void Attach() {}
		virtual void Detach() {}
		virtual void OnEvent() = 0;
		virtual void Update(float dt) = 0;
		virtual void Render() = 0;

		const std::string GetName() const { return m_Name; }
	protected:
		std::string m_Name = " ";
	};

}

#endif