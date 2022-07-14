#ifndef TEXTURE_H
#define TEXTURE_H



#include <string>
#include <glad/glad.h>
#include <iostream>


class Texture
{
public:
	Texture(const char * filename,GLenum type);
	virtual ~Texture();

	int GetWidth() const { return width; }
	int GetHeight() const { return height; }

	void bind(const GLint texture_unit);
	void unbind();

	GLuint GetId();

	std::string & GetFilename();

private:
	GLuint id;
	int width;
	int height;
	int nrChannels;
	unsigned int type;
	std::string m_Filename;

};

#endif

