#ifndef EDITOR_SCENE_H
#define EDITOR_SCENE_H

#include <GL/glew.h>


#include "../../Runtime/Entity/Scene.h"
#include "../../Runtime/Camera/Camera.h"
#include "../../Runtime/Rendering/Shader.h"
#include "../../Runtime/Rendering/Model.h"
#include "../../Runtime/Rendering/Cubemap.h"
#include "../../Runtime/Rendering/FrameBuffer.h"


#include "../../Runtime/Core/Event.h"
#include "../../Runtime/Light/LightPoint.h"

#include "../../Runtime/PhysicsEngine/DynamicWorld.h"
#include "../../Runtime/Rendering/Terrain/Terrain.h"

#include "../../Runtime/Rendering/Renderer.h"
#include "../../Runtime/Rendering/Materials/PBRMaterial.h"
#include "../../Runtime/Rendering/Water/WaterMesh.h"
#include "../../Runtime/Rendering/Water/WaterFrameBuffers.h"

#include "../../Runtime/Scripts/ScriptEngine.h"

#include "../../Runtime/Entity/CameraComponent.h"


class EditorScene : public Scene {
public:
	void OnCreate() override;
	void OnDestroy() override;

	void OnActivate() override;

	void OnDeactivate() override;

	void InitDefaultEntities();

	Entity& CreateEntity(unsigned int id, std::string name) override;
	void DeleteEntity(unsigned int id) override;

	std::unique_ptr<Entity>& GetEntity(unsigned int id);

	bool& IsPhysicsSimulation() { return physicsSimulation; }

	unsigned int GetEntitiesCount();
	void RecalculateEntitiesCount();

	void SimulatePhysics() { physicsSimulation = true; }
	void StopSimulatePhyiscs() { physicsSimulation = false; }

	DynamicWorld& GetPhysicsWorld() { return *m_PhysicsWorld; }

	void UpdateMainCamera(float DeltaTime);

	void SendCameraMatricesToShaderProgram(Camera * camera) const;

	void OnUpdate(float DeltaTime) override;

	EditorCamera& GetMainCamera();

	void AddLight() { m_LightCount++; }
	void RemoveLight() { if (m_LightCount >= 0) m_LightCount--; }

	void SetLightCount(int count) { m_LightCount = count; }

	int GetLightCount() { return m_LightCount; }

	void RecompileScripts();

	std::unique_ptr<Entity>& SelectEntityByRayCast(glm::vec3 & mouseRay);

	void OnRender() override;

	bool OnStart() { return m_OnStart; }

	void Play() { m_OnStart = true; }
	void Pause() { m_OnStart = false; }

	void InitMainCharacter();

	ScriptManager& GetScriptManager() { return *m_ScriptManager; }

	std::shared_ptr<FrameBuffer>& GetViewPortBuffer() { return m_ViewPortFrameBuffer; }

private:
	EditorCamera* m_MainCamera;

	Shader* m_editorShader;
	Shader* m_skyboxShader;
	Shader* m_animationShader;
	Shader* m_MaterialShader;
	bool physicsSimulation;
	DynamicWorld* m_PhysicsWorld;

	Cubemap* m_EditorSkybox;

	bool m_OnStart = false;

	unsigned int m_LightCount = 0;

	std::shared_ptr<FrameBuffer> m_ViewPortFrameBuffer;

};

#endif