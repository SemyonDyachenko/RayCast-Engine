
#include "FrameBuffer.h"

#include "../Platform/OpenGL/glFrameBuffer.h"

namespace RayCast {

	std::unique_ptr<FrameBuffer> FrameBuffer::Create(const FrameBufferProps& props) {
		return std::make_unique<glFrameBuffer>(props);
	}

}