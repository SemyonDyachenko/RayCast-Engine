#ifndef GL_FRAME_BUFFER_H
#define GL_FRAME_BUFFER_H

#include <GL/glew.h>
#include "../../Rendering/FrameBuffer.h"
#include "../../Core/Log.h"

class glFrameBuffer : public FrameBuffer
{
public:
	glFrameBuffer(const FrameBufferProps & props);
	virtual ~glFrameBuffer();

	void Invalidate();

	unsigned int GetTextureID(unsigned int index = 0) const  override {
		return m_ColorAttachments[index];
	}
	unsigned int GetDepthID() const  override {
		return m_DepthID;
	}

	
	const FrameBufferProps& GetFrameBufferProps() const override { return m_Props;  }

	virtual void Bind() override;
	virtual void Unbind() override;

	virtual void Resize(unsigned int width, unsigned int height) override;

	virtual int  ReadPixel(uint32_t index, int x, int y) override;

private:
	unsigned int FBO = 0;
	unsigned int m_TextureID = 0, m_DepthID = 0;
	FrameBufferProps m_Props;
	std::vector<FrameBufferTextureSpecification> m_ColorAttachmentSpecs;
	FrameBufferTextureSpecification m_DepthAttachmentSpec = FrameBufferTextureFormat::None;

	std::vector<unsigned int> m_ColorAttachments;
	unsigned int m_DepthAttachment = 0;

	// Inherited via FrameBuffer

};

#endif