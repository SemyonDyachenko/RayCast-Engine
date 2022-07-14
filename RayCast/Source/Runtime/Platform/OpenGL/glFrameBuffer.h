#ifndef GL_FRAME_BUFFER_H
#define GL_FRAME_BUFFER_H

#include <glad/glad.h>
#include "../../Rendering/FrameBuffer.h"


class glFrameBuffer : public FrameBuffer
{
public:
	glFrameBuffer(const FrameBufferProps & props);
	virtual ~glFrameBuffer();

	void Invalidate();

	virtual unsigned int GetTextureID() const  override {
		return m_TextureID;
	}

	const FrameBufferProps& GetFrameBufferProps() const override { return m_Props;  }

	virtual void Bind() override;
	virtual void Unbind() override;

private:
	unsigned int FBO;
	unsigned int m_TextureID, m_DepthID;
	FrameBufferProps m_Props;

};

#endif