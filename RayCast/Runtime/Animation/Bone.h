#ifndef BONE_H
#define BONE_H

#include <string>
#include <vector>
#include <assimp/anim.h>
#include "assimp_utils.h"
#define GLM_ENABLE_EXPERIMENTAL

struct KeyPosition
{
	glm::vec3 position;
	float timeStamp;
};

struct KeyRotation {
	glm::quat orientation;
	float timeStamp;
};

struct KeyScale {
	glm::vec3 scale;
	float timeStamp;
};

class Bone
{
public:
	Bone(const std::string& name, int ID, const aiNodeAnim* channel);
	virtual ~Bone() = default;

	void Update(float animationTime);

	glm::mat4 GetLocalTransform();
	std::string GetName();
	int GetID();

	int GetPositionIndex(float animationTime);
	int GetRotationIndex(float animationTime);
	int GetScalingIndex(float animationTime);

private:
	float GetScaleFactor(float lastTimeStamp, float nextTimeStamp, float animationTime);

	glm::mat4 InterpolatePosition(float animationTime);
	glm::mat4 InterpolateRotation(float animationTime);
	glm::mat4 InterpolateScaling(float animationTime);

private:
	std::vector<KeyPosition> m_Positions;
	std::vector<KeyRotation> m_Rotations;
	std::vector<KeyScale> m_Scales;

	int m_numPos;
	int m_numRot;
	int m_numScal;


	int m_Id;
	glm::mat4 m_localTransform;
	std::string m_Name;	
};

#endif