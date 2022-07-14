#include "AnimationScene.h"

AnimationScene::AnimationScene()
{
	m_Entity = nullptr;
	m_AnimatorCamera = new Camera();

	FrameBufferProps props;
	props.Width = 1280;
	props.Height = 720;
	m_FrameBuffer = FrameBuffer::Create(props);

	m_AnimatorCamera->SetAspectRatio(props.Width,props.Height);
	m_AnimatorCamera->SetFov(60.f);
	
	m_Shader = new Shader("resources/shaders/animated_vertex_shader.glsl", "resources/shaders/materials/rbp_fragment_shader.glsl");
}

AnimationScene::~AnimationScene()
{
	delete m_Entity;
}

void AnimationScene::Update(float DeltaTime)
{
	m_Shader->use();
	m_Shader->SetMat4("ProjectionMatrix", m_AnimatorCamera->GetProjectionMatrix());
	m_Shader->SetMat4("ViewMatrix", m_AnimatorCamera->GetViewMatrix());
}

void AnimationScene::Render(SceneHierarchy& sceneHierarchy)
{
	if (sceneHierarchy.HasSelectedEntity()) {

		m_Entity = &sceneHierarchy.GetSelectedEntity();

		if (m_Entity) {
			m_FrameBuffer->Bind();



			m_FrameBuffer->Unbind();


		}

	}
}


