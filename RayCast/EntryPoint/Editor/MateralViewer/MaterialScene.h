#ifndef MATERIAL_SCENE_H
#define MATERIAL_SCENE_H


#include "../../../Runtime/Rendering/Mesh.h"
#include "../../../Runtime/Light/Light.h"
#include "../../../Runtime/Rendering/Materials/PBRMaterial.h"
#include "../../../Runtime/Camera/Camera.h"
#include "../../../Runtime/Rendering/FrameBuffer.h"

#include "../../../Runtime/Rendering/Renderer.h"


class MaterialScene
{
public:
	MaterialScene();
	virtual ~MaterialScene();

	void ApplyMaterial(MaterialStructure & material);

	void LoadMaterial();

	void Update(float DeltaTime);

	void Render();

	PBRMaterial& GetMaterial() { return *m_Material; }

	std::shared_ptr<FrameBuffer>& GetFrameBuffer() { return m_FrameBuffer; }

private:
	Light* m_DirectionalLight;
	Mesh* m_Sphere;
	Shader* m_Shader;
	MaterialStructure m_CurrentMaterial;
	PBRMaterial* m_Material;
	Camera* m_Camera;
	std::shared_ptr<FrameBuffer> m_FrameBuffer;
};

#endif