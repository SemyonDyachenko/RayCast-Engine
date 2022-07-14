#ifndef EDITOR_SCENE_H
#define EDITOR_SCENE_H

#include <glad/glad.h>

#include "../Game/Scenes/Scene.h"
#include "../../Runtime/Camera/Camera.h"
#include "../../Runtime/Rendering/Shader.h"
#include "../../Runtime/Rendering/Model.h"
#include "../../Runtime/Rendering/Cubemap.h"
#include "../../Runtime/Rendering/FrameBuffer.h"
#include "../../Vendor/imgui/imgui.h"
//#include "../../Vendor/imgui/imgui_impl_glfw.h"
//#include "../../Vendor/imgui/imgui_impl_opengl3.h"
#include "EditorSceneObject.h"
#include "../../Runtime/Core/Event.h"
#include "../../Runtime/Light/LightPoint.h"

#include "../../Runtime/PhysicsEngine/DynamicWorld.h"
#include "../../Runtime/Rendering/Terrain/Terrain.h"




class EditorScene : public Scene {
public:
	void OnCreate() override;
	void OnDestroy() override;

	void ImGuiScene();

	void OnActivate() override;

	void OnDeactivate() override;

	Entity& CreateEntity(unsigned int id,std::string name) override;
	void DeleteEntity(unsigned int id) override;

	std::unique_ptr<Entity>& GetEntity(unsigned int id);

	bool& IsPhysicsSimulation() { return physicsSimulation; }

	unsigned int GetEntitiesCount();
	void RecalculateEntitiesCount();

	void SimulatePhysics() { physicsSimulation = true; }
	void StopSimulatePhyiscs() { physicsSimulation = false; }

	DynamicWorld& GetPhysicsWorld() { return *m_PhysicsWorld; }

	void UpdateMainCamera(float DeltaTime);

	void OnUpdate(float DeltaTime) override;

	Camera& GetMainCamera();

	void OnRender() override;

private:
	Camera* m_MainCamera;
	Shader* m_editorShader;
	bool physicsSimulation;
	DynamicWorld* m_PhysicsWorld;

	Terrain* m_Terrain;
};

#endif