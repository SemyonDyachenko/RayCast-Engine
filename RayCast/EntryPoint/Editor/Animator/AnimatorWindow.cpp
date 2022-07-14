#include "AnimatorWindow.h"



AnimatorWindow::AnimatorWindow()
{
	m_Scene = new AnimationScene();
}

AnimatorWindow::~AnimatorWindow()
{
}

void AnimatorWindow::Update(float DeltaTime)
{
	m_Scene->Update(DeltaTime);
}

void AnimatorWindow::Render(SceneHierarchy & sceneHierarchy)
{
	
	if (m_Opened) {

		m_Scene->Render(sceneHierarchy);

		ImGui::Begin("Animator", &m_Opened);

		unsigned int textureID = m_Scene->GetFrameBuffer()->GetTextureID();

		glm::vec2 frameSize = { m_Scene->GetFrameBuffer()->GetFrameBufferProps().Width,m_Scene->GetFrameBuffer()->GetFrameBufferProps().Height };

		ImGui::Image((ImTextureID)textureID, { frameSize.x,frameSize.y }, { 0,1 }, { 1,0 });
		

		ImGui::End();

	}
}
