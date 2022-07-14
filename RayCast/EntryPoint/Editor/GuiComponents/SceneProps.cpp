#include "SceneProps.h"

//#include "../../../Vendor/imgui/ImGuizmo.h"

#include "../Utils/IconsFontAwesome5.h"

SceneProps::SceneProps()
{
	m_TransformMode = TransformMode::Translate;
}

int SceneProps::GetGizmosType() const
{
	return m_GizmosType;
}

void SceneProps::SetGizmosType(int type)
{
	m_GizmosType = type;
}

TransformMode SceneProps::GetTransformMode() const
{
	return m_TransformMode;
}

void SceneProps::Update(float DeltaTime)
{
}

void SceneProps::Render(EditorScene & scene)
{
	ImGuiWindowFlags window_flags = 0;
	window_flags |= ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoTitleBar;
	// etc.
	bool open_ptr = true;
	ImGui::Begin("Scene Viewport",&open_ptr,window_flags);

	

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
	ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(0.25f, 0.25f, 0.25f, 0.00f));
	ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4(0.25f, 0.25f, 0.25f, 0.00f));
	ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImVec4(0.25f, 0.25f, 0.25f, 0.00f));
	scene.OnStart() ? ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(0.35f, 0.35f, 0.35f, 1.00f)) : ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(1.f, 1.f, 1.f, 1.00f));
	if (ImGui::Button(ICON_FA_PLAY)) {
		if (!scene.OnStart()) {
			scene.Play();
			scene.SimulatePhysics();
		}
		else
		{
			scene.Pause();
			scene.StopSimulatePhyiscs();
		}
	}
	ImGui::PopStyleColor();
	ImGui::SameLine();

	
	if (ImGui::Button(ICON_FA_PAUSE)) {
		scene.Pause();
		scene.StopSimulatePhyiscs();
	}
	
	ImGui::SameLine();
	if (ImGui::Button(ICON_FA_REDO_ALT)) {
		scene.Pause();
		scene.StopSimulatePhyiscs();
		scene.RecompileScripts();
		//scene.Pause();
		//scene.StopSimulatePhyiscs();
	}
	ImGui::PopStyleColor(3);

	ImGui::SameLine();


	ImGui::End();
}
