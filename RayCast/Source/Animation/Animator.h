#ifndef ANIMATOR_H
#define ANIMATOR_H

#include "Animation.h"

class Animator
{
public:
	Animator(Animation * animation);
	virtual ~Animator() = default;

	void UpdateAnimation(float DeltaTime);

	void PlayAnimation(Animation* pAnimation);

	void CalculateBoneTransform(const AssimpNodeData* node, glm::mat4 parentTransform);

	std::vector<glm::mat4> GetFinalBoneMatrices();
private:
	std::vector<glm::mat4> m_FinalBoneMatrices;
	Animation* m_currentAnimation;
	float m_currentTime;
	float m_deltaTime;
};

#endif