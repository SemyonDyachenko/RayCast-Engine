#include "../../stdafx.h"
#include "EditorScene.h"
#include "../../Runtime/Core/Game.h"
#include "GuiComponents/ObjectAdditor.h"



void EditorScene::OnCreate()
{
	m_MainCamera = new EditorCamera(glm::vec3(0.0f, 2.0f, 5.f), 1280.f / 720.f, glm::vec3(0.f, 1.f, 0.f), glm::vec3(0.f, 0.f, -1.f), 60.f, 0.1f, 1000.f);
	m_editorShader = new Shader("resources/shaders/vertex_shader.glsl", "resources/shaders/fragment_shader.glsl");
	m_skyboxShader = new Shader("resources/shaders/cubemap/cubemap_vertex_shader.glsl", "resources/shaders/cubemap/cubemap_fragment_shader.glsl");
	m_animationShader = new Shader("resources/shaders/animated_vertex_shader.glsl", "resources/shaders/materials/rbp_fragment_shader.glsl");
	m_MaterialShader = new Shader("resources/shaders/materials/rbp_vertex_shader.glsl", "resources/shaders/materials/rbp_fragment_shader.glsl");
	m_EntitiesCount = m_Manager.GetEntitiesCount();
	m_PhysicsWorld = new DynamicWorld();
	physicsSimulation = false;

	m_EditorSkybox = new Cubemap();
	m_ScriptManager = new ScriptManager();
	RecompileScripts();

	m_ScriptManager->Start();

	FrameBufferProps m_ViewPortProps;
	m_ViewPortProps.Attachments = { FrameBufferTextureFormat::RGBA8,FrameBufferTextureFormat::RED_INTEGER,FrameBufferTextureFormat::Depth };
	m_ViewPortProps.Width = 1280;
	m_ViewPortProps.Height = 720;
	m_ViewPortFrameBuffer = FrameBuffer::Create(m_ViewPortProps);

	for (auto& entity : m_Manager.GetEntities()) {
		if (entity->HasComponent<ScriptComponent>()) {
			entity->GetComponent<ScriptComponent>().Start();
		}
	}

	InitDefaultEntities();
}

void EditorScene::OnDestroy()
{
	delete m_MainCamera;
	delete m_editorShader;
	delete m_skyboxShader;
	delete m_animationShader;
	delete m_MaterialShader;
	delete m_PhysicsWorld;
}


void EditorScene::OnActivate()
{
}

void EditorScene::OnDeactivate()
{
}

void EditorScene::InitDefaultEntities()
{
	auto& entity = CreateEntity(GetEntitiesCount(), "Directional Light");
	auto* light = new Light(GetLightCount(), LightMode::DIRECTIONAL_LIGHT, entity.GetComponent<TransformComponent>().Position, glm::vec3(150.f, 150.f, 150.f));
	AddLight();
	entity.GetComponent<TransformComponent>().SetPosition({ 10.f, 10.f, 10.f });
	light->SetPosition(entity.GetComponent<TransformComponent>().GetPosition());
	entity.AddComponent<LightComponent>(*light);
	RecalculateEntitiesCount();
	InitMainCharacter();
}


Entity& EditorScene::CreateEntity(unsigned int id, std::string name)
{
	return m_Manager.CreateEntity(id, name);
}

void EditorScene::DeleteEntity(unsigned int id)
{
	for (auto& entity : m_Manager.GetEntities()) {
		if (entity->GetId() == id) {
			if (entity->HasComponent<LightComponent>()) {
				RemoveLight();
			}
		}
	}
	m_Manager.DeleteEntity(id);
	RecalculateEntitiesCount();
}


std::unique_ptr<Entity>& EditorScene::GetEntity(unsigned int id)
{
	for (auto& entity : m_Manager.GetEntities()) {
		if (entity->GetId() == id) {
			return entity;

		}
	}
}


unsigned int EditorScene::GetEntitiesCount()
{
	return  m_EntitiesCount;
}

void EditorScene::RecalculateEntitiesCount()
{
	m_EntitiesCount = m_Manager.GetEntitiesCount();
}



void EditorScene::UpdateMainCamera(float DeltaTime)
{
	if (!m_OnStart) {
		if (Input::IsKeyPressed(Input::KEY_W)) {
			m_MainCamera->Move(EditorCameraDirection::FORWARD, DeltaTime);
		}
		if (Input::IsKeyPressed(Input::KEY_S)) {
			m_MainCamera->Move(EditorCameraDirection::BACK, DeltaTime);
		}
		if (Input::IsKeyPressed(Input::KEY_A)) {
			m_MainCamera->Move(EditorCameraDirection::LEFT, DeltaTime);
		}
		if (Input::IsKeyPressed(Input::KEY_D)) {
			m_MainCamera->Move(EditorCameraDirection::RIGHT, DeltaTime);
		}
		if (Input::IsKeyPressed(Input::KEY_SPACE)) {
			m_MainCamera->Move(EditorCameraDirection::UP, DeltaTime);
		}
		if (Input::IsKeyPressed(Input::KEY_LSHIFT)) {
			m_MainCamera->Move(EditorCameraDirection::DOWN, DeltaTime);
		}
	}
}

void EditorScene::SendCameraMatricesToShaderProgram(Camera* camera) const
{
	m_editorShader->SetMat4("ProjectionMatrix", camera->GetProjectionMatrix());
	m_animationShader->use();
	m_animationShader->SetVec3("camPos", camera->GetPosition());

	m_MaterialShader->use();
	m_MaterialShader->SetVec3("camPos", camera->GetPosition());

	m_skyboxShader->use();
	m_skyboxShader->SetMat4("ViewMatrix", camera->GetViewMatrix());
	m_skyboxShader->SetMat4("ProjectionMatrix", camera->GetProjectionMatrix());

	m_animationShader->use();
	m_animationShader->SetMat4("ViewMatrix", camera->GetViewMatrix());
	m_animationShader->SetMat4("ProjectionMatrix", camera->GetProjectionMatrix());

	m_MaterialShader->use();
	m_MaterialShader->SetMat4("ViewMatrix", camera->GetViewMatrix());
	m_MaterialShader->SetMat4("ProjectionMatrix", camera->GetProjectionMatrix());
}

void EditorScene::OnUpdate(float DeltaTime)
{

	for (auto& entity : m_Manager.GetEntities())
	{

		if (entity->HasComponent<CameraComponent>())
		{
			auto tc = entity->GetComponent<TransformComponent>();
			auto& camera = entity->GetComponent<CameraComponent>();

		}
	}

	if (!m_OnStart) {

		m_MainCamera->OnUpdate(DeltaTime, Game::GetWindow().GetNativeWindow());

		m_editorShader->use();
		m_editorShader->SetMat4("ViewMatrix", m_MainCamera->GetViewMatrix());
		m_editorShader->SetMat4("ProjectionMatrix", m_MainCamera->GetProjectionMatrix());

		m_editorShader->SetVec3("cameraPos", m_MainCamera->GetPosition());

		m_animationShader->use();
		m_animationShader->SetVec3("camPos", m_MainCamera->GetPosition());

		m_MaterialShader->use();
		m_MaterialShader->SetVec3("camPos", m_MainCamera->GetPosition());

		m_skyboxShader->use();
		m_skyboxShader->SetMat4("ViewMatrix", m_MainCamera->GetViewMatrix());
		m_skyboxShader->SetMat4("ProjectionMatrix", m_MainCamera->GetProjectionMatrix());

		m_animationShader->use();
		m_animationShader->SetMat4("ViewMatrix", m_MainCamera->GetViewMatrix());
		m_animationShader->SetMat4("ProjectionMatrix", m_MainCamera->GetProjectionMatrix());

		m_MaterialShader->use();
		m_MaterialShader->SetMat4("ViewMatrix", m_MainCamera->GetViewMatrix());
		m_MaterialShader->SetMat4("ProjectionMatrix", m_MainCamera->GetProjectionMatrix());

	}
	else
	{
		if (auto * primaryCamera = &(*m_Manager.GetPrimaryCamera()); primaryCamera != nullptr) 
		{
					auto& camera = primaryCamera->GetComponent<CameraComponent>();
			
					SendCameraMatricesToShaderProgram(camera.camera);

		}
		else
		{
			ENGINE_ERROR("Cannot start simulation, Main Camera is missing.");
		}

	}

	m_ScriptManager->InstanceUpdate();


	if (m_OnStart) {
		for (auto& entity : m_Manager.GetEntities())
		{

			if (entity->HasComponent<AnimationComponent>()) {
				entity->GetComponent<AnimationComponent>().Update(DeltaTime);
				entity->GetComponent<AnimationComponent>().Play();
			}

			if (entity->HasComponent<CameraComponent>())
			{
				auto tc = entity->GetComponent<TransformComponent>();
				auto& camera = entity->GetComponent<CameraComponent>();

				camera.camera->SetRotation(tc.Rotation.x, tc.Rotation.y);
				
			}


		}


		if (physicsSimulation) {
			

			if (m_PhysicsWorld->GetNumRigidBodies() > 0) {
				
				for (auto& entity : m_Manager.GetEntities()) {
					if (entity->HasComponent<RigidBodyComponent>()) {
						auto& tc = entity->GetComponent<TransformComponent>();
						auto& rb = entity->GetComponent<RigidBodyComponent>();
						tc.Position = PhysicUtils::BtVec3ToGLM(rb.rigidbody.GetWorldTransform().getOrigin());
						tc.Rotation = glm::eulerAngles(PhysicUtils::BtQuatToGLM(rb.rigidbody.GetWorldTransform().getRotation()));


					}

				}
			}
			m_PhysicsWorld->StepSimulation(DeltaTime);
		}

		m_ScriptManager->Update(DeltaTime);

	}
	else {



		for (auto& entity : m_Manager.GetEntities()) {

			auto& tc = entity->GetComponent<TransformComponent>();

			if (entity->HasComponent<RigidBodyComponent>()) {
				auto& rb = entity->GetComponent<RigidBodyComponent>();
				rb.rigidbody.ResetForce();
				rb.rigidbody.ResetTorque();
				rb.rigidbody.ResetVelocity();
				rb.rigidbody.Teleport(tc.Position, tc.GetQuatRotation());

			}

		}
	}

	m_Manager.Update(DeltaTime);
}

EditorCamera& EditorScene::GetMainCamera()
{
	return *m_MainCamera;
}

void EditorScene::RecompileScripts()
{
	m_ScriptManager->ReloadInterpreter();
	ScriptEngine::InitLua(m_ScriptManager->State);
	m_ScriptManager->RecompileScripts(false);


	luabridge::LuaRef Func = luabridge::getGlobal(m_ScriptManager->State, "Prepare");
	Func(&m_Manager);

	m_ScriptManager->ReinstanceScript();

	for(auto& entity : m_Manager.GetEntities())
	{
		if(entity->HasComponent<ScriptComponent>())
		{
			for(auto& script : entity->GetComponent<ScriptComponent>().Scripts)
			{
				script->m_State = m_ScriptManager->State;
				script->CreateObject(script->class_name.c_str());
				script->ResetVarsValues();
			}
		}
	}

	m_ScriptManager->Start();
}

std::unique_ptr<Entity>& EditorScene::SelectEntityByRayCast(glm::vec3& mouseRay)
{
	auto mouseX = mouseRay.x;
	auto mouseY = mouseRay.y;
	auto mouseZ = mouseRay.z;

	for (auto & entity : m_Manager.GetEntities()) {
		auto transform = entity->GetComponent<TransformComponent>();
		if (mouseX >= transform.GetPosition().x) {
			return entity;
		}
	}
}

void EditorScene::OnRender()
{
	m_ViewPortFrameBuffer->Bind();
	Renderer::Init();
	Renderer::Clear();
	Renderer::SetViewport({ 0, 0, m_ViewPortFrameBuffer->GetFrameBufferProps().Width, m_ViewPortFrameBuffer->GetFrameBufferProps().Height });

	//glViewport(0, 0, m_ViewPortFrameBuffer->GetFrameBufferProps().Width, m_ViewPortFrameBuffer->GetFrameBufferProps().Height);

	
	m_EditorSkybox->Render(*m_skyboxShader);
	for (auto& entity : m_Manager.GetEntities()) {
		if (entity->HasComponent<TransformComponent>()) {
			/*if (!entity->HasComponent<PBRMaterialComponent>()) {
				m_editorShader->use();
				m_editorShader->SetMat4("ModelMatrix", entity->GetComponent<TransformComponent>().GetTrasnform());
				m_editorShader->setInt("lightCount", m_LightCount);*/

			m_MaterialShader->use();
			m_MaterialShader->setInt("lightCount", m_LightCount);

			
			m_MaterialShader->SetMat4("ModelMatrix", entity->GetComponent<TransformComponent>().GetTrasnform());
	

			/*	}
				else {
					if (entity->GetComponent<PBRMaterialComponent>().material.IsActive()) {
						m_MaterialShader->use();
						m_MaterialShader->setInt("lightCount", m_LightCount);
						m_MaterialShader->SetMat4("ModelMatrix", entity->GetComponent<TransformComponent>().GetTrasnform());
					}
					else
					{
						m_editorShader->use();
						m_editorShader->SetMat4("ModelMatrix", entity->GetComponent<TransformComponent>().GetTrasnform());
					}
				}*/
		}

		if (entity->HasComponent<MaterialComponent>()) {
			auto& materialComponent = entity->GetComponent<MaterialComponent>();
			if (materialComponent.material.IsActive()) {
				m_editorShader->use();
				m_editorShader->setBool("textured", true);
				materialComponent.material.SetUniforms(*m_editorShader);

				if (entity->HasComponent<AnimationComponent>()) {
					m_animationShader->use();
					m_animationShader->setBool("textured", true);
					materialComponent.material.SetUniforms(*m_animationShader);
				}
			}
			else {
				m_editorShader->setBool("textured", false);
				m_animationShader->setBool("textured", false);
			}
		}
		else {
			m_editorShader->setBool("textured", false);
		}

		if (entity->HasComponent<PBRMaterialComponent>())
		{
			auto& material = entity->GetComponent<PBRMaterialComponent>();

			if (entity->GetComponent<PBRMaterialComponent>().material.IsActive()) {
				m_MaterialShader->use();
				material.material.SetUniforms(*m_MaterialShader);
			}

		}

		if (!entity->HasComponent<AnimationComponent>())
		{
			if (entity->HasComponent<MeshComponent>()) {
				if (!entity->HasComponent<PBRMaterialComponent>()) {
					m_MaterialShader->use();
					entity->GetComponent<MeshComponent>().mesh.OnRender(*m_MaterialShader);
				}
				else
				{
					if (entity->HasComponent<PBRMaterialComponent>()) {
						if (entity->GetComponent<PBRMaterialComponent>().material.IsActive()) {
							m_MaterialShader->use();
							entity->GetComponent<MeshComponent>().mesh.UseSolidColor(false);
							entity->GetComponent<MeshComponent>().mesh.OnRender(*m_MaterialShader);
						}
						else {
							m_MaterialShader->use();
							entity->GetComponent<MeshComponent>().mesh.OnRender(*m_MaterialShader);
						}
					}
				}
			}
		}


		if (entity->HasComponent<DirectionalLightComponent>()) {
			entity->GetComponent<DirectionalLightComponent>().light.SetUniforms(*m_editorShader);
			if (entity->HasComponent<AnimationComponent>()) {
				entity->GetComponent<DirectionalLightComponent>().light.SetUniforms(*m_animationShader);
			}
		}

		if (entity->HasComponent<LightPointComponent>()) {
			entity->GetComponent<LightPointComponent>().light.SetUniforms(*m_editorShader);
			if (entity->HasComponent<AnimationComponent>()) {
				entity->GetComponent<LightPointComponent>().light.SetUniforms(*m_animationShader);
			}
		}

		if (entity->HasComponent<LightComponent>()) {
			auto& light = entity->GetComponent<LightComponent>();
			light.light.SetUniforms(*m_MaterialShader);
			light.light.SetUniforms(*m_animationShader);
			m_editorShader->setInt("lightCount", m_LightCount);
		}

		if (entity->HasComponent<AnimationComponent>()) {
			m_animationShader->use();
			m_animationShader->SetMat4("ModelMatrix", entity->GetComponent<TransformComponent>().GetTrasnform());
			m_animationShader->setInt("lightCount", m_LightCount);

			auto transforms = entity->GetComponent<AnimationComponent>().animator.GetFinalBoneMatrices();
			for (int i = 0; i < transforms.size(); ++i) {
				m_animationShader->use();
				m_animationShader->SetMat4("bonesTransforms[" + std::to_string(i) + "]",
					transforms[i]);

			}

			m_animationShader->use();
			entity->GetComponent<AnimationComponent>().Render(*m_animationShader);
		}
	}
	m_ViewPortFrameBuffer->Unbind();
}

void EditorScene::InitMainCharacter()
{
	auto& mainCharacter = CreateEntity(GetEntitiesCount(), "Main Chararcter");


	Mesh* mesh = ObjectAdditor::CreateMesh(DefaultObjects::Cube);
	glm::vec3 defaultColor = { 0.8,0.8,0.8 };

	mainCharacter.AddComponent<MeshComponent>(*mesh,defaultColor);

	auto* model = new AnimatedModel("resources/animations/girl/Idle.dae"); // TODO: Testing animation model!  change later
	std::string idlePath = "resources/animations/girl/Idle.dae";
	auto* anim = new Animation(idlePath, model);

	auto* animator = new Animator(anim);

	mainCharacter.AddComponent<AnimationComponent>(*model, *animator);
	mainCharacter.GetComponent<AnimationComponent>().AddAnimation("Idle", idlePath);

	RecalculateEntitiesCount();
}
