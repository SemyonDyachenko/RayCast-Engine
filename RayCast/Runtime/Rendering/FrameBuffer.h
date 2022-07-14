#ifndef FRAME_BUFFER_H
#define FRAME_BUFFER_H

#include <memory>


enum class FrameBufferTextureFormat {
	None = 0,
	RGBA8,
	RED_INTEGER,
	DEPTH24STENCIL8,
	Depth = DEPTH24STENCIL8
};

struct FrameBufferTextureSpecification {
	FrameBufferTextureSpecification() = default;
	FrameBufferTextureSpecification(FrameBufferTextureFormat format) : TextureFormat(format) {}

	FrameBufferTextureFormat TextureFormat;

};

struct FrameBufferAttachmentSpecification {
	FrameBufferAttachmentSpecification() = default;
	FrameBufferAttachmentSpecification(const std::initializer_list<FrameBufferTextureSpecification> attachments)  : Attachments(attachments) {}

	std::vector<FrameBufferTextureSpecification> Attachments;
};

struct FrameBufferProps {
	unsigned int Width;
	unsigned int Height;

	FrameBufferAttachmentSpecification Attachments;

	unsigned int Samples = 1;

};

class FrameBuffer {
public:


	virtual ~FrameBuffer() = default;

	virtual const FrameBufferProps& GetFrameBufferProps() const = 0;

	virtual unsigned int GetTextureID(unsigned int index = 0) const = 0;
	virtual unsigned int GetDepthID() const = 0;

	static std::unique_ptr<FrameBuffer> Create(const FrameBufferProps& props);

	virtual void Resize(unsigned int width, unsigned int height) = 0;

	virtual int  ReadPixel(uint32_t index, int x, int y) = 0;

	virtual void Bind() = 0;
	virtual void Unbind() = 0;
};


#endif

