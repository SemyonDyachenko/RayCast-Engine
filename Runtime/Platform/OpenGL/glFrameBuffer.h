#ifndef GL_FRAME_BUFFER_H
#define GL_FRAME_BUFFER_H

#include <GL/glew.h>
#include "../../Rendering/FrameBuffer.h"


class glFrameBuffer : public RayCast::FrameBuffer
{
public:
	glFrameBuffer(const RayCast::FrameBufferProps& props);
	virtual ~glFrameBuffer();

	void Invalidate();

	virtual unsigned int GetTextureID() const  override {
		return m_TextureID;
	}

	const RayCast::FrameBufferProps& GetFrameBufferProps() const override { return m_Props; }

	virtual void Bind() override;
	virtual void Unbind() override;

private:
	unsigned int FBO;
	unsigned int m_TextureID, m_DepthID;
	RayCast::FrameBufferProps m_Props;

};

#endif