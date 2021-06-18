#include "ObjectProperties.h"

ObjectProperties::ObjectProperties(SceneHierarchy& sceneHierarchy)
{
	m_Object = nullptr;
	m_SceneHierarchy = &sceneHierarchy;
}

ObjectProperties::~ObjectProperties()
{
}

void ObjectProperties::OnUpdate(float DeltaTime)
{
}

void ObjectProperties::OnRender(EditorScene& scene)
{
	ImGuiWindowFlags window_flags = 0;
	window_flags |= ImGuiWindowFlags_NoMove;
	bool open_ptr = true;

	ImGui::Begin("Properties",&open_ptr,window_flags);

	if (!m_SceneHierarchy->HasSelectedEntity()) {
		m_ObjectId = -1;
		m_Object = nullptr;
	}
	else {
		auto& m_Entity = scene.GetEntity(m_SceneHierarchy->GetSelectedEntity().GetId());// for already components 

		std::string objectName = m_Entity->GetComponent<TagComponent>().tag;

		char buffer[256];

		memset(buffer, 0, sizeof(buffer));

		strcpy_s(buffer, sizeof(buffer), objectName.c_str());

		const ImGuiTreeNodeFlags treeNodeFlags = ImGuiTreeNodeFlags_DefaultOpen | ImGuiTreeNodeFlags_AllowItemOverlap;

		if (m_Entity->HasComponent<TagComponent>()) {
			auto& tagComponent = m_Entity->GetComponent<TagComponent>();

			if (ImGui::TreeNodeEx((void*)typeid(tagComponent).hash_code(), treeNodeFlags, "Tag Component")) {
				ImGui::Text("Tag     "); ImGui::SameLine();
				if (ImGui::InputText(" ", buffer, IM_ARRAYSIZE(buffer))) {
					tagComponent.tag = std::string(buffer);
				}

				ImGui::TreePop();
			}

		}
		
		if (m_Entity->HasComponent<TransformComponent>()) {
			auto& tc = m_Entity->GetComponent<TransformComponent>();


			if (ImGui::TreeNodeEx((void*)typeid(tc).hash_code(), ImGuiTreeNodeFlags_DefaultOpen, "Transform Component")) {

				float v_Speed = 0.1f;

				ImGui::Text("Position "); ImGui::SameLine();  ImGui::DragFloat3("P", glm::value_ptr(tc.Position), v_Speed);
				ImGui::Text("Rotation"); ImGui::SameLine(); ImGui::DragFloat3("R", glm::value_ptr(tc.Rotation), v_Speed);
				ImGui::Text("Scale       "); ImGui::SameLine(); ImGui::DragFloat3("S", glm::value_ptr(tc.Scale), v_Speed);

				ImGui::TreePop();

			}
		}

		if (m_Entity->HasComponent<MeshComponent>()) {
			auto& meshComponent = m_Entity->GetComponent<MeshComponent>();

			if (ImGui::TreeNodeEx((void*)m_Entity->HasComponent<MeshComponent>(), ImGuiTreeNodeFlags_DefaultOpen, "Mesh Component")) {

				ImGui::ColorEdit3("Color", glm::value_ptr(meshComponent.color));
				meshComponent.SetColor();
				

				ImGui::TreePop();
			}

		}

		if (m_Entity->HasComponent<MaterialComponent>()) {
			auto& material = m_Entity->GetComponent<MaterialComponent>();
			if (ImGui::TreeNodeEx((void*)&material, ImGuiTreeNodeFlags_DefaultOpen, "Mesh Component")) {


				ImGui::TreePop();
			}
		}
		
		if (ImGui::Button("Add Component")) {
			ImGui::OpenPopup("AddComponent");
		}

		if (ImGui::BeginPopup("AddComponent")) {

			if (!m_Entity->HasComponent<MeshComponent>()) {
				if (ImGui::MenuItem("Mesh Component")) {

					std::vector<Vertex> rawModel = OBJLoader::loadObjModel("resources/vanilla/obj/cube.obj");
					Mesh mesh(rawModel.data(), rawModel.size(), 0, 0);
					glm::vec3 defaultColor = { 1.0f,1.0f,1.0f };
					m_Entity->AddComponent<MeshComponent>(mesh, defaultColor);
					if (m_Entity->HasComponent<MeshComponent>()) {
						
					}
				}
			}

			if (!m_Entity->HasComponent<TransformComponent>()) {
				if (ImGui::MenuItem("Transform Component")) {
					m_Entity->AddComponent<TransformComponent>();
				}
			}

			/*if (!m_Entity.HasComponent<AnimationComponent>()) {
				if (ImGui::MenuItem("Animation Component")) {
					m_Entity.AddComponent<AnimationComponent>();
				}
			}

			if (!m_Entity.HasComponent<MaterialComponent>()) {
				if (ImGui::MenuItem("Material Component")) {
					m_Entity.AddComponent<MaterialComponent>();
				}
			}*/

			ImGui::EndPopup();
		}

			
	}
	
	ImGui::End();
}
