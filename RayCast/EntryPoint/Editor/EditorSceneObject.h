#ifndef EDITOR_SCENE_OBJECT
#define EDITOR_SCENE_OBJECT

#include "gtc/matrix_transform.hpp"

#include <vector>
#include "../../Runtime/Rendering/Mesh.h"
#include "../../Runtime/Rendering/Texture.h"
#include "../../Runtime/Rendering/Material.h"
#include "../../Animation/AnimatedModel.h"


class EditorSceneObject
{
public:
	EditorSceneObject(int id, std::string name, std::string type);

	virtual ~EditorSceneObject();

	void Update(float DeltaTime);
	void Render(Shader* shader);

	void AddMesh(Mesh* mesh);
	void AddTexture(Texture* texture);
	void AddMaterial(Material * material);

	Material* GetMaterial();

	void AddAnimatedModel(AnimatedModel* model);
	AnimatedModel& GetAnimatedModel() const;

	void SetPosition(glm::vec3 position);
	void SetRotation(glm::vec3 rotation);
	void SetScale(glm::vec3 scale);

	glm::vec3& GetPosition();
	glm::vec3& GetRotation();
	glm::vec3& GetScale();


	std::string& GetType();
	std::string& GetName();
	unsigned int GetId();

	glm::mat4 GetModelMatrix();
	void RecalculateModelMatrix();

private:
	std::vector<Mesh*> m_Meshes;
	AnimatedModel* m_AnimatedModel;
	std::vector<Texture*> m_Textures;
	Material* m_Material;

	glm::vec3 m_Position;
	glm::vec3 m_Rotation;
	glm::vec3 m_Scaling;	

	std::string m_Type;
	std::string m_Name;
	unsigned int Id;

	glm::mat4 ModelMatrix;
};

#endif