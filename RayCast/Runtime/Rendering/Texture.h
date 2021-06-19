#ifndef TEXTURE_H
#define TEXTURE_H



#include <string>
#include <GL/glew.h>
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

	const char * GetFilename();

private:
	GLuint id;
	int width;
	int height;
	int nrChannels;
	unsigned int type;
	const char* m_Filename;

};

#endif

