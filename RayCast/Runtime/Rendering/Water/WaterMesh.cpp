#include "WaterMesh.h"


WaterMesh::WaterMesh(std::vector<WaterTile*> waterSurface)
	: m_WaterSurface(waterSurface)
{
	m_WaterShader = new Shader("resources/shaders/water/water_vertex_shader.glsl","resources/shaders/water/water_fragment_shader.glsl");

	std::vector<glm::vec3> vertices(4);
	vertices.push_back({ -1, -1, -1 });
	vertices.push_back({ 1, 1, -1 });
	vertices.push_back({ 1, -1, -1 });
	vertices.push_back({ 1, -1, 1 });

	std::vector<Vertex> finalVertices;
	finalVertices.resize(vertices.size(), Vertex());
	
	for(size_t i =0;i < finalVertices.size();i++)
	{
		finalVertices[i].position = vertices[i];
		finalVertices[i].normal = glm::vec3(0, 1, 0);
		finalVertices[i].color = glm::vec3(1, 1, 1);
		finalVertices[i].texcoord = glm::vec2(1, 1);
		
	}

	auto vt = OBJLoader::loadObjModel("resources/vanilla/obj/cube.obj");
	
	m_Mesh = new Mesh(vt.data(), vt.size(), 0, 0);
}


void WaterMesh::AddReflectionAndRefractionTextures(int reflectionId, int refractionId)
{
	m_ReflectionTexID = reflectionId;
	m_RefractionTexID = reflectionId;
}

void WaterMesh::Render(EditorCamera* camera)
{
	m_WaterShader->use();
	
	m_WaterShader->SetMat4("ProjectionMatrix", camera->GetProjectionMatrix());
	m_WaterShader->SetMat4("ViewMatrix", camera->GetViewMatrix());

	glActiveTexture(GL_TEXTURE0 + m_ReflectionTexID);
	glBindTexture(GL_TEXTURE_2D, m_ReflectionTexID);
	glActiveTexture(GL_TEXTURE0 + m_RefractionTexID);
	glBindTexture(GL_TEXTURE_2D, m_RefractionTexID);

	m_WaterShader->setInt("reflectionTexture", m_ReflectionTexID);
	m_WaterShader->setInt("refractionTexture", m_RefractionTexID);
	
	for(WaterTile* tile : m_WaterSurface)
	{
		glm::mat4 transform = glm::translate(glm::mat4(1.0f), glm::vec3(tile->GetX(), tile->GetHeight(), tile->GetZ())) *
			glm::toMat4(glm::quat(glm::vec3(0.0f))) *  glm::scale(glm::mat4(1.0f), glm::vec3(tile->GetScale()));
		m_WaterShader->use();
		m_WaterShader->SetMat4("ModelMatrix", transform);
		m_Mesh->OnRender(*m_WaterShader);
	}

	m_WaterShader->unuse();
}
