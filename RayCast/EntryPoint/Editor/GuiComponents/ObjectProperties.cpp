#include "ObjectProperties.h"

ObjectProperties::ObjectProperties()
{
	m_Object = nullptr;
}

ObjectProperties::~ObjectProperties()
{
}

void ObjectProperties::OnUpdate(float DeltaTime)
{
}

void ObjectProperties::OnRender(EditorScene& scene, GuiConsole& console, SceneHierarchy& sceneHierarchy)
{
	ImGui::Begin("Object Properties");

	if (sceneHierarchy.GetSelectedObject() == -1) {
		m_ObjectId = -1;
		m_Object = nullptr;
	}
	else {
		m_ObjectId = sceneHierarchy.GetSelectedObject();
		//m_Object = scene.GetObjectById(m_ObjectId);
		auto & m_Entity = scene.GetEntity(m_ObjectId);

		auto tc = m_Entity->GetComponent<TransformComponent>();
		
		std::string objectName = m_Entity->GetName();

		char buffer[256];

		memset(buffer, 0, sizeof(buffer));

		strcpy_s(buffer, sizeof(buffer), objectName.c_str());

		if (ImGui::InputText("Name",buffer,IM_ARRAYSIZE(buffer))) {
			//std::string new_name = std::string(buffer);
			//scene.GetObjectById(m_ObjectId)->ChangeName(new_name);
		}


		if (ImGui::TreeNodeEx((void*)typeid(m_Object).hash_code(), ImGuiTreeNodeFlags_DefaultOpen, "Transform")) {


			ImGui::DragFloat3("Position", glm::value_ptr(tc.Position));
			ImGui::DragFloat3("Rotation", glm::value_ptr(tc.Rotation));
			ImGui::DragFloat3("Scale", glm::value_ptr(tc.Scale));
			
			ImGui::TreePop();
		
		}

		if (ImGui::TreeNodeEx((void*)typeid(m_Object).hash_code(), ImGuiTreeNodeFlags_DefaultOpen, "Material")) {

			if (!m_Entity->HasComponent<MaterialComponent>()) {

				if (ImGui::Button("Add Material")) {
					ImGui::OpenPopup("New Material");
				}

				if (ImGui::BeginPopupModal("New Material"))
				{
					

					
					
					ImGui::InputText("Diffuse texture", texture_filename, IM_ARRAYSIZE(texture_filename));

					ImGui::InputFloat3("Ambient",glm::value_ptr(ambient));
					ImGui::InputFloat3("Diffuse",glm::value_ptr(diffuse));
					ImGui::InputFloat3("Specular",glm::value_ptr(specular));

					ImGui::ColorPicker3("Color",glm::value_ptr(material_color));

					if (ImGui::Button("Create")) {


						std::string finalPath = "resources/images/textures/" + std::string(texture_filename);


						diffuseTexture = new Texture(finalPath.c_str(), GL_TEXTURE_2D);
						specularTexture = new Texture(finalPath.c_str(), GL_TEXTURE_2D);
					
						diffuseTexture->bind(diffuseTexture->GetId());
						specularTexture->bind(specularTexture->GetId());

						glm::vec3 new_color = glm::vec3(material_color.x / 255.f, material_color.y / 255.f, material_color.z / 255.f);

						material = new Material(ambient, diffuse, specular,
							diffuseTexture->GetId(), specularTexture->GetId(), new_color);

						scene.GetObjectById(m_ObjectId)->AddMaterial(material);
						scene.GetObjectById(m_ObjectId)->AddTexture(diffuseTexture);

						memset(texture_filename, 0, sizeof(texture_filename));
						ambient = glm::vec3(0.0f);
						diffuse = glm::vec3(0.0f);
						specular = glm::vec3(0.0f);
						ImGui::CloseCurrentPopup();
					}
					ImGui::SameLine();

					if (ImGui::Button("Cancel")) {
						ImGui::CloseCurrentPopup();
					}

					ImGui::EndPopup();
				}

			}
			else {

				glm::vec3 ambient = m_Entity->GetComponent<MaterialComponent>().material.GetAmbient();
				glm::vec3 diffuse = m_Entity->GetComponent<MaterialComponent>().material.GetDiffuse();
				glm::vec3 specular = m_Entity->GetComponent<MaterialComponent>().material.GetSpecular();

				ImGui::DragFloat3("Ambient",glm::value_ptr(ambient));
				ImGui::DragFloat3("Diffuse", glm::value_ptr(diffuse));
				ImGui::DragFloat3("Specular",glm::value_ptr(specular));
			
				//ImGui::Text(scene.GetObjectById(m_ObjectId)->GetTextures()[0]->GetFilename());
			}

			ImGui::TreePop();

		}
	}


	ImGui::End();
}
