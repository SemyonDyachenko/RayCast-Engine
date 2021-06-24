#include "../../../stdafx.h"
#include "glFrameBuffer.h"

glFrameBuffer::glFrameBuffer(const FrameBufferProps& props) : m_Props(props)
{
	Invalidate();
}

glFrameBuffer::~glFrameBuffer()
{
	glDeleteFramebuffers(1, &FBO);
}

void glFrameBuffer::Invalidate()
{
	glCreateFramebuffers(1, &FBO);
	glBindFramebuffer(GL_FRAMEBUFFER, FBO);

	glCreateTextures(GL_TEXTURE_2D, 1, &m_TextureID);
	glBindTexture(GL_TEXTURE_2D, m_TextureID);	
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, m_Props.Width, m_Props.Height, 0, GL_RGBA, GL_UNSIGNED_BYTE, nullptr);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, m_TextureID, 0);

	glCreateTextures(GL_TEXTURE_2D, 1, &m_DepthID);
	glBindTexture(GL_TEXTURE_2D, m_DepthID);
	glTexStorage2D(GL_TEXTURE_2D, 1, GL_DEPTH24_STENCIL8, m_Props.Width, m_Props.Height);
	// glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH24_STENCIL8, m_Specification.Width, m_Specification.Height, 0,
	// 	GL_DEPTH_STENCIL, GL_UNSIGNED_INT_24_8, NULL);
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_TEXTURE_2D, m_DepthID, 0);
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

void glFrameBuffer::Bind()
{
	glBindFramebuffer(GL_FRAMEBUFFER, FBO);
}

void glFrameBuffer::Unbind()
{
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
}
