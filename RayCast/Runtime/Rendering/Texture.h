#ifndef TEXTURE_H
#define TEXTURE_H


#include <GL/glew.h>
#include <string>
#include <iostream>
#include "../Core/Log.h"

class Texture
{
public:
	Texture(const char * filename);
	virtual ~Texture();

	int GetWidth() const { return width; }
	int GetHeight() const { return height; }

	void LoadFromFile(const char * filename);

	void bind(const GLint texture_unit);
	void bind();
	void unbind();

	GLuint GetId();

	std::string GetFilename();

private:
	GLuint id;
	int width;
	int height;
	int nrChannels;
	unsigned int type;
	std::string m_Filename;

};

#endif

