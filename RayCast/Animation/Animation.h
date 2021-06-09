#ifndef ANIMATION_H
#define ANIMATION_H



#include "Bone.h"
#include <map>
#include <assimp/scene.h>
#include <assimp/Importer.hpp>
#include <assimp/postprocess.h>
#include "AnimatedModel.h"

struct AssimpNodeData {
	glm::mat4 transformation;
	std::string name;
	int childrenCount;
	std::vector<AssimpNodeData> children;


};

class Animation {
public:
	Animation() = default;
	virtual ~Animation() = default;

	Animation(const std::string& path, AnimatedModel* animatedModel);

	Bone* FindBone(const std::string& name);

	 float GetTickPerSecond();
	 float GetDuration();
	 const AssimpNodeData& GetRootNode();
	 const std::map<std::string, BoneInfo> GetBoneIDMap();

	 aiMatrix4x4 GetInverseGlobalTransformation();
private:
	void ReadMissingBones(const aiAnimation* animation, AnimatedModel& animatedModel);
	void ReadHeirachyData(AssimpNodeData& dest, const aiNode* src);

	float m_Duration;
	float m_TicksPerSecond;
	std::vector<Bone> m_Bones;
	AssimpNodeData m_rootNode;
	std::map<std::string, BoneInfo> m_BoneInfoMap;
	aiMatrix4x4 m_globalTransformation;

};


#endif