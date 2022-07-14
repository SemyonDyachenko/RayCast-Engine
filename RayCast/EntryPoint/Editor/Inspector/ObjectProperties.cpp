

#include "../../../stdafx.h"
#include "ObjectProperties.h"
#include "../../../Runtime/Core/Input.h"
#include "../../../Runtime/Utils/PlatformUtils.h"
#include "../GuiComponents/ObjectAdditor.h"
#include "../../../Vendor/imgui-docking/imgui_internal.h"

ObjectProperties::ObjectProperties(SceneHierarchy& sceneHierarchy)
{
	
	m_SceneHierarchy = &sceneHierarchy;
	m_Transparent = new Texture("resources/images/editor/transparentbg.jpg");
}

ObjectProperties::~ObjectProperties()
{
	delete m_SceneHierarchy;
	delete m_Transparent;
	
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

void ObjectProperties::OnRender(EditorScene& scene, GuiConsole& console)
{
	ImGuiWindowFlags window_flags = 0;
	
	bool open_ptr = true;

	ImGui::Begin("Properties", &open_ptr, window_flags);

	if (!m_SceneHierarchy->EditorCameraSelected()) {
		if (!m_SceneHierarchy->HasSelectedEntity()) {
			m_ObjectId = -1;
			
		}
		else {
			Entity* m_Entity = nullptr;
			m_Entity = &(*scene.GetEntity(m_SceneHierarchy->GetSelectedEntity().GetId()));// for already components 

			float v_Speed = 0.1f;

			if(m_Entity) {
				
			std::string entityName = m_Entity->GetComponent<TagComponent>().tag;

			char buffer[256];

			memset(buffer, 0, sizeof(buffer));

			strcpy_s(buffer, sizeof(buffer), entityName.c_str());

			const ImGuiTreeNodeFlags treeNodeFlags = ImGuiTreeNodeFlags_DefaultOpen | ImGuiTreeNodeFlags_Framed | ImGuiTreeNodeFlags_SpanAvailWidth | ImGuiTreeNodeFlags_AllowItemOverlap | ImGuiTreeNodeFlags_FramePadding;

			if (m_Entity->HasComponent<TagComponent>()) {
				auto& tagComponent = m_Entity->GetComponent<TagComponent>();

				ImGui::Separator();
				ImGui::PushStyleVar(ImGuiStyleVar_FramePadding, ImVec2{ 4,4 });
				if (ImGui::TreeNodeEx((void*)typeid(tagComponent).hash_code(), treeNodeFlags, "Tag Component")) {
					ImGui::Text("Tag     "); ImGui::SameLine();
					if (ImGui::InputText(" ", buffer, IM_ARRAYSIZE(buffer))) {
						tagComponent.tag = std::string(buffer);
					}

					ImGui::TreePop();
				}
				ImGui::PopStyleVar();

			}

			if (m_Entity->HasComponent<TransformComponent>()) {
				auto& tc = m_Entity->GetComponent<TransformComponent>();

				
				ImGui::Separator();
				ImGui::PushStyleVar(ImGuiStyleVar_FramePadding, ImVec2{ 4,4 });
				if (ImGui::TreeNodeEx((void*)typeid(tc).hash_code(), treeNodeFlags, "Transform Component")) {

					ImGui::Text("Position "); ImGui::SameLine();  ImGui::DragFloat3("##tposition", glm::value_ptr(tc.Position), v_Speed);
					ImGui::Text("Rotation"); ImGui::SameLine(); ImGui::DragFloat3("##trotation", glm::value_ptr(tc.Rotation), v_Speed);
					ImGui::Text("Scale       "); ImGui::SameLine(); ImGui::DragFloat3("##tscale", glm::value_ptr(tc.Scale), v_Speed);

					ImGui::TreePop();
				}
				ImGui::PopStyleVar();
				
			}

			if (m_Entity->HasComponent<MeshComponent>()) {
				auto& meshComponent = m_Entity->GetComponent<MeshComponent>();

				ImGui::Separator();
				ImGui::PushStyleVar(ImGuiStyleVar_FramePadding, ImVec2{ 4,4 });
				if (ImGui::TreeNodeEx((void*)m_Entity->HasComponent<MeshComponent>(), treeNodeFlags, "Mesh Renderer")) {

					ImGui::ColorEdit3("Color", glm::value_ptr(meshComponent.color));
					meshComponent.SetColor();

					if (ImGui::Button("Change Model")) {
						ImGui::OpenPopup("ChangeModel");
					}

					if (ImGui::BeginPopup("ChangeModel")) {
						if (ImGui::MenuItem("Cube")) {
							meshComponent.mesh = *ObjectAdditor::CreateMesh(DefaultObjects::Cube);
						}

						if (ImGui::MenuItem("Sphere")) {
							meshComponent.mesh = *ObjectAdditor::CreateMesh(DefaultObjects::Sphere);
						}

						if (ImGui::MenuItem("Plane")) {
							meshComponent.mesh = *ObjectAdditor::CreateMesh(DefaultObjects::Plane);
						}

						if (ImGui::MenuItem("Monkey")) {
							meshComponent.mesh = *ObjectAdditor::CreateMesh(DefaultObjects::Monkey);
						}

						if (ImGui::MenuItem("Cylinder")) {
							meshComponent.mesh = *ObjectAdditor::CreateMesh(DefaultObjects::Cylinder);
						}


						ImGui::EndPopup();
					}

					

					ImGui::TreePop();
				}
				ImGui::PopStyleVar();
			}

			if (m_Entity->HasComponent<DirectionalLightComponent>()) {
				auto& tc = m_Entity->GetComponent<DirectionalLightComponent>();

				ImGui::Separator();
				ImGui::PushStyleVar(ImGuiStyleVar_FramePadding, ImVec2{ 4,4 });
				if (ImGui::TreeNodeEx((void*)typeid(tc).hash_code(), treeNodeFlags, "Directional Light Component")) {
					auto& direction = tc.light.GetDirection();

					ImGui::Text("Direction"); ImGui::SameLine();  ImGui::DragFloat3("##directionlight", glm::value_ptr(direction), v_Speed);
					tc.light.SetDirection(direction);

					ImGui::Text("Ambient   "); ImGui::SameLine(); 	ImGui::PushItemWidth(160); ImGui::DragFloat3("##ambientdir", glm::value_ptr(tc.light.GetAmbient()), v_Speed); ImGui::PopItemWidth();
					ImGui::Text("Diffuse     "); ImGui::SameLine(); 	ImGui::PushItemWidth(160); ImGui::DragFloat3("##diffusedir", glm::value_ptr(tc.light.GetDiffuse()), v_Speed); ImGui::PopItemWidth();
					ImGui::Text("Specular  "); ImGui::SameLine(); 	ImGui::PushItemWidth(160); ImGui::DragFloat3("##speculardir", glm::value_ptr(tc.light.GetSpecular()), v_Speed); ImGui::PopItemWidth();

					ImGui::TreePop();

				}
				ImGui::PopStyleVar();
			}

			if (m_Entity->HasComponent<LightPointComponent>()) {
				auto& tc = m_Entity->GetComponent<LightPointComponent>();

				ImGui::Separator();
				ImGui::PushStyleVar(ImGuiStyleVar_FramePadding, ImVec2{ 4,4 });
				if (ImGui::TreeNodeEx((void*)typeid(tc).hash_code(), treeNodeFlags, "Light Point Component")) {

					tc.light.SetPosition(m_Entity->GetComponent<TransformComponent>().Position);
					ImGui::Text("Position   "); ImGui::SameLine();  ImGui::DragFloat3("##position", glm::value_ptr(tc.light.GetPosition()), v_Speed);

					ImGui::Text("Constant "); ImGui::SameLine(); 	ImGui::PushItemWidth(160); ImGui::DragFloat("##const", &tc.light.GetConstant(), v_Speed); ImGui::PopItemWidth();
					ImGui::Text("Linear       "); ImGui::SameLine(); ImGui::PushItemWidth(160); ImGui::DragFloat("##linear", &tc.light.GetLinear(), v_Speed / 10); ImGui::PopItemWidth();
					ImGui::Text("Quadratic"); ImGui::SameLine();  ImGui::PushItemWidth(160); ImGui::DragFloat("##quadratic", &tc.light.GetQuadratic(), v_Speed / 100); ImGui::PopItemWidth();

					ImGui::Text("Ambient   "); ImGui::SameLine(); 	ImGui::PushItemWidth(160); ImGui::DragFloat3("##ambientpoint", glm::value_ptr(tc.light.GetAmbient()), v_Speed); ImGui::PopItemWidth();
					ImGui::Text("Diffuse     "); ImGui::SameLine(); 	ImGui::PushItemWidth(160); ImGui::DragFloat3("##diffusepoint", glm::value_ptr(tc.light.GetDiffuse()), v_Speed); ImGui::PopItemWidth();
					ImGui::Text("Specular  "); ImGui::SameLine(); 	ImGui::PushItemWidth(160); ImGui::DragFloat3("##specularpoint", glm::value_ptr(tc.light.GetSpecular()), v_Speed); ImGui::PopItemWidth();

					ImGui::TreePop();

				}
				ImGui::PopStyleVar();
			}

			if (m_Entity->HasComponent<BoxColliderComponent>()) {
				auto& boxCollider = m_Entity->GetComponent<BoxColliderComponent>();

				ImGui::Separator();
				ImGui::PushStyleVar(ImGuiStyleVar_FramePadding, ImVec2{ 4,4 });
				if (ImGui::TreeNodeEx((void*)typeid(boxCollider).hash_code(), treeNodeFlags, "Box Collider Component")) {

					std::string materialName = boxCollider.collider.HasPhysicMaterial ? boxCollider.collider.material.GetName() : "None";

					ImGui::Text("Physic Material"); ImGui::SameLine();

					ImGui::Button(materialName.c_str());

					if (ImGui::BeginDragDropTarget()) {

						const ImGuiPayload* payload = ImGui::AcceptDragDropPayload("contentelement");

						if (payload) {
							const wchar_t* payloadPath = (const wchar_t*)payload->Data;
							const char* cstr = (const char*)payloadPath;
							std::string finalPath = std::string(cstr);

							std::filesystem::path filesystemPath = finalPath;
							std::filesystem::directory_entry it(filesystemPath);

							if (!it.is_directory()) {
								if (filesystemPath.has_extension()) {
									auto ext = filesystemPath.extension().string();

									if (ext == ".rcpm") {
										boxCollider.collider.material = PhysicsMaterialController::Deserialize(finalPath);
										boxCollider.collider.HasPhysicMaterial = true;
									}
								}
							}
						}

						ImGui::EndDragDropTarget();
					}

					ImGui::Text("Size     "); ImGui::SameLine();  ImGui::DragFloat3("##boxcollidersize", glm::value_ptr(boxCollider.collider.Size), v_Speed);
					ImGui::Text("Center"); ImGui::SameLine();  ImGui::DragFloat3("##boxcollidercenter", glm::value_ptr(boxCollider.collider.Center), v_Speed);

					ImGui::Text("Is Trigger"); ImGui::SameLine();

					bool tr = true;
					ImGui::Checkbox("##istrigerboxcollider", &tr);

					boxCollider.collider.Position = m_Entity->GetComponent<TransformComponent>().Position;
					boxCollider.collider.Size = m_Entity->GetComponent<TransformComponent>().Scale;
					boxCollider.collider.Rotation = m_Entity->GetComponent<TransformComponent>().GetQuatRotation();

					ImGui::TreePop();

				}
				ImGui::PopStyleVar();
			}

			if (m_Entity->HasComponent<CircleColliderComponent>()) {
				auto& circleCollider = m_Entity->GetComponent<CircleColliderComponent>();
				
				ImGui::Separator();
				ImGui::PushStyleVar(ImGuiStyleVar_FramePadding, ImVec2{ 4,4 });
				
				if (ImGui::TreeNodeEx((void*)typeid(circleCollider).hash_code(), treeNodeFlags, "Circle Collider Component")) {

					std::string materialName = circleCollider.collider.HasPhysicMaterial ? circleCollider.collider.material.GetName() : "None";

					ImGui::Text("Physic Material"); ImGui::SameLine();

					ImGui::Button(materialName.c_str());

					if (ImGui::BeginDragDropTarget()) {

						const ImGuiPayload* payload = ImGui::AcceptDragDropPayload("contentelement");

						if (payload) {
							const wchar_t* payloadPath = (const wchar_t*)payload->Data;
							const char* cstr = (const char*)payloadPath;
							std::string finalPath = std::string(cstr);

							std::filesystem::path filesystemPath = finalPath;
							std::filesystem::directory_entry it(filesystemPath);

							if (!it.is_directory()) {
								if (filesystemPath.has_extension()) {
									auto ext = filesystemPath.extension().string();

									if (ext == ".rcpm") {
										circleCollider.collider.material = PhysicsMaterialController::Deserialize(finalPath);
										circleCollider.collider.HasPhysicMaterial = true;
									}
								}
							}
						}

						ImGui::EndDragDropTarget();
					}

					ImGui::Text("Radius "); ImGui::SameLine();  ImGui::DragFloat("##circlecolliderradius", &circleCollider.collider.Radius, v_Speed);
					ImGui::Text("Center "); ImGui::SameLine();  ImGui::DragFloat3("##circlecollidercenter", glm::value_ptr(circleCollider.collider.Center), v_Speed);

					ImGui::Text("Is Trigger"); ImGui::SameLine();

					bool tr = true;
					ImGui::Checkbox("##istrigercirclecollider", &tr);


					circleCollider.collider.Center = m_Entity->GetComponent<TransformComponent>().Position;
					circleCollider.collider.SetRadius(m_Entity->GetComponent<TransformComponent>().Scale.x / 2.0f);

					ImGui::TreePop();

				}
				ImGui::PopStyleVar();
			}

			if (m_Entity->HasComponent<CapsuleColliderComponent>()) {
				auto& capsuleCollider = m_Entity->GetComponent<CapsuleColliderComponent>();

				ImGui::Separator();
				ImGui::PushStyleVar(ImGuiStyleVar_FramePadding, ImVec2{ 4,4 });
				
				if (ImGui::TreeNodeEx((void*)typeid(capsuleCollider).hash_code(), treeNodeFlags, "Circle Collider Component")) {

					std::string materialName = capsuleCollider.collider.HasPhysicMaterial ? capsuleCollider.collider.material.GetName() : "None";

					ImGui::Text("Physic Material"); ImGui::SameLine();

					ImGui::Button(materialName.c_str());

					if (ImGui::BeginDragDropTarget()) {

						const ImGuiPayload* payload = ImGui::AcceptDragDropPayload("contentelement");

						if (payload) {
							const wchar_t* payloadPath = (const wchar_t*)payload->Data;
							const char* cstr = (const char*)payloadPath;
							std::string finalPath = std::string(cstr);

							std::filesystem::path filesystemPath = finalPath;
							std::filesystem::directory_entry it(filesystemPath);

							if (!it.is_directory()) {
								if (filesystemPath.has_extension()) {
									auto ext = filesystemPath.extension().string();

									if (ext == ".rcpm") {
										capsuleCollider.collider.HasPhysicMaterial = true;
										capsuleCollider.collider.material = PhysicsMaterialController::Deserialize(finalPath);
										
									}
								}
							}
						}

						ImGui::EndDragDropTarget();
					}

					ImGui::Text("Radius "); ImGui::SameLine();  ImGui::DragFloat("##capsulecollideradius", &capsuleCollider.collider.Radius, v_Speed);
					ImGui::Text("Center "); ImGui::SameLine();  ImGui::DragFloat3("##capsulecollidercenter", glm::value_ptr(capsuleCollider.collider.Center), v_Speed);
					ImGui::Text("Height "); ImGui::SameLine();  ImGui::DragFloat("##capsulecolliderheight", &capsuleCollider.collider.Height, v_Speed);


					ImGui::Text("Is Trigger"); ImGui::SameLine();

					bool tr = true;
					ImGui::Checkbox("##istrigercapsulecollider", &tr);

					capsuleCollider.collider.Center = m_Entity->GetComponent<TransformComponent>().Position;
					capsuleCollider.collider.SetRadius(m_Entity->GetComponent<TransformComponent>().Scale.x / 2.0f);

					ImGui::TreePop();
				}
				ImGui::PopStyleVar();
			}

			if (m_Entity->HasComponent<RigidBodyComponent>()) {
				auto& rb = m_Entity->GetComponent<RigidBodyComponent>();

				ImGui::Separator();
				ImGui::PushStyleVar(ImGuiStyleVar_FramePadding, ImVec2{ 4,4 });
				
				if (ImGui::TreeNodeEx((void*)typeid(rb).hash_code(), treeNodeFlags, "RigidBody Component")) {

					auto& mass = rb.rigidbody.GetMass();

					rb.rigidbody.ApplyPhysicMaterial();

					ImGui::PushItemWidth(100); ImGui::Text("Mass               "); ImGui::PopItemWidth();  ImGui::SameLine(); ImGui::PushItemWidth(160);  ImGui::DragFloat("##rigidbodymass", &mass, v_Speed); ImGui::PopItemWidth();
					ImGui::PushItemWidth(100);  ImGui::Text("Linear Drag  "); ImGui::PopItemWidth();  ImGui::SameLine(); ImGui::PushItemWidth(160); ImGui::DragFloat("##rigidbodylindrag", &rb.rigidbody.GetLinearDrag(), v_Speed); ImGui::PopItemWidth();
					ImGui::PushItemWidth(100);  ImGui::Text("Angular Drag");  ImGui::PopItemWidth();  ImGui::SameLine(); ImGui::PushItemWidth(160);  ImGui::DragFloat("##rigidbodyangdrag", &rb.rigidbody.GetAngularDrag(), v_Speed); ImGui::PopItemWidth();

					rb.rigidbody.SetMass(mass);

					//ImGui::Text("Radius "); ImGui::SameLine();  ImGui::DragFloat("##circlecolliderradius", &circleCollider.collider.Radius, v_Speed);
					//ImGui::Text("Center "); ImGui::SameLine();  ImGui::DragFloat3("##circlecollidercenter", glm::value_ptr(circleCollider.collider.Center), v_Speed);

					ImGui::Text("Use Gravity  "); ImGui::SameLine();
					ImGui::Checkbox("##rigidbodygravity", &rb.rigidbody.TakesGravity());

					ImGui::Text("Is Kinematic"); ImGui::SameLine();
					ImGui::Checkbox("##rigidbodykinematic", &rb.rigidbody.IsKinematic());

					ImGuiTreeNodeFlags flags = ImGuiTreeNodeFlags_DefaultOpen;
					auto openPtr = true;

					if (ImGui::TreeNodeEx("##rigidbodyconstrains", flags, "Constranins")) {

						ImGui::Text("Freeze Position"); ImGui::SameLine();	
						ImGui::Checkbox("X",&openPtr); ImGui::SameLine(); ImGui::Checkbox("Y", &openPtr); ImGui::SameLine(); ImGui::Checkbox("Z", &openPtr);

						ImGui::Text("Freeze Rotation"); ImGui::SameLine();
						ImGui::Checkbox("X", &openPtr); ImGui::SameLine(); ImGui::Checkbox("Y", &openPtr); ImGui::SameLine(); ImGui::Checkbox("Z", &openPtr);

						ImGui::TreePop();
					}

					ImGui::TreePop();



				}

				ImGui::PopStyleVar();

			}

			if (m_Entity->HasComponent<LightComponent>()) {
				auto& light = m_Entity->GetComponent<LightComponent>();
				light.light.SetPosition(m_Entity->GetComponent<TransformComponent>().Position);

				ImGui::Separator();
				ImGui::PushStyleVar(ImGuiStyleVar_FramePadding, ImVec2{ 4,4 });
				
				if (ImGui::TreeNodeEx((void*)&light, treeNodeFlags, "Light Component")) {
					ImGui::ColorEdit3("##AmbientColor", glm::value_ptr(light.light.GetAmbientColor()));

					std::string m_CurrentValue;
					switch (light.light.m_Mode)
					{
					case DIRECTIONAL_LIGHT:
						m_CurrentValue = "Directional Light";
						break;
					case POINT_LIGHT:
						m_CurrentValue = "Point Light";
						break;
					case SPOTLIGHT:
						m_CurrentValue = "Spotlight";
						break;
					default:
						break;
					}

					if (ImGui::BeginCombo("##lightmodecombo", m_CurrentValue.c_str())) // The second parameter is the label previewed before opening the combo.
					{
						if (ImGui::Selectable("Directional Light", (m_CurrentValue == "Directional Light")))
						{
							light.light.SetMode(DIRECTIONAL_LIGHT);
						}

						if (ImGui::Selectable("Point Light", (m_CurrentValue == "Point Light")))
						{
							light.light.SetMode(POINT_LIGHT);
							// TODO: change later mode 
						}

						if (ImGui::Selectable("Spotlight", (m_CurrentValue == "Spotlight")))
						{
							light.light.SetMode(SPOTLIGHT);
							// TODO: change later mode 
						}

						ImGui::EndCombo();
					}
					ImGui::TreePop();
				}

				ImGui::PopStyleVar();
			}

			if (m_Entity->HasComponent<MaterialComponent>()) {
				auto& material = m_Entity->GetComponent<MaterialComponent>();

				ImGui::Separator();
				ImGui::PushStyleVar(ImGuiStyleVar_FramePadding, ImVec2{ 4,4 });
				
				if (ImGui::TreeNodeEx((void*)&material, treeNodeFlags, "Material Component")) {

					ImGui::Text("Basic Material");

					ImGui::ColorEdit3("Color", glm::value_ptr(material.material.GetColor()));

					ImGui::Text("Shininess: "); ImGui::SameLine();
					ImGui::PushItemWidth(160);
					ImGui::DragFloat("    ", &material.material.GetShininess(), 1.f, 1.f, 145.f);
					ImGui::PopItemWidth();

					if (!material.material.IsTextured()) {
						if (ImGui::TreeNodeEx((void*)323243242463, treeNodeFlags, "Diffuse map")) {
							if (ImGui::ImageButton((void*)m_Transparent->GetId(), { 55,55 })) {
								material.material.AddDiffuseTexture(new Texture(GetTexturePath().c_str()));
							}
							ImGui::SameLine();
							ImGui::Text("Use  "); ImGui::SameLine();
							ImGui::Checkbox("##materialdiffuseused", &material.material.IsTextured());

							ImGui::TreePop();
						}

						if (ImGui::TreeNodeEx((void*)324324324324324, treeNodeFlags, "Specular map")) {
							if (ImGui::ImageButton((void*)m_Transparent->GetId(), { 55,55 })) {
								material.material.AddSpecularTexture(new Texture(GetTexturePath().c_str()));
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
						if (ImGui::TreeNodeEx((void*)3232432424634, treeNodeFlags, "Diffuse map")) {
							if (ImGui::ImageButton((void*)material.material.GetDiffuseTexture().GetId(), { 55,55 })) {
								material.material.AddDiffuseTexture(new Texture(GetTexturePath().c_str()));
							}
							ImGui::SameLine();
							ImGui::Text("Use  "); ImGui::SameLine();
							ImGui::Checkbox("##materialdiffuseused", &material.material.IsTextured());

							ImGui::TreePop();
						}

						if (ImGui::TreeNodeEx((void*)3243243243243244, treeNodeFlags, "Specular map")) {
							if (ImGui::ImageButton((void*)material.material.GetSpecularTexture().GetId(), { 55,55 })) {
								material.material.AddSpecularTexture(new Texture(GetTexturePath().c_str()));
							}
							ImGui::SameLine();
							ImGui::Text("Use  "); ImGui::SameLine();
							ImGui::Checkbox("##materialspecularused", &material.material.IsTextured());

							ImGui::TreePop();
						}
					}

					ImGui::TreePop();
				}

				ImGui::PopStyleVar();
			}

			if (m_Entity->HasComponent<AnimationComponent>()) {
				auto& ac = m_Entity->GetComponent<AnimationComponent>();

				ImGui::Separator();
				ImGui::PushStyleVar(ImGuiStyleVar_FramePadding, ImVec2{ 4,4 });
				if (ImGui::TreeNodeEx((void*)&ac, treeNodeFlags, "Animation Component")) {

			

					if (ImGui::Button("Add Animation"))
					{
						if (std::string path = FileDialogs::OpenFile("Animation File (*.dae)\0*.dae\0(*.fbx)\0*.fbx\0"); path.length() > 0) {
							std::string animationName = FilesystemUtils::GetFilenameFromPath(path);

							ac.AddAnimation(animationName, path);
						}
					}


					ImGui::Text("Playable  "); ImGui::SameLine();

					ImGui::PushItemWidth(150);
					if (ImGui::BeginCombo("##cameratargetcombo", ac.selectedAnimation.empty() ? "Empty" : ac.selectedAnimation.c_str())) // The second parameter is the label previewed before opening the combo.
					{
						
						for (auto& anim : ac.animations)
						{
							if (ImGui::Selectable(anim.first.c_str())) {
								ac.selectedAnimation = anim.first;
							}
						}

						ImGui::EndCombo();
					}
					ImGui::PopItemWidth();
		

					ImGui::TreePop();
				}
				ImGui::PopStyleVar();
			}

			if (m_Entity->HasComponent<TerrainComponent>())
			{
				auto& tc = m_Entity->GetComponent<TerrainComponent>();

				ImGui::Separator();
				ImGui::PushStyleVar(ImGuiStyleVar_FramePadding, ImVec2{ 4,4 });
				if (ImGui::TreeNodeEx((void*)&tc, treeNodeFlags, "Terrain Component")) {

					auto& sizeX = tc.terrain.GetGridSizeX();
					auto& sizeZ = tc.terrain.GetGridSizeZ();

					ImGui::Text("Grid Size X"); ImGui::SameLine();  ImGui::DragFloat("##terraingridx", &sizeX, v_Speed);
					ImGui::Text("Grid Size Z"); ImGui::SameLine();  ImGui::DragFloat("##terraingridz", &sizeZ, v_Speed);


					if (ImGui::ImageButton((void*)m_Transparent->GetId(), { 55,55 })) {
						if (std::string pathStdString = FileDialogs::OpenFile("Image File (*.png)\0*.png\0(*.jpg)\0*.jpg\0"); pathStdString.length() != 0) {
							tc.terrain.SetHeightMapFromResource(pathStdString);
							m_Entity->GetComponent<MeshComponent>().mesh = tc.terrain.GetTerrainMesh();
						}
					}


					if (ImGui::Button("Apply"))
					{
						tc.terrain.SetGridSize(sizeX, sizeZ);
						m_Entity->GetComponent<MeshComponent>().mesh = tc.terrain.GetTerrainMesh();
					}



					ImGui::TreePop();
				}

				ImGui::PopStyleVar();
			}

			if (m_Entity->HasComponent<PBRMaterialComponent>())
			{
				auto& mt = m_Entity->GetComponent<PBRMaterialComponent>();

				ImGui::Separator();
				ImGui::PushStyleVar(ImGuiStyleVar_FramePadding, ImVec2{ 4,4 });
				if (ImGui::TreeNodeEx((void*)&mt, treeNodeFlags, "PBRMaterial Component"))
				{
					std::string name = mt.material.GetName() == "" ? "None" : mt.material.GetName();
					
					ImGui::Text("Material"); ImGui::SameLine();

					ImGui::Button(name.c_str(), {180,25});

					if (ImGui::BeginDragDropTarget()) {

						const ImGuiPayload* payload = ImGui::AcceptDragDropPayload("contentelement");

						if (payload) {
							const wchar_t* payloadPath = (const wchar_t*)payload->Data;
							const char* cstr = (const char*)payloadPath;
							std::string finalPath = std::string(cstr);

							std::filesystem::path filesystemPath = finalPath;
							std::filesystem::directory_entry it(filesystemPath);

							if (!it.is_directory()) {
								if (filesystemPath.has_extension()) {
									auto ext = filesystemPath.extension().string();

									if (ext == ".rcasset") {
										mt.material.Apply(finalPath);
									}
								}
							}
						}

						ImGui::EndDragDropTarget();
					}

					ImGui::TreePop();
				}

				ImGui::PopStyleVar();
			}

			if (m_Entity->HasComponent<CameraComponent>())
			{
				auto& cameraComponent = m_Entity->GetComponent<CameraComponent>();

				ImGui::Separator();
				ImGui::PushStyleVar(ImGuiStyleVar_FramePadding, ImVec2{ 4,4 });
				
				if (ImGui::TreeNodeEx((void*)&cameraComponent, treeNodeFlags, "Camera Component")) {

					ImGui::PushItemWidth(100);	ImGui::Text("Fov"); ImGui::PopItemWidth(); ImGui::SameLine(); ImGui::PushItemWidth(100); ImGui::DragFloat("##cameracomponentfov", &cameraComponent.camera->GetFov(), 0.1f); ImGui::PopItemWidth();
					ImGui::PushItemWidth(100); ImGui::Text("Near Plane"); ImGui::PopItemWidth(); ImGui::SameLine(); ImGui::PushItemWidth(100);  ImGui::DragFloat("##cameracomponentnear", &cameraComponent.camera->GetNearPlane(), 0.1f); ImGui::PopItemWidth();
					ImGui::PushItemWidth(100); ImGui::Text("Far Plane"); ImGui::PopItemWidth(); ImGui::SameLine();  ImGui::PushItemWidth(100);  ImGui::DragFloat("##cameracomponentfar", &cameraComponent.camera->GetFarPlane(), 1.f);  ImGui::PopItemWidth();

					ImGui::Text("Primary"); ImGui::SameLine();

					if (ImGui::Checkbox("##cameraprimary", &cameraComponent.Primary))
					{
						for (auto& entity : scene.GetManager().GetEntities())
						{
							if (entity->HasComponent<CameraComponent>())
							{
								if (m_Entity != &(*entity))
								{
									entity->GetComponent<CameraComponent>().Primary = false;
								}
							}
						}
					}

					ImGui::Text("Target  "); ImGui::SameLine();

					ImGui::PushItemWidth(150);
					if (ImGui::BeginCombo("##cameratargetcombo", 
						cameraComponent.camera->HasTarget() ? cameraComponent.camera->GetTarget()->GetComponent<TagComponent>().tag.c_str() : "Empty")) // The second parameter is the label previewed before opening the combo.
					{
						Entity* m_CurrentEntity = cameraComponent.camera->HasTarget() ? cameraComponent.camera->GetTarget() : nullptr;
						for(auto & entity : scene.GetManager().GetEntities())
						{
							if (m_Entity != &(*entity)) {
								auto& tagComponent = entity->GetComponent<TagComponent>();

								if (ImGui::Selectable(tagComponent.tag.c_str(),
									m_CurrentEntity ? (m_CurrentEntity->GetComponent<TagComponent>().tag.c_str() == tagComponent.tag.c_str()) : false))
								{
									m_CurrentEntity = &(*entity);
									cameraComponent.camera->LookAt(m_CurrentEntity);
								}
							}
						}
				
						ImGui::EndCombo();
					}
					ImGui::PopItemWidth();

					ImGui::TreePop();
				}
				ImGui::PopStyleVar();
			}

			if (m_Entity->HasComponent<ScriptComponent>()) {
				auto& scriptComponent = m_Entity->GetComponent<ScriptComponent>();



				for (size_t i = 0; i < scriptComponent.Scripts.size(); i++) {

					std::string componentName = scriptComponent.Scripts[i]->class_name + " (Script Component)";

					ImGui::Separator();
					ImGui::PushStyleVar(ImGuiStyleVar_FramePadding, ImVec2{ 4,4 });

					if (ImGui::TreeNodeEx((void*)(&scriptComponent + i), treeNodeFlags, componentName.c_str()))
					{
						for (size_t j = 0; j < scriptComponent.Scripts[i]->properties.size(); j++) {

							auto prop = scriptComponent.Scripts[i]->properties[j];


							if (prop.name != "input") {
								ImGui::Text(prop.name.c_str());
							}


							if (prop.type == Float || prop.type == Int)
							{
								ImGui::SameLine();

								std::string properyHidName = "##script" + std::to_string(i) + "property" + std::to_string(j);
								float var = static_cast<float>(scriptComponent.Scripts[i]->GetVarFloat(prop.name));
								ImGui::PushItemWidth(100);
								ImGui::DragFloat(properyHidName.c_str(), &var, 0.1f);
								ImGui::PopItemWidth();
								scriptComponent.Scripts[i]->SetVar(prop.name, var);
							}

							else if (prop.name != "input" && prop.type == USERDATA)
							{
								ImGui::SameLine();

								std::string comboName = "##comboscript" + std::to_string(i) + "var" + std::to_string(j);

								if (ImGui::BeginCombo(comboName.c_str(), "Null")) // The second parameter is the label previewed before opening the combo.
								{

									for (auto& entity : scene.GetManager().GetEntities())
									{
										if (ImGui::Selectable(entity->GetName().c_str()))
										{
											scriptComponent.Scripts[i]->SetVar(prop.name, static_cast<int>(entity->GetId()));
										}
									}


									ImGui::EndCombo();
								}
							}

						}

						ImGui::PopStyleVar();


						ImGui::TreePop();
					}
				}
			}


			if (ImGui::Button("Add Component")) {
				ImGui::OpenPopup("AddComponent");
			}

			if (ImGui::BeginPopup("AddComponent")) {

				if (!m_Entity->HasComponent<MeshComponent>()) {
					if (ImGui::MenuItem("Mesh Component")) {

						Mesh* mesh = ObjectAdditor::CreateMesh(DefaultObjects::Cube);
						glm::vec3 defaultColor = { 0.8,0.8,0.8 };
						m_Entity->AddComponent<MeshComponent>(*mesh, defaultColor);
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
							auto* rb = new RigidBody(&cc, 1.0f, 1.0f, 1.0f, glm::vec3(1.0f), glm::vec3(1.0f));
							m_Entity->AddComponent<RigidBodyComponent>(*rb);
						}
						else if (m_Entity->HasComponent<BoxColliderComponent>()) {
							auto& bc = m_Entity->GetComponent<BoxColliderComponent>().collider;
							auto* rb = new RigidBody(&bc, 1.0f, 1.0f, 1.0f, glm::vec3(1.0f), glm::vec3(1.0f));
							m_Entity->AddComponent<RigidBodyComponent>(*rb);
						}
						else if(m_Entity->HasComponent<CapsuleColliderComponent>())
						{
							auto& cc = m_Entity->GetComponent<CapsuleColliderComponent>().collider;
							auto* rb = new RigidBody(&cc, 1.0f, 1.0f, 1.0f, glm::vec3(1.0f), glm::vec3(1.0f));
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
							m_Entity->AddComponent<BoxColliderComponent>(transform.Scale, transform.Position, transform.Rotation);
						}
					}
				}

				if (!m_Entity->HasComponent<CapsuleColliderComponent>()) {
					if (ImGui::MenuItem("CapsuleCollider Component")) {
						if (m_Entity->HasComponent<TransformComponent>()) {
							auto& transform = m_Entity->GetComponent<TransformComponent>();
							m_Entity->AddComponent<CapsuleColliderComponent>(transform.Position, transform.Rotation, transform.Scale.y, transform.Scale.x / 2.f);
						}
					}
				}

				if (!m_Entity->HasComponent<CircleColliderComponent>()) {
					if (ImGui::MenuItem("CircleCollider Component")) {
						auto& tc = m_Entity->GetComponent<TransformComponent>();
						m_Entity->AddComponent<CircleColliderComponent>(tc.Scale.x, tc.Position, tc.Rotation);
					}
				}

				if (!m_Entity->HasComponent<MaterialComponent>()) {
					if (ImGui::MenuItem("Material Component")) {
						Material* material = new Material();
						m_Entity->AddComponent<MaterialComponent>(*material);

					}

				}

				if (!m_Entity->HasComponent<PBRMaterialComponent>())
				{
					if (ImGui::MenuItem("PBRMaterial Component"))
					{
						auto* material = new PBRMaterial();
						m_Entity->AddComponent<PBRMaterialComponent>(*material);
					}
				}

				if (!m_Entity->HasComponent<DirectionalLightComponent>()) {
					if (ImGui::MenuItem("Directional Light")) {
						auto* light = new DirectionalLight(glm::vec3(50.0f), glm::vec3(0.1f, 0.3f, 0.2f), glm::vec3(0.7f, 0.42f, 0.26f), glm::vec3(0.7f, 0.7f, 0.7f), glm::vec3(1.0f));

						m_Entity->AddComponent<DirectionalLightComponent>(*light);
					}
				}

				if (!m_Entity->HasComponent<LightPointComponent>()) {
					if (ImGui::MenuItem("Point Light")) {
						auto* light = new LightPoint(m_Entity->GetComponent<TransformComponent>().Position, glm::vec3(0.1f, 0.3f, 0.2f), glm::vec3(0.7f, 0.42f, 0.26f), glm::vec3(0.7f, 0.7f, 0.7f), glm::vec3(1.0f), 1.0f, 0.09f, 0.032f);

						m_Entity->AddComponent<LightPointComponent>(*light, m_Entity->GetComponent<TransformComponent>().Position);


					}
				}


				if (!m_Entity->HasComponent<AnimationComponent>()) {
					if (ImGui::MenuItem("Animation Component")) {
						auto* model = new AnimatedModel("resources/animations/girl/Idle.dae"); // TODO: Testing animation model!  change later
						std::string idlePath = "resources/animations/girl/Idle.dae";
						auto* anim = new Animation(idlePath, model);

						auto* animator = new Animator(anim);


						m_Entity->AddComponent<AnimationComponent>(*model, *animator);
						m_Entity->GetComponent<AnimationComponent>().AddAnimation("Idle", idlePath);
					}
				}

				if (!m_Entity->HasComponent<CameraComponent>())
				{
					if (ImGui::MenuItem("Camera Component")) {
						m_Entity->AddComponent<CameraComponent>();
					}
				}

				if (m_Entity->HasComponent<ScriptComponent>()) {
					for (size_t i = 0; i < scene.GetScriptManager().m_LoadedScripts.size(); i++) {
						const char* className = scene.GetScriptManager().m_LoadedScripts[i].m_ClassName.c_str();

						if (ImGui::MenuItem(className)) {
							if (scene.GetScriptManager().m_LoadedScripts[i].valide)
							{
								m_Entity->GetComponent<ScriptComponent>().AddScript(scene.GetScriptManager().ScriptInstanceClass(m_Entity->GetId(), className));
								m_Entity->GetComponent<ScriptComponent>().Start();
							}
						}

					}
				}




				ImGui::EndPopup();
			}


		}

		}
	}
	else {
		const ImGuiTreeNodeFlags treeNodeFlags = ImGuiTreeNodeFlags_DefaultOpen | ImGuiTreeNodeFlags_AllowItemOverlap;

		char buffer[256];

		memset(buffer, 0, sizeof(buffer));

		strcpy_s(buffer, sizeof(buffer), "Main Camera");

		float v_Speed = 0.1f;


		if (ImGui::TreeNodeEx((void*)typeid(scene.GetMainCamera()).hash_code(), treeNodeFlags, "Main Camera")) {
			ImGui::Text("Tag     "); ImGui::SameLine();
			if (ImGui::InputText(" ", buffer, IM_ARRAYSIZE(buffer))) {

			}
			ImGui::TreePop();
		}

		if (ImGui::TreeNodeEx((void*)(typeid(scene.GetMainCamera()).hash_code() + 1), ImGuiTreeNodeFlags_DefaultOpen, "Camera Properties")) {

			ImGui::Text("Speed"); ImGui::SameLine();  ImGui::DragFloat("##maincameraspeed", &scene.GetMainCamera().GetSpeed(), v_Speed, 3.0f, 100.f);
			ImGui::Text("Fov      "); ImGui::SameLine();  ImGui::DragFloat("##maincamerafov", &scene.GetMainCamera().GetFov(), v_Speed, 30.0f, 120.f);
			//ImGui::Text("Rotation"); ImGui::SameLine(); ImGui::DragFloat3("##trotation", glm::value_ptr(tc.Rotation), v_Speed);
			//ImGui::Text("Scale       "); ImGui::SameLine(); ImGui::DragFloat3("##tscale", glm::value_ptr(tc.Scale), v_Speed);

			ImGui::TreePop();

		}



	}

	ImGui::End();
}
