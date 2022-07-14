
#ifndef CUBEMAP_H
#define CUBEMAP_H

#include <GL/glew.h>

#include <iostream>
#include <vector>
#include <string>

#include "../Core/Log.h"
#include "Shader.h"

static std::vector<std::string> DefaultFace  = {
     "resources/images/icons/editor/skybox/right.jpg",
    "resources/images/icons/editor/skybox/left.jpg",
    "resources/images/icons/editor/skybox/bottom.jpg",
    "resources/images/icons/editor/skybox/top.jpg",
    "resources/images/icons/editor/skybox/front.jpg",
    "resources/images/icons/editor/skybox/back.jpg"
};

class Cubemap
{
public:
	Cubemap();

    static unsigned int LoadCubemap(std::vector<std::string> faces);
    
    unsigned int GetTextureId() { return m_TextureID; }

    void Render(Shader& shader);

	virtual ~Cubemap() = default;

private:
    unsigned int m_TextureID;
    GLuint m_VaoId;
    GLuint m_VboId;

    float Size = 500.f;

};

#endif