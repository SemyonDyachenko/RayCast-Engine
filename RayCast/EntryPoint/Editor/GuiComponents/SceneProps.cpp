#include "SceneProps.h"

SceneProps::SceneProps()
{
	m_TransformMode = TransformMode::Translate;
}

TransformMode SceneProps::GetTransformMode()
{
	return m_TransformMode;
}

void SceneProps::Update(float DeltaTime)
{
}

void SceneProps::Render()
{
	ImGuiWindowFlags window_flags = 0;
	window_flags |= ImGuiWindowFlags_NoBackground;
	// etc.
	bool open_ptr = true;
	ImGui::Begin("Scene",&open_ptr,window_flags);

	

	ImGui::Button("Translate"); ImGui::SameLine();
	ImGui::Button("Rotate"); ImGui::SameLine();
	ImGui::Button("Scale"); ImGui::SameLine();

	


	ImGui::End();
}
