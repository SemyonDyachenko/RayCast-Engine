#include "SceneProps.h"
#include "../../../Vendor/imgui/ImGuizmo.h"

SceneProps::SceneProps()
{
	m_TransformMode = TransformMode::Translate;
}

int SceneProps::GetGizmosType()
{
	return m_GizmosType;
}

void SceneProps::SetGizmosType(int type)
{
	m_GizmosType = type;
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
	window_flags |= ImGuiWindowFlags_NoBackground | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoResize;
	// etc.
	bool open_ptr = true;
	ImGui::Begin("Scene",&open_ptr,window_flags);

	

	if (ImGui::Button("Translate")) {
		m_GizmosType = ImGuizmo::TRANSLATE;
	}
	
	ImGui::SameLine();
	if (ImGui::Button("Rotate")) {
		m_GizmosType = ImGuizmo::ROTATE;
	}
		
	ImGui::SameLine();
	if (ImGui::Button("Scale")) {
		m_GizmosType = ImGuizmo::SCALE;
	}
	
	ImGui::SameLine();

	


	ImGui::End();
}
