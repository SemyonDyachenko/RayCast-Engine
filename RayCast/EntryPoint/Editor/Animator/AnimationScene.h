#ifndef ANIMATION_SCENE_H
#define ANIMATION_SCENE_H

#include "../../../Runtime/Entity/Scene.h"
#include "../SceneHierarchy/SceneHierarchy.h"

class AnimationScene
{
public:
	AnimationScene();
	~AnimationScene();
	
	void Update(float DeltaTime);

	std::shared_ptr<FrameBuffer>& GetFrameBuffer() {
		return m_FrameBuffer;
	}

	void Render(SceneHierarchy& sceneHierarchy);

private:
	Entity* m_Entity;
	std::shared_ptr<FrameBuffer> m_FrameBuffer;
	Camera* m_AnimatorCamera;

	Shader* m_Shader;
};


#endif