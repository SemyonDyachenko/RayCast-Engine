#include "TerrainEditor.h"

TerrainEditor::TerrainEditor()
{
	m_Entity = nullptr;
}

TerrainEditor::~TerrainEditor()
{
}

void TerrainEditor::Update(float DeltaTime)
{
}

void TerrainEditor::Render(EditorScene& scene, SceneHierarchy& sceneHierarchy)
{
	const ImGuiTreeNodeFlags treeNodeFlags = ImGuiTreeNodeFlags_DefaultOpen | ImGuiTreeNodeFlags_Framed | ImGuiTreeNodeFlags_SpanAvailWidth | ImGuiTreeNodeFlags_AllowItemOverlap | ImGuiTreeNodeFlags_FramePadding;

	if (m_Opened) {
		ImGui::Begin("Terrain", &m_Opened);
		if (sceneHierarchy.HasSelectedEntity()) {
			m_Entity = &(*scene.GetEntity(sceneHierarchy.GetSelectedEntity().GetId()));

			if (m_Entity) {
				if (m_Entity->HasComponent<TerrainComponent>()) {


					auto& terrain = m_Entity->GetComponent<TerrainComponent>();

					auto& tc = m_Entity->GetComponent<TransformComponent>();
					float v_Speed = 0.1f;

					if (ImGui::TreeNodeEx((void*)&terrain, treeNodeFlags, m_Entity->GetComponent<TagComponent>().tag.c_str()))
					{
						ImGui::Text("Material"); ImGui::SameLine();

						ImGui::Button("None");

						ImGui::Text("Position "); ImGui::SameLine();  ImGui::DragFloat3("##tposition", glm::value_ptr(tc.Position), v_Speed);
						ImGui::Text("Rotation"); ImGui::SameLine(); ImGui::DragFloat3("##trotation", glm::value_ptr(tc.Rotation), v_Speed);
						ImGui::Text("Scale       "); ImGui::SameLine(); ImGui::DragFloat3("##tscale", glm::value_ptr(tc.Scale), v_Speed);


						ImGui::Text("Grid Size X"); ImGui::SameLine();  ImGui::DragFloat("##terraineditorgridx", &terrain.terrain.GetGridSizeX(), v_Speed);
						ImGui::Text("Grid Size Z"); ImGui::SameLine();  ImGui::DragFloat("##terrainedutirgridz", &terrain.terrain.GetGridSizeX(), v_Speed);


						ImGui::TreePop();
					}

				}
			}

		}

		ImGui::End();
	}
}
