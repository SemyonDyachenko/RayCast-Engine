#ifndef FRAME_BUFFER_H
#define FRAME_BUFFER_H

#include <memory>
#include "../Core/Core.h"

namespace RayCast {


	struct FrameBufferProps {
		unsigned int Width;
		unsigned int Height;
		unsigned int Samples = 1;

	};

	class RAYCAST_API FrameBuffer {
	public:


		virtual ~FrameBuffer() = default;

		virtual const FrameBufferProps& GetFrameBufferProps() const = 0;

		virtual unsigned int GetTextureID() const = 0;

		static std::unique_ptr<FrameBuffer> Create(const FrameBufferProps& props);

		virtual void Bind() = 0;
		virtual void Unbind() = 0;
	};

}

#endif

