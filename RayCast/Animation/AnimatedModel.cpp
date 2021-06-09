#include "AnimatedModel.h"

AnimatedModel::AnimatedModel(std::string const path)
{
	load(path);
	gammaCorrection = false;
}

void AnimatedModel::load(std::string const path)
{
	Assimp::Importer importer;
	const aiScene* scene = importer.ReadFile(path, aiProcess_JoinIdenticalVertices |
		aiProcess_SortByPType |
		aiProcess_Triangulate |
		aiProcess_GenSmoothNormals |
		aiProcess_FlipUVs |
		aiProcess_LimitBoneWeights);

	if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode) {
		std::cout << "ERROR::ASSIMP:: " << importer.GetErrorString() << std::endl;
		return;
	}

	directory = path.substr(0, path.find_last_of("/"));

	processNode(scene->mRootNode, scene);
}

void AnimatedModel::processNode(aiNode* node, const aiScene* scene)
{
	for (unsigned int i = 0; i < node->mNumMeshes; i++) {
		aiMesh* mesh = scene->mMeshes[node->mMeshes[i]];
		m_Meshes.push_back(processMesh(mesh, scene));
	}

	for (unsigned int i = 0; i < node->mNumChildren; i++) {
		processNode(node->mChildren[i], scene);
	}
}

void AnimatedModel::Draw(Shader& shader)
{
	shader.use();

	if (!m_Textures.empty()) {
		for (int i = 0; i < m_Textures.size(); i++) {
			m_Textures[i].bind(m_Textures[i].GetId());
			shader.setInt("texture1", m_Textures[i].GetId());
		}
	}

	for (unsigned int i = 0; i < m_Meshes.size(); i++)
		m_Meshes[i].OnRender(shader);
}

void AnimatedModel::AddTexture(Texture& texture)
{
	bool already = false;
	if (m_Textures.size() != 0) {
		for (size_t i = 0; i < m_Textures.size(); i++) {
			if (m_Textures[i].GetFilename() == texture.GetFilename()) {
				 already = true;
			}
			else {
				already = false;
			}
		}
	}
	else {
		already = false;
	}

	if(!already) 
	m_Textures.push_back(texture);
}

void AnimatedModel::AddTextures(std::vector<Texture>& texture)
{
	m_Textures = texture;
}

std::map<std::string, BoneInfo> AnimatedModel::GetBoneInfoMap()
{
	return m_BoneInfoMap;
}

int AnimatedModel::GetBoneCounter()
{
	return m_BoneCounter;
}

void AnimatedModel::SetVertexBoneDataToDefault(AnimatedVertex& vertex)
{
	for (int i = 0; i < MAX_BONE_INFLUENCE; i++) {
		vertex.m_BoneIDs[i] = -1;
		vertex.m_Weights[i] = 0.0f;
	}
}

AnimatedMesh AnimatedModel::processMesh(aiMesh* mesh, const aiScene* scene)
{
	std::vector<AnimatedVertex> vertices;
	std::vector<unsigned int> indices;
	std::vector<AnimatedTexture> textures;

	for (unsigned int i = 0; i < mesh->mNumVertices; i++) {
		AnimatedVertex vertex;

		SetVertexBoneDataToDefault(vertex);

		vertex.position = AssimpUtils::AiVectorToGLM(mesh->mVertices[i]);
		vertex.normal = AssimpUtils::AiVectorToGLM(mesh->mNormals[i]);

		if (mesh->mTextureCoords[0]) {
			glm::vec2 vec;
			vec.x = mesh->mTextureCoords[0][i].x;
			vec.y = mesh->mTextureCoords[0][i].y;
			vertex.texcoord = vec;
		}
		else {
			vertex.texcoord = glm::vec2(0.0f, 0.0f);
		}
		vertices.push_back(vertex);
	}

	for (unsigned int i = 0; i < mesh->mNumFaces; i++)
	{
		aiFace face = mesh->mFaces[i];
		for (unsigned int j = 0; j < face.mNumIndices; j++)
			indices.push_back(face.mIndices[j]);
	}

	ExtractBoneWeightForVertices(vertices, mesh, scene);

	return AnimatedMesh(vertices, indices, textures);

}

void AnimatedModel::SetVertexBoneData(AnimatedVertex& vertex, int boneID, float weight)
{
	for (int i = 0; i < MAX_BONE_INFLUENCE; i++) {
		if (vertex.m_BoneIDs[i] < 0) {
			vertex.m_Weights[i] = weight;
			vertex.m_BoneIDs[i] = boneID;
			break;
		}
	}
}

void AnimatedModel::ExtractBoneWeightForVertices(std::vector<AnimatedVertex>& vertices, aiMesh* mesh, const aiScene* scene)
{
	for (int boneIndex = 0; boneIndex  < mesh->mNumBones; boneIndex++) {
		int boneID = -1;
		std::string boneName = mesh->mBones[boneIndex]->mName.C_Str();
		if (m_BoneInfoMap.find(boneName) == m_BoneInfoMap.end()) {
			BoneInfo boneInfo;
			boneInfo.id = m_BoneCounter;
			boneInfo.offset = AssimpUtils::AiMatrixToGLM(mesh->mBones[boneIndex]->mOffsetMatrix);
			m_BoneInfoMap[boneName] = boneInfo;
			boneID = m_BoneCounter;
			m_BoneCounter++;
		}
		else {
			boneID = m_BoneInfoMap[boneName].id;
		}
		assert(boneID != -1);

		auto weights = mesh->mBones[boneIndex]->mWeights;
		int numWeights = mesh->mBones[boneIndex]->mNumWeights;

		for (int weightIndex = 0; weightIndex < numWeights; ++weightIndex) {
			int vertexId = weights[weightIndex].mVertexId;
			float weight = weights[weightIndex].mWeight;
			assert(vertexId <= vertices.size());
			SetVertexBoneData(vertices[vertexId], boneID, weight);
		}
	}
}

