#include "Cubemap.h"

#include "stb_image.h"

namespace RayCast {

    Cubemap::Cubemap()
    {
        float skyboxVertices[] = {
            // positions          
            -Size,  Size, -Size,
            -Size, -Size, -Size,
             Size, -Size, -Size,
             Size, -Size, -Size,
             Size,  Size, -Size,
            -Size,  Size, -Size,

            -Size, -Size,  Size,
            -Size, -Size, -Size,
            -Size,  Size, -Size,
            -Size,  Size, -Size,
            -Size,  Size,  Size,
            -Size, -Size,  Size,

             Size, -Size, -Size,
             Size, -Size,  Size,
             Size,  Size,  Size,
             Size,  Size,  Size,
             Size,  Size, -Size,
             Size, -Size, -Size,

            -Size, -Size,  Size,
            -Size,  Size,  Size,
             Size,  Size,  Size,
             Size,  Size,  Size,
             Size, -Size,  Size,
            -Size, -Size,  Size,

            -Size,  Size, -Size,
             Size,  Size, -Size,
             Size,  Size,  Size,
             Size,  Size,  Size,
            -Size,  Size,  Size,
            -Size,  Size, -Size,

            -Size, -Size, -Size,
            -Size, -Size,  Size,
             Size, -Size, -Size,
             Size, -Size, -Size,
            -Size, -Size,  Size,
             Size, -Size,  Size
        };


        glGenVertexArrays(1, &m_VaoId);
        glGenBuffers(1, &m_VboId);
        glBindVertexArray(m_VaoId);
        glBindBuffer(GL_ARRAY_BUFFER, m_VboId);
        glBufferData(GL_ARRAY_BUFFER, sizeof(skyboxVertices), &skyboxVertices, GL_STATIC_DRAW);
        glEnableVertexAttribArray(0);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);

        m_TextureID = LoadCubemap(DefaultFace);
    }

    unsigned int Cubemap::LoadCubemap(std::vector<std::string> faces)
    {
        unsigned int textureID;
        glGenTextures(1, &textureID);
        glBindTexture(GL_TEXTURE_CUBE_MAP, textureID);

        int width, height, nrChannels;
        for (unsigned int i = 0; i < faces.size(); i++)
        {
            stbi_set_flip_vertically_on_load(true);
            unsigned char* data = stbi_load(faces[i].c_str(), &width, &height, &nrChannels, 0);
            if (data)
            {
                glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i,
                    0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data
                );
                stbi_image_free(data);
            }
            else
            {
                std::cout << "Cubemap tex failed to load at path: " << faces[i] << std::endl;
                stbi_image_free(data);
            }
        }
        glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);


        return textureID;
    }

    void Cubemap::Render(Shader& shader)
    {

        glDepthFunc(GL_LEQUAL);
        shader.use();
        glBindVertexArray(m_VaoId);
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_CUBE_MAP, m_TextureID);
        glDrawArrays(GL_TRIANGLES, 0, 36);
        glBindVertexArray(0);
        glDepthFunc(GL_LESS); // set 
    }

}