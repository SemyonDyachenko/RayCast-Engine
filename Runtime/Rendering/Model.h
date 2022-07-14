#ifndef MODEL_H
#define MODEL_H

#include "Texture.h"
#include <iostream>
#include <vector>
#include "Mesh.h"
#include "OBJLoader.h"

#include <assimp/scene.h>

namespace RayCast {

	class Model {
	private:
		std::vector<Texture*> m_Textures;
		std::vector<Mesh*> m_Meshes;
		glm::vec3 m_Position;

		OBJLoader* m_Objloader;

		glm::mat4 m_ModelMatrix;

	public:
		Model(glm::vec3 position, std::vector<Mesh*>& meshes);
		Model(glm::vec3 position, const char* obj_filename);
		Model(const char* obj_filename);


		void AddTexture(Texture* texture);
		void AddTextures(std::vector<Texture*> textures);

		void SetPosition(glm::vec3 position);
		void Move(int direction, float DeltaTime, float velocity);

		void OnRender(Shader* shader);

		glm::mat4& GetModelMatrix();

		glm::vec3 GetPosition();

		virtual ~Model();
	};

}

#endif