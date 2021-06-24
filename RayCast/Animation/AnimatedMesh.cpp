#pragma once
#include "../stdafx.h"
#include "AnimatedMesh.h"


AnimatedMesh::AnimatedMesh(std::vector<AnimatedVertex> vertices, std::vector<unsigned int> indices, std::vector<AnimatedTexture> textures)
{
	this->indices = indices;
    this->vertices = vertices;

	glCreateVertexArrays(1, &VAO);
	glBindVertexArray(VAO);

	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(AnimatedVertex), &vertices[0], GL_STATIC_DRAW);


	glGenBuffers(1, &this->EBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int), &indices[0], GL_STATIC_DRAW);
	


    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(AnimatedVertex), (void*)offsetof(AnimatedVertex,position));
    // vertex normals
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(AnimatedVertex), (void*)offsetof(AnimatedVertex, normal));
    // vertex texture coords
    glEnableVertexAttribArray(2);
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(AnimatedVertex), (void*)offsetof(AnimatedVertex, texcoord));
    // vertex tangent
    glEnableVertexAttribArray(3);
    glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, sizeof(AnimatedVertex), (void*)offsetof(AnimatedVertex, m_BoneIDs));
    // vertex bitangent
    glEnableVertexAttribArray(4);
    glVertexAttribPointer(4, 3, GL_FLOAT, GL_FALSE, sizeof(AnimatedVertex), (void*)offsetof(AnimatedVertex, m_Weights));


	glBindVertexArray(0);
}

AnimatedMesh::~AnimatedMesh()
{
}

void AnimatedMesh::OnRender(Shader& shader)
{
 

 
    glBindVertexArray(VAO);
    glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0);
    glBindVertexArray(0);

  
    glActiveTexture(GL_TEXTURE0);
}

