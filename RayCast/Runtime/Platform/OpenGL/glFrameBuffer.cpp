#include "../../../stdafx.h"
#include "glFrameBuffer.h"

static GLenum TextureTarget(bool multisampled) {
	return multisampled ? GL_TEXTURE_2D_MULTISAMPLE : GL_TEXTURE_2D;
}

static void CreateTextures(bool multisampled, unsigned int* id, unsigned int count) {
	glCreateTextures(TextureTarget(multisampled), count, id);
}

static void BindTexture(bool multisampled, unsigned int id) {
	glBindTexture(TextureTarget(multisampled), id);
}

static void AttachColorTexture(unsigned int id, int samples, GLenum internalFormat,GLenum foramt, unsigned int width, unsigned int height, int index) {
	bool multisampled = samples > 1;
	if (multisampled) {
		glTexImage2DMultisample(GL_TEXTURE_2D_MULTISAMPLE, samples, internalFormat, width, height, GL_FALSE);
	}
	else {
		glTexImage2D(GL_TEXTURE_2D, 0, internalFormat, width, height, 0, foramt, GL_UNSIGNED_BYTE, NULL);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

	}

	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0 + index, TextureTarget(multisampled), id, 0);
}


static void AttachDepthTexture(unsigned int id, int samples, GLenum format,GLenum attachmentType, unsigned int width, unsigned int height) {
	bool multisampled = samples > 1;
	if (multisampled) {
		glTexImage2DMultisample(GL_TEXTURE_2D_MULTISAMPLE, samples, format, width, height, GL_FALSE);
	}
	else {
		glTexStorage2D(GL_TEXTURE_2D, 1, format, width, height);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

	}

	glFramebufferTexture2D(GL_FRAMEBUFFER, attachmentType, TextureTarget(multisampled), id, 0);
}


static bool IsDepthFormat(FrameBufferTextureFormat format) {
	switch (format)
	{
		case FrameBufferTextureFormat::DEPTH24STENCIL8: return true;
	}
	return false;
}

glFrameBuffer::glFrameBuffer(const FrameBufferProps& props) : m_Props(props)
{

	for (auto spec : m_Props.Attachments.Attachments) {
		if (IsDepthFormat(spec.TextureFormat)) {
			m_DepthAttachmentSpec = spec;
		}
		else {
			m_ColorAttachmentSpecs.emplace_back(spec);
		}
	}


	Invalidate();
}

glFrameBuffer::~glFrameBuffer()
{
	glDeleteFramebuffers(1, &FBO);
	glDeleteTextures(1,&m_TextureID);
	glDeleteTextures(1,&m_DepthID);

	glDeleteTextures(m_ColorAttachments.size(), m_ColorAttachments.data());
	glDeleteTextures(1, &m_DepthAttachment);
}

void glFrameBuffer::Invalidate()
{
	if (FBO) {
		glDeleteFramebuffers(1, &FBO);
		glDeleteTextures(m_ColorAttachments.size(), m_ColorAttachments.data());
		glDeleteTextures(1, &m_DepthAttachment);
		glDeleteTextures(1, &m_TextureID);
		glDeleteTextures(1, &m_DepthID);

		m_ColorAttachments.clear();
		m_DepthAttachment = 0;
	}
	 
	glCreateFramebuffers(1, &FBO);
	glBindFramebuffer(GL_FRAMEBUFFER, FBO);

	bool multisample = m_Props.Samples > 1;

	if (m_ColorAttachmentSpecs.size()) 
	{
		m_ColorAttachments.resize(m_ColorAttachmentSpecs.size());
		CreateTextures(multisample, m_ColorAttachments.data(), m_ColorAttachments.size());

		for (size_t i = 0; i < m_ColorAttachments.size(); i++)
		{
			BindTexture(multisample, m_ColorAttachments[i]);
			switch (m_ColorAttachmentSpecs[i].TextureFormat) 
			{
				case FrameBufferTextureFormat::RGBA8:
					AttachColorTexture(m_ColorAttachments[i], m_Props.Samples, GL_RGBA8,GL_RGBA,m_Props.Width,m_Props.Height,i);
					break;
				case FrameBufferTextureFormat::RED_INTEGER:
					AttachColorTexture(m_ColorAttachments[i], m_Props.Samples, GL_R32I, GL_RED_INTEGER, m_Props.Width, m_Props.Height, i);
					break;


			}
		}
	}

	if (m_DepthAttachmentSpec.TextureFormat != FrameBufferTextureFormat::None) {
		CreateTextures(multisample, &m_DepthAttachment, 1);	
		BindTexture(multisample, m_DepthAttachment);
		switch (m_DepthAttachmentSpec.TextureFormat)
		{
			case FrameBufferTextureFormat::DEPTH24STENCIL8:
				AttachDepthTexture(m_DepthAttachment, m_Props.Samples, GL_DEPTH24_STENCIL8, GL_DEPTH_STENCIL_ATTACHMENT, m_Props.Width, m_Props.Height);
			break;
		}
	}
	
	if (m_ColorAttachments.size() > 1) {
		assert(m_ColorAttachments.size() <= 4);
		GLenum buffers[4] = { GL_COLOR_ATTACHMENT0,GL_COLOR_ATTACHMENT1,GL_COLOR_ATTACHMENT2,GL_COLOR_ATTACHMENT3 };
		glDrawBuffers(m_ColorAttachments.size(), buffers);
	}
	else if (m_ColorAttachments.empty()) {
		glDrawBuffer(GL_NONE);
	}

	if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
		ENGINE_ERROR("ERROR::FRAMEBUFFER:: Framebuffer is not complete!");
	
	/*glCreateTextures(GL_TEXTURE_2D, 1, &m_TextureID);
	glBindTexture(GL_TEXTURE_2D, m_TextureID);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, m_Props.Width, m_Props.Height, 0, GL_RGBA, GL_UNSIGNED_BYTE, NULL);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, m_TextureID, 0);

	glCreateTextures(GL_TEXTURE_2D,1, &m_DepthID);
	glBindTexture(GL_TEXTURE_2D, m_DepthID);
	glTexStorage2D(GL_TEXTURE_2D, 1, GL_DEPTH24_STENCIL8, m_Props.Width, m_Props.Height);
	//glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH24_STENCIL8, m_Props.Width, m_Props.Height, 0, GL_DEPTH_STENCIL, GL_UNSIGNED_INT_24_8, NULL);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);	
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);


	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_TEXTURE_2D, m_DepthID, 0);*/
	
	

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

void glFrameBuffer::Resize(unsigned int width, unsigned int height)
{
	m_Props.Width = width;
	m_Props.Height = height;

	Invalidate();
}

int  glFrameBuffer::ReadPixel(uint32_t index, int x, int y)
{
	glReadBuffer(GL_COLOR_ATTACHMENT0 + index);
	int pixelData;
	glReadPixels(x, y, 1, 1, GL_RED_INTEGER, GL_INT, &pixelData);
	return pixelData;
}
