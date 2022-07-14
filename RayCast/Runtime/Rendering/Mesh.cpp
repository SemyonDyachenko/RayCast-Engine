#include "../../stdafx.h"
#include "Mesh.h"
#include <gtc/matrix_transform.hpp>
#include <chrono>


Mesh::Mesh(Vertex* vertices, int verticesCount, GLuint* indices, int indicesCount, std::string filename)
{
	m_Filename = filename;
	this->m_verticesCount = verticesCount;
	m_numberOfIndices = indicesCount;
	//this->ModelMatrix = modelMatrix;

	this->vertices = new Vertex[verticesCount];
	for (size_t i = 0; i < verticesCount; i++)
	{
		this->vertices[i] = vertices[i];
	}

	glCreateVertexArrays(1, &VAO);
	glBindVertexArray(VAO);

	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, verticesCount * sizeof(Vertex), this->vertices, GL_STATIC_DRAW);

	if (this->m_numberOfIndices > 0)
	{
		glGenBuffers(1, &this->EBO);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->EBO);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, this->m_numberOfIndices * sizeof(GLuint), indices, GL_STATIC_DRAW);
	}


	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)offsetof(Vertex, position));
	glEnableVertexAttribArray(0);
	//Color
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)offsetof(Vertex, color));
	glEnableVertexAttribArray(1);
	//Texcoord
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)offsetof(Vertex, texcoord));
	glEnableVertexAttribArray(2);
	//Normal
	glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)offsetof(Vertex, normal));
	glEnableVertexAttribArray(3);

	//glVertexAttribIPointer(4, 4, GL_INT, sizeof(Vertex),(GLvoid*)offsetof(Vertex, m_BoneIDs));
	//glEnableVertexAttribArray(4);

	//glVertexAttribIPointer(5, 4, GL_INT, sizeof(Vertex), (GLvoid*)offsetof(Vertex, m_Weights));
	//glEnableVertexAttribArray(5);


	glBindVertexArray(0);

}

/*void Mesh::UpdateModelMatrix(glm::mat4 ModelMatrix)
{
	this->ModelMatrix = ModelMatrix;
}*/

Mesh::~Mesh()
{
	glDeleteVertexArrays(1, &this->VAO);
	glDeleteBuffers(1, &this->VBO);
	glDeleteBuffers(1, &this->EBO);
}

void Mesh::SetSolidColor(glm::vec3& color)
{
	m_SolidColor = color;
}

void Mesh::OnRender(Shader& shader)
{
	if (m_UseSolidColor) {
		shader.use();
		//shader.SetVec3("u_Color", m_SolidColor);
		shader.setBool("useTextureMapping", false);
		shader.SetVec3("SolidAlbedoColor", m_SolidColor);
	}

	glBindVertexArray(VAO);
	if (this->m_numberOfIndices == 0)
		glDrawArrays(GL_TRIANGLES, 0, this->m_verticesCount);
	else
		glDrawElements(GL_TRIANGLES, this->m_numberOfIndices, GL_UNSIGNED_INT, 0);
	glBindVertexArray(0);
	glUseProgram(0);
	glActiveTexture(0);
	glBindTexture(GL_TEXTURE_2D, 0);
}
