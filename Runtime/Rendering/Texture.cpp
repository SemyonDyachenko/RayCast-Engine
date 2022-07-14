#include "Texture.h"

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

namespace  RayCast {


	Texture::Texture(const char* filename, GLenum type)
	{
		this->m_Filename = filename;
		this->type = type;

		unsigned char* image = stbi_load(filename, &this->width, &this->height, &this->nrChannels, 0);

		glGenTextures(1, &this->id);

		if (image) {
			GLenum format;
			if (nrChannels == 1)
				format = GL_RED;
			else if (nrChannels == 3)
				format = GL_RGB;
			else if (nrChannels == 4)
				format = GL_RGBA;

			glBindTexture(GL_TEXTURE_2D, this->id);
			glTexImage2D(GL_TEXTURE_2D, 0, format, this->width, this->height, 0, format, GL_UNSIGNED_BYTE, image);
			glGenerateMipmap(GL_TEXTURE_2D);

			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);


		}
		else {
			ENGINE_INFO("ERROR::TEXTURE::LOADFROMFILE::TEXTURE_LOADING_FAILED: ", filename);
		}


		glActiveTexture(0);
		glBindTexture(GL_TEXTURE_2D, 0);
		stbi_image_free(image);
	}

	Texture::~Texture()
	{
		glDeleteTextures(1, &this->id);
	}

	void Texture::bind(const GLint texture_unit)
	{
		glActiveTexture(GL_TEXTURE0 + texture_unit);
		glBindTexture(GL_TEXTURE_2D, this->id);
	}

	void Texture::bind()
	{
		glActiveTexture(GL_TEXTURE0 + GetId());
		glBindTexture(GL_TEXTURE_2D, this->id);
	}

	void Texture::unbind()
	{
		glActiveTexture(0);
		glBindTexture(GL_TEXTURE_2D, 0);
	}

	GLuint Texture::GetId()
	{
		return id;
	}

	std::string& Texture::GetFilename()
	{
		return m_Filename;
	}

}