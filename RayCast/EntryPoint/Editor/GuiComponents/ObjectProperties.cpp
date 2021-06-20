#include "ObjectProperties.h"
#include "../../../Runtime/Core/Input.h"
#include "../../../Runtime/Utils/PlatformUtils.h"


ObjectProperties::ObjectProperties(SceneHierarchy& sceneHierarchy)
{
	m_Object = nullptr;
	m_SceneHierarchy = &sceneHierarchy;
}

ObjectProperties::~ObjectProperties()
{
}

std::string ObjectProperties::GetTexturePath()
{
	std::string pathStdString = FileDialogs::OpenFile("Image File (*.jpg)\0*.jpg\0(*.png)\0*.png\0");
	const std::filesystem::path systemPath = pathStdString;
	const std::string filename = systemPath.filename().string();

	std::string texturePath = "resources/images/textures/" + filename;

	return texturePath;
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

		float v_Speed = 0.1f;


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

				ImGui::Text("Position "); ImGui::SameLine();  ImGui::DragFloat3("##tposition", glm::value_ptr(tc.Position), v_Speed);
				ImGui::Text("Rotation"); ImGui::SameLine(); ImGui::DragFloat3("##trotation", glm::value_ptr(tc.Rotation), v_Speed);
				ImGui::Text("Scale       "); ImGui::SameLine(); ImGui::DragFloat3("##tscale", glm::value_ptr(tc.Scale), v_Speed);

				ImGui::TreePop();

			}
		}

		if (m_Entity->HasComponent<MeshComponent>()) {
			auto& meshComponent = m_Entity->GetComponent<MeshComponent>();

			if (ImGui::TreeNodeEx((void*)m_Entity->HasComponent<MeshComponent>(), ImGuiTreeNodeFlags_DefaultOpen, "Mesh Component")) {

				ImGui::ColorEdit3("Color", glm::value_ptr(meshComponent.color));
				meshComponent.SetColor();

				if (ImGui::Button("Change Model")) {
					ImGui::OpenPopup("ChangeModel");
				}

				if (ImGui::BeginPopup("ChangeModel")) {
					if (ImGui::MenuItem("Cube")) {
						std::vector<Vertex> rawModel = OBJLoader::loadObjModel("resources/vanilla/obj/cube.obj");
						Mesh mesh(rawModel.data(), rawModel.size(), 0, 0);

						meshComponent.mesh = mesh;
					}

					if (ImGui::MenuItem("Sphere")) {
						std::vector<Vertex> rawModel = OBJLoader::loadObjModel("resources/vanilla/obj/sphere.obj");
						Mesh mesh(rawModel.data(), rawModel.size(), 0, 0);

						meshComponent.mesh = mesh;
					}

					if (ImGui::MenuItem("Plane")) {
						std::vector<Vertex> rawModel = OBJLoader::loadObjModel("resources/vanilla/obj/plane.obj");
						Mesh mesh(rawModel.data(), rawModel.size(), 0, 0);

						meshComponent.mesh = mesh;
					}

					if (ImGui::MenuItem("Monkey")) {
						std::vector<Vertex> rawModel = OBJLoader::loadObjModel("resources/models/assets/skel.obj");
						Mesh mesh(rawModel.data(), rawModel.size(), 0, 0);

						meshComponent.mesh = mesh;
					}

					if (ImGui::MenuItem("Cylinder")) {
						std::vector<Vertex> rawModel = OBJLoader::loadObjModel("resources/vanilla/obj/cylinder.obj");
						Mesh mesh(rawModel.data(), rawModel.size(), 0, 0);

						meshComponent.mesh = mesh;
					}


					ImGui::EndPopup();
				}

				

				ImGui::TreePop();
			}

		}

		if (m_Entity->HasComponent<DirectionalLightComponent>()) {
			auto& tc = m_Entity->GetComponent<DirectionalLightComponent>();


			if (ImGui::TreeNodeEx((void*)typeid(tc).hash_code(), ImGuiTreeNodeFlags_DefaultOpen, "Directional Light Component")) {
				auto& direction = tc.light.GetDirection();

				ImGui::Text("Direction"); ImGui::SameLine();  ImGui::DragFloat3("##directionlight", glm::value_ptr(direction), v_Speed);
				tc.light.SetDirection(direction);

				ImGui::TreePop();

			}
		}

		if (m_Entity->HasComponent<LightPointComponent>()) {
			auto& tc = m_Entity->GetComponent<LightPointComponent>();


			if (ImGui::TreeNodeEx((void*)typeid(tc).hash_code(), ImGuiTreeNodeFlags_DefaultOpen, "Light Point Component")) {

				tc.light.SetPosition(m_Entity->GetComponent<TransformComponent>().Position);
				ImGui::Text("Position   "); ImGui::SameLine();  ImGui::DragFloat3("##position", glm::value_ptr(tc.light.GetPosition()), v_Speed);
				
				ImGui::Text("Constant "); ImGui::SameLine(); 	ImGui::PushItemWidth(160); ImGui::DragFloat("##const", &tc.light.GetConstant(), v_Speed); ImGui::PopItemWidth();
				ImGui::Text("Linear       "); ImGui::SameLine(); ImGui::PushItemWidth(160); ImGui::DragFloat("##linear", &tc.light.GetLinear(), v_Speed/10); ImGui::PopItemWidth();
				ImGui::Text("Quadratic"); ImGui::SameLine();  ImGui::PushItemWidth(160); ImGui::DragFloat("##quadratic", &tc.light.GetQuadratic(), v_Speed/100); ImGui::PopItemWidth();

				ImGui::TreePop();

			}
		}


		if (m_Entity->HasComponent<MaterialComponent>()) {
			auto& material = m_Entity->GetComponent<MaterialComponent>();
			if (ImGui::TreeNodeEx((void*)&material, ImGuiTreeNodeFlags_DefaultOpen, "Material Component")) {

				ImGui::Text("Basic Material");

				ImGui::ColorEdit3("Color", glm::value_ptr(material.material.GetColor()));

				ImGui::Text("Shininess: "); ImGui::SameLine();
				ImGui::PushItemWidth(160);
				ImGui::DragFloat("    ", &material.material.GetShininess(), 1.f, 1.f, 145.f);
				ImGui::PopItemWidth();



				if (material.material.IsActive()) {
					ImGui::Text("Diffuse map:    "); ImGui::SameLine();

					ImGui::ImageButton((void*)material.material.GetDiffuseTexture().GetId(), { 45,45 });

					ImGui::Text("Specular map: "); ImGui::SameLine();

					ImGui::ImageButton((void*)material.material.GetSpecularTexture().GetId(), { 45,45 });
				}
				else {
					ImGui::Text("Diffuse map:    "); ImGui::SameLine();

					if (ImGui::Button("Add Diffuse map")) {
						material.material.AddDiffuseTexture(new Texture(GetTexturePath().c_str(),GL_TEXTURE_2D));
					}

					ImGui::Text("Specular map: "); ImGui::SameLine();

					if (ImGui::Button("Add Specular map")) {
						material.material.AddSpecularTexture(new Texture(GetTexturePath().c_str(), GL_TEXTURE_2D));

						material.material.Enable();
					}
				}

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

			if (!m_Entity->HasComponent<RigidBodyComponent>()) {
				if (ImGui::MenuItem("RigidBody Component")) {
					m_Entity->AddComponent<RigidBodyComponent>();
				}
			}

			if (!m_Entity->HasComponent<BoxColliderComponent>()) {
				if (ImGui::MenuItem("BoxCollider Component")) {
					m_Entity->AddComponent<BoxColliderComponent>();
				}
			}

			if (!m_Entity->HasComponent<CircleColliderComponent>()) {
				if (ImGui::MenuItem("CircleCollider Component")) {
					m_Entity->AddComponent<CircleColliderComponent>();
				}
			}
			
			if (!m_Entity->HasComponent<MaterialComponent>()) {
				if (ImGui::MenuItem("Material Component")) {

					Texture* diffuse = new Texture("resources/images/textures/skull.jpg",GL_TEXTURE_2D);
					Texture* specular = new Texture("resources/images/textures/skull.jpg",GL_TEXTURE_2D);

					Material* material = new Material();


					m_Entity->AddComponent<MaterialComponent>(*material);

				}

			}

			if (!m_Entity->HasComponent<DirectionalLightComponent>()) {
				if (ImGui::MenuItem("Directional Light")) {
					DirectionalLight* light = new DirectionalLight(glm::vec3(-1.0f),glm::vec3(0.1f, 0.3f, 0.2f), glm::vec3(0.7f, 0.42f, 0.26f), glm::vec3(0.7f, 0.7f, 0.7f),glm::vec3(1.0f));

					m_Entity->AddComponent<DirectionalLightComponent>(*light);
				}
			}

			if (!m_Entity->HasComponent<LightPointComponent>()) {
				if (ImGui::MenuItem("Point Light")) {
					LightPoint* light = new LightPoint(m_Entity->GetComponent<TransformComponent>().Position, glm::vec3(0.1f, 0.3f, 0.2f), glm::vec3(0.7f, 0.42f, 0.26f), glm::vec3(0.7f, 0.7f, 0.7f), glm::vec3(1.0f),1.0f, 0.09f, 0.032f);

					m_Entity->AddComponent<LightPointComponent>(*light,m_Entity->GetComponent<TransformComponent>().Position);

					
				}
			}

			/*if (!m_Entity.HasComponent<AnimationComponent>()) {
				if (ImGui::MenuItem("Animation Component")) {
					m_Entity.AddComponent<AnimationComponent>();
				}
			}*/

		

			ImGui::EndPopup();
		}

			
	}
	
	ImGui::End();
}
