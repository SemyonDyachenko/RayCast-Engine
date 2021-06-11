#include "Model.h"

Model::Model(glm::vec3 position, std::vector<Mesh*>& meshes) : m_Position(position),  m_Meshes(meshes)
{
	for (auto* i : meshes) {
		m_Meshes.push_back(new Mesh(*i));
	}

	for (auto& i : m_Meshes) {
		// set position ...
	}

	m_Textures = std::vector<Texture*>();
}

Model::Model(glm::vec3 position,  const char* obj_filename) : m_Position(position)
{
	m_Objloader = new OBJLoader();

	m_ModelMatrix = glm::mat4(1.f);
	m_Position = position;
	m_ModelMatrix = glm::translate(m_ModelMatrix, m_Position);

	std::vector<Vertex> rawModel = m_Objloader->loadObjModel(obj_filename);
	this->m_Meshes.push_back(new Mesh(rawModel.data(), rawModel.size(), NULL, 0,m_ModelMatrix));

	m_Textures = std::vector<Texture*>();
}

Model::Model(const char* obj_filename)
{
	m_Objloader = new OBJLoader();

	m_ModelMatrix = glm::mat4(1.f);

	std::vector<Vertex> rawModel = m_Objloader->loadObjModel(obj_filename);
	this->m_Meshes.push_back(new Mesh(rawModel.data(), rawModel.size(), NULL, 0, m_ModelMatrix));

	m_Textures = std::vector<Texture*>();
}



void Model::AddTexture(Texture* texture)
{
	m_Textures.push_back(texture);
}

void Model::AddTextures(std::vector<Texture*> textures)
{
	m_Textures = textures;
}

void Model::SetPosition(glm::vec3 position)
{
	m_Position = position;
	m_ModelMatrix = glm::translate(m_ModelMatrix, m_Position);

	for (auto& i : m_Meshes) {
		i->UpdateModelMatrix(m_ModelMatrix);
	}
}

void Model::Move(int direction, float DeltaTime, float velocity)
{
	if (direction == 0) {
		m_Position.z += velocity * DeltaTime;
	}
	else if (direction == 1) {
		m_Position.z -= velocity * DeltaTime;
	}
	else if (direction == 2) {
		m_Position.x -= velocity * DeltaTime;
	}
	else if (direction == 3) {
		m_Position.x += velocity * DeltaTime;
	}

	m_ModelMatrix = glm::mat4(1.f);
	m_ModelMatrix = glm::translate(m_ModelMatrix, m_Position);
	
	for (auto& i : m_Meshes) {
		i->UpdateModelMatrix(m_ModelMatrix);
	}
}

void Model::OnRender(Shader * shader)
{
	shader->use();
	shader->SetMat4("ModelMatrix", m_ModelMatrix);


	for (auto& i : m_Meshes) {
		shader->use();

		if (!m_Textures.empty()) {
			for (size_t i = 0; i < m_Textures.size(); i++) {
				m_Textures[i]->bind(m_Textures[i]->GetId());
			}
		}
		i->OnRender(*shader);
	}
}

glm::mat4& Model::GetModelMatrix()
{
	return m_ModelMatrix;
}

glm::vec3 Model::GetPosition()
{
	return glm::vec3();
}

Model::~Model()
{
	for (auto*& i : m_Meshes)
		delete i;
}
