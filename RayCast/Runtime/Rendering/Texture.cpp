#include "Texture.h"

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"


Texture::Texture(const char * filename, GLenum type)
{
	this->m_Filename = filename;
	this->type = type;
	stbi_set_flip_vertically_on_load(true);

	unsigned char* image = stbi_load(filename, &this->width, &this->height, &this->nrChannels,0);

	glGenTextures(1, &this->id);
	glBindTexture(GL_TEXTURE_2D,this->id);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

	if (image) {
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, this->width, this->height, 0, GL_RGB, GL_UNSIGNED_BYTE, image);
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else {
		std::cout << "ERROR::TEXTURE::LOADFROMFILE::TEXTURE_LOADING_FAILED: " << filename << "\n";
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

void Texture::unbind()
{
	glActiveTexture(0);
	glBindTexture(GL_TEXTURE_2D, 0);
}

GLuint Texture::GetId()
{
	return id;
}

const char* Texture::GetFilename()
{
	return m_Filename;
}
