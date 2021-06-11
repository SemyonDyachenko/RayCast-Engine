#ifndef EDITOR_SCENE_H
#define EDITOR_SCENE_H

#include <GL/glew.h>
#include "../Game/Scenes/Scene.h"
#include "../../Runtime/Camera/Camera.h"
#include "../../Runtime/Rendering/Shader.h"
#include "../../Runtime/Rendering/Model.h"
#include "../../Runtime/Rendering/FrameBuffer.h"
#include "../../Vendor/imgui/imgui.h"
#include "../../Vendor/imgui/imgui_impl_glfw.h"
#include "../../Vendor/imgui/imgui_impl_opengl3.h"
#include "EditorSceneObject.h"


class EditorScene : public Scene {
public:
	void OnCreate() override;
	void OnDestroy() override;

	void ImGuiScene();

	void OnActivate() override;

	void OnDeactivate() override;

	void OnUpdate(float DeltaTime) override;

	void OnRender() override;

private:
	Camera* m_MainCamera;
	Shader* m_editorShader;
	Shader* framebuffer_shader;
	std::unique_ptr<FrameBuffer> m_FrameBuffer;
	std::vector<EditorSceneObject*> m_Objects;

};

#endif