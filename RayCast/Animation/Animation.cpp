#include "Animation.h"

Animation::Animation(const std::string& path, AnimatedModel* animatedModel)
{
	Assimp::Importer importer;
	const aiScene* scene = importer.ReadFile(path, aiProcess_Triangulate);
	assert(scene && scene->mRootNode);
	aiAnimation* animation = scene->mAnimations[0];
	m_Duration = animation->mDuration;
	m_TicksPerSecond = animation->mTicksPerSecond;
	m_globalTransformation = scene->mRootNode->mTransformation;
	m_globalTransformation = m_globalTransformation.Inverse();

	ReadHeirachyData(m_rootNode, scene->mRootNode);
	ReadMissingBones(animation, *animatedModel);
}

Bone* Animation::FindBone(const std::string& name)
{
	auto iter = std::find_if(m_Bones.begin(), m_Bones.end(),
		[&](Bone& Bone)
		{
			return Bone.GetName() == name;
		}
	);
	if (iter == m_Bones.end()) {
		return nullptr;
	}
	else {
		return &(*iter);
	}
}

 float Animation::GetTickPerSecond()
{
	return m_TicksPerSecond;
}

 float Animation::GetDuration()
{
	return m_Duration;
}

 const AssimpNodeData& Animation::GetRootNode()
{
	return m_rootNode;
}

 const std::map<std::string, BoneInfo> Animation::GetBoneIDMap()
{
	return m_BoneInfoMap;
}

 aiMatrix4x4 Animation::GetInverseGlobalTransformation()
 {
	 return m_globalTransformation;
 }

void Animation::ReadMissingBones(const aiAnimation* animation, AnimatedModel& animatedModel)
{
	int size = animation->mNumChannels;

	std::map<std::string, BoneInfo> boneInfoMap = animatedModel.GetBoneInfoMap();
	int boneCount = animatedModel.GetBoneCounter();

	for (int i = 0; i < size; i++) {
		auto channel = animation->mChannels[i];
		std::string boneName = channel->mNodeName.data;

		if (boneInfoMap.find(boneName) == boneInfoMap.end()) {
			boneInfoMap[boneName].id = boneCount;
			boneCount++;
		}
		m_Bones.push_back(Bone(channel->mNodeName.data, boneInfoMap[channel->mNodeName.data].id, channel));
	}
	m_BoneInfoMap = boneInfoMap;
}

void Animation::ReadHeirachyData(AssimpNodeData& dest, const aiNode* src)
{
	assert(src);

	dest.name = src->mName.data;
	dest.transformation = AssimpUtils::AiMatrixToGLM(src->mTransformation);
	dest.childrenCount = src->mNumChildren;

	for (int i = 0; i < src->mNumChildren; i++) {
		AssimpNodeData newData;
		ReadHeirachyData(newData, src->mChildren[i]);
		dest.children.push_back(newData);
	}
}
