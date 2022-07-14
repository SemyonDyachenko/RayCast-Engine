#ifndef ANIMATED_MODEL_H
#define ANIMATED_MODEL_H

#include <vector>
#include <string>
#include "AnimatedMesh.h"
#include <map>
#include <assimp/scene.h>
#include "assimp_utils.h"
#include <assimp/Importer.hpp>
#include <assimp/postprocess.h>
#include "../Rendering/Texture.h"
#include "../Rendering/Shader.h"

namespace RayCast {

	struct BoneInfo
	{
		int id;
		glm::mat4 offset;

	};


	class RAYCAST_API AnimatedModel {
	public:
		AnimatedModel(std::string const path);

		void load(std::string const path);

		void processNode(aiNode* node, const aiScene* scene);

		void Draw(Shader& shader);

		void AddTexture(Texture& texture);
		void AddTextures(std::vector<Texture>& texture);

		std::map<std::string, BoneInfo> GetBoneInfoMap();
		int GetBoneCounter();
	private:
		std::map<std::string, BoneInfo> m_BoneInfoMap;
		int m_BoneCounter = 0;

		std::vector<Texture> m_Textures;

		std::vector<AnimatedTexture> m_Textures_loaded;
		std::vector<AnimatedMesh>  m_Meshes;
		std::string directory;
		bool gammaCorrection;

		void SetVertexBoneDataToDefault(AnimatedVertex& vertex);

		AnimatedMesh processMesh(aiMesh* mesh, const aiScene* scene);

		void SetVertexBoneData(AnimatedVertex& vertex, int boneID, float weight);

		void ExtractBoneWeightForVertices(std::vector<AnimatedVertex>& vertices, aiMesh* mesh, const aiScene* scene);

	};

}

#endif