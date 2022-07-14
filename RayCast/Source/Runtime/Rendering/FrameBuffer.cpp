#include "../../stdafx.h"
#include "FrameBuffer.h"

#include "../Platform/OpenGL/glFrameBuffer.h"

std::unique_ptr<FrameBuffer> FrameBuffer::Create(const FrameBufferProps& props) {
	return std::make_unique<glFrameBuffer>(props);
}