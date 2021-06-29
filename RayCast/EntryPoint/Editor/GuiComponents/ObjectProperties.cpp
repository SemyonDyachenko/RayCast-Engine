#include "../../../stdafx.h"
#include "ObjectProperties.h"
#include "../../../Runtime/Core/Input.h"
#include "../../../Runtime/Utils/PlatformUtils.h"

#include "../../../resources/scripts/MovementController.h"


ObjectProperties::ObjectProperties(SceneHierarchy& sceneHierarchy)
{
	m_Object = nullptr;
	m_SceneHierarchy = &sceneHierarchy;
	m_Transparent = new Texture("resources/images/editor/transparentbg.jpg", GL_TEXTURE_2D);
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

void ObjectProperties::OnRender(EditorScene& scene,GuiConsole & console)
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

			if (ImGui::TreeNodeEx((void*)m_Entity->HasComponent<MeshComponent>(), ImGuiTreeNodeFlags_DefaultOpen, "Mesh Renderer")) {

				ImGui::ColorEdit3("Color", glm::value_ptr(meshComponent.color));
				meshComponent.SetColor();

				if (ImGui::Button("Change Model")) {
					ImGui::OpenPopup("ChangeModel");
				}

				if (ImGui::BeginPopup("ChangeModel")) {
					if (ImGui::MenuItem("Cube")) {
						std::vector<Vertex> rawModel = OBJLoader::loadObjModel("resources/vanilla/obj/cube.obj");
						Mesh mesh(rawModel.data(), rawModel.size(), 0, 0,"resources/vanilla/obj/cube.obj");

						meshComponent.mesh = mesh;
					}

					if (ImGui::MenuItem("Sphere")) {
						std::vector<Vertex> rawModel = OBJLoader::loadObjModel("resources/vanilla/obj/sphere.obj");
						Mesh mesh(rawModel.data(), rawModel.size(), 0, 0, "resources/vanilla/obj/sphere.obj");

						meshComponent.mesh = mesh;
					}

					if (ImGui::MenuItem("Plane")) {
						std::vector<Vertex> rawModel = OBJLoader::loadObjModel("resources/vanilla/obj/plane.obj");
						Mesh mesh(rawModel.data(), rawModel.size(), 0, 0, "resources/vanilla/obj/plane.obj");

						meshComponent.mesh = mesh;
					}

					if (ImGui::MenuItem("Monkey")) {
						std::vector<Vertex> rawModel = OBJLoader::loadObjModel("resources/vanilla/obj/monkey.obj");
						Mesh mesh(rawModel.data(), rawModel.size(), 0, 0, "resources/vanilla/obj/monkey.obj");

						meshComponent.mesh = mesh;
					}

					if (ImGui::MenuItem("Cylinder")) {
						std::vector<Vertex> rawModel = OBJLoader::loadObjModel("resources/vanilla/obj/cylinder.obj");
						Mesh mesh(rawModel.data(), rawModel.size(), 0, 0, "resources/vanilla/obj/cylinder.obj");

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

				ImGui::Text("Ambient   "); ImGui::SameLine(); 	ImGui::PushItemWidth(160); ImGui::DragFloat3("##ambientdir", glm::value_ptr(tc.light.GetAmbient()), v_Speed); ImGui::PopItemWidth();
				ImGui::Text("Diffuse     "); ImGui::SameLine(); 	ImGui::PushItemWidth(160); ImGui::DragFloat3("##diffusedir", glm::value_ptr(tc.light.GetDiffuse()), v_Speed); ImGui::PopItemWidth();
				ImGui::Text("Specular  "); ImGui::SameLine(); 	ImGui::PushItemWidth(160); ImGui::DragFloat3("##speculardir", glm::value_ptr(tc.light.GetSpecular()), v_Speed); ImGui::PopItemWidth();

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

				ImGui::Text("Ambient   "); ImGui::SameLine(); 	ImGui::PushItemWidth(160); ImGui::DragFloat3("##ambientpoint", glm::value_ptr(tc.light.GetAmbient()), v_Speed); ImGui::PopItemWidth();
				ImGui::Text("Diffuse     "); ImGui::SameLine(); 	ImGui::PushItemWidth(160); ImGui::DragFloat3("##diffusepoint", glm::value_ptr(tc.light.GetDiffuse()), v_Speed); ImGui::PopItemWidth();
				ImGui::Text("Specular  "); ImGui::SameLine(); 	ImGui::PushItemWidth(160); ImGui::DragFloat3("##specularpoint", glm::value_ptr(tc.light.GetSpecular()), v_Speed); ImGui::PopItemWidth();

				ImGui::TreePop();

			}
		}

		if (m_Entity->HasComponent<BoxColliderComponent>()) {
			auto& boxCollider = m_Entity->GetComponent<BoxColliderComponent>();
			if (ImGui::TreeNodeEx((void*)typeid(boxCollider).hash_code(), ImGuiTreeNodeFlags_DefaultOpen, "Box Collider Component")) {

				ImGui::Text("Size          "); ImGui::SameLine();  ImGui::DragFloat3("##boxcollidersize", glm::value_ptr(boxCollider.collider.Size), v_Speed);
				ImGui::Text("Position "); ImGui::SameLine();  ImGui::DragFloat3("##boxcolliderposition", glm::value_ptr(boxCollider.collider.Position), v_Speed);
				ImGui::Text("Rotation"); ImGui::SameLine();  ImGui::DragFloat3("##boxcolliderrotation", glm::value_ptr(boxCollider.collider.Position), v_Speed);

				boxCollider.collider.Position = m_Entity->GetComponent<TransformComponent>().Position;
				boxCollider.collider.Size = m_Entity->GetComponent<TransformComponent>().Scale;
				boxCollider.collider.Rotation = m_Entity->GetComponent<TransformComponent>().GetQuatRotation();

				ImGui::TreePop();

			}

		}

		if (m_Entity->HasComponent<CircleColliderComponent>()) {
			auto& circleCollider = m_Entity->GetComponent<CircleColliderComponent>();
			if (ImGui::TreeNodeEx((void*)typeid(circleCollider).hash_code(), ImGuiTreeNodeFlags_DefaultOpen, "Circle Collider Component")) {

				ImGui::Text("Radius "); ImGui::SameLine();  ImGui::DragFloat("##circlecolliderradius", &circleCollider.collider.Radius, v_Speed);
				ImGui::Text("Center "); ImGui::SameLine();  ImGui::DragFloat3("##circlecollidercenter", glm::value_ptr(circleCollider.collider.Center), v_Speed);

				circleCollider.collider.Center = m_Entity->GetComponent<TransformComponent>().Position;
				circleCollider.collider.SetRadius(m_Entity->GetComponent<TransformComponent>().Scale.x / 2.0f);

				ImGui::TreePop();

			}

		}

		if (m_Entity->HasComponent<RigidBodyComponent>()) {
			auto& rb = m_Entity->GetComponent<RigidBodyComponent>();
			if (ImGui::TreeNodeEx((void*)typeid(rb).hash_code(), ImGuiTreeNodeFlags_DefaultOpen, "RigidBody Component")) {

				auto& mass = rb.rigidbody.GetMass();
				
				ImGui::PushItemWidth(100); ImGui::Text("Mass               "); ImGui::PopItemWidth();  ImGui::SameLine(); ImGui::PushItemWidth(160);  ImGui::DragFloat("##rigidbodymass", &mass, v_Speed); ImGui::PopItemWidth();
				ImGui::PushItemWidth(100);  ImGui::Text("Linear Drag  "); ImGui::PopItemWidth();  ImGui::SameLine(); ImGui::PushItemWidth(160); ImGui::DragFloat("##rigidbodylindrag", &rb.rigidbody.GetLinearDrag(), v_Speed); ImGui::PopItemWidth();
				ImGui::PushItemWidth(100);  ImGui::Text("Angular Drag");  ImGui::PopItemWidth();  ImGui::SameLine(); ImGui::PushItemWidth(160);  ImGui::DragFloat("##rigidbodyangdrag", &rb.rigidbody.GetAngularDrag(), v_Speed); ImGui::PopItemWidth();

				rb.rigidbody.SetMass(mass);

				//ImGui::Text("Radius "); ImGui::SameLine();  ImGui::DragFloat("##circlecolliderradius", &circleCollider.collider.Radius, v_Speed);
				//ImGui::Text("Center "); ImGui::SameLine();  ImGui::DragFloat3("##circlecollidercenter", glm::value_ptr(circleCollider.collider.Center), v_Speed);

				ImGui::Text("Gravity  "); ImGui::SameLine();
				ImGui::Checkbox("##rigidbodygravity", &rb.rigidbody.m_isDynamic);

				//ImGui::Text("Position  "); ImGui::SameLine();
				//ImGui::DragFloat3("##rigidbodyposition", glm::value_ptr(rb.rigidbody.Position));

				if (!scene.IsPhysicsSimulation()) {
					rb.rigidbody.Position = m_Entity->GetComponent<TransformComponent>().Position;
					m_Entity->GetComponent<TransformComponent>().Scale;
					//rb.rigidbody.m_Body->setWorldTransform();
					//rb.rigidbody.boxCollider->Rotation = m_Entity->GetComponent<TransformComponent>().Rotation;
					//rb.rigidbody.boxCollider = &m_Entity->GetComponent<BoxColliderComponent>().collider;
				}
				 
				//std::cout << rb.rigidbody.GetPosition().x << " " << rb.rigidbody.GetPosition().y << " " << rb.rigidbody.GetPosition().z << "\n";

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

				if (!material.material.IsTextured()) {
					if (ImGui::TreeNodeEx((void*)323243242463, ImGuiTreeNodeFlags_DefaultOpen, "Diffuse map")) {
						if (ImGui::ImageButton((void*)m_Transparent->GetId(), { 55,55 })) {
							material.material.AddDiffuseTexture(new Texture(GetTexturePath().c_str(), GL_TEXTURE_2D));
						}
						ImGui::SameLine();
						ImGui::Text("Use  "); ImGui::SameLine();
						ImGui::Checkbox("##materialdiffuseused", &material.material.IsTextured());

						ImGui::TreePop();
					}

					if (ImGui::TreeNodeEx((void*)324324324324324, ImGuiTreeNodeFlags_DefaultOpen, "Specular map")) {
						if(ImGui::ImageButton((void*)m_Transparent->GetId(), { 55,55 }))  {
							material.material.AddSpecularTexture(new Texture(GetTexturePath().c_str(), GL_TEXTURE_2D));
							material.material.Textured();
							material.material.Enable();
						}
						ImGui::SameLine();
						ImGui::Text("Use  "); ImGui::SameLine();
						ImGui::Checkbox("##materialspecularused", &material.material.IsTextured());

						ImGui::TreePop();
					}
				}
				
				else {
					if (ImGui::TreeNodeEx((void*)3232432424634, ImGuiTreeNodeFlags_DefaultOpen, "Diffuse map")) {
						if (ImGui::ImageButton((void*)material.material.GetDiffuseTexture().GetId(), { 55,55 })) {
							material.material.AddDiffuseTexture(new Texture(GetTexturePath().c_str(), GL_TEXTURE_2D));
						}
						ImGui::SameLine();
						ImGui::Text("Use  "); ImGui::SameLine();
						ImGui::Checkbox("##materialdiffuseused", &material.material.IsTextured());

						ImGui::TreePop();
					}

					if (ImGui::TreeNodeEx((void*)3243243243243244, ImGuiTreeNodeFlags_DefaultOpen, "Specular map")) {
						if (ImGui::ImageButton((void*)material.material.GetSpecularTexture().GetId(), { 55,55 })) {
							material.material.AddSpecularTexture(new Texture(GetTexturePath().c_str(), GL_TEXTURE_2D));
						}
						ImGui::SameLine();
						ImGui::Text("Use  "); ImGui::SameLine();
						ImGui::Checkbox("##materialspecularused", &material.material.IsTextured());

						ImGui::TreePop();
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
					Mesh mesh(rawModel.data(), rawModel.size(), 0, 0, "resources/vanilla/obj/cube.obj");
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
					if (m_Entity->HasComponent<CircleColliderComponent>()) {
						auto& cc = m_Entity->GetComponent<CircleColliderComponent>().collider;
						RigidBody* rb = new RigidBody(&cc,1.0f, 1.0f, 1.0f, glm::vec3(1.0f), glm::vec3(1.0f));
						m_Entity->AddComponent<RigidBodyComponent>(*rb);
					}
					else if(m_Entity->HasComponent<BoxColliderComponent>()) {
						auto& bc = m_Entity->GetComponent<BoxColliderComponent>().collider;
						RigidBody* rb = new RigidBody(&bc,1.0f, 1.0f, 1.0f, glm::vec3(1.0f), glm::vec3(1.0f));
						m_Entity->AddComponent<RigidBodyComponent>(*rb);
					}
					auto& entity_rb = m_Entity->GetComponent<RigidBodyComponent>();
					if (&entity_rb) {
						scene.GetPhysicsWorld().AddRigidBody(&entity_rb.rigidbody);
					}
					else {
						console.PushMessage("Entity has not a collider, impossible create a RigidBody!", CalculateTime(), MessageStatus::Error);
					}
				}
			}

			if (!m_Entity->HasComponent<BoxColliderComponent>()) {
				if (ImGui::MenuItem("BoxCollider Component")) {
					if (m_Entity->HasComponent<TransformComponent>()) {
						auto& transform = m_Entity->GetComponent<TransformComponent>();
						m_Entity->AddComponent<BoxColliderComponent>(transform.Scale,transform.Position,transform.Rotation);
					}
				}
			}

			if (!m_Entity->HasComponent<CircleColliderComponent>()) {
				if (ImGui::MenuItem("CircleCollider Component")) {
					auto& tc = m_Entity->GetComponent<TransformComponent>();
					m_Entity->AddComponent<CircleColliderComponent>(tc.Scale.x,tc.Position,tc.Rotation);
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

		

			/*if (!m_Entity->HasComponent<AnimationComponent>()) {
				if (ImGui::MenuItem("Animation Component")) {

					AnimatedModel* model = new AnimatedModel("resources/demon.dae");

					m_Entity->AddComponent<AnimationComponent>();
				}
			}*/

		

			ImGui::EndPopup();
		}

			
	}
	
	ImGui::End();
}
