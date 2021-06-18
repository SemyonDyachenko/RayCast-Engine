#ifndef SCENE_HIERARCHY_H
#define SCENE_HIERARCHY_H


#include <iostream>
#include <vector>
#include <string>
#include <map>


#include "../../Vendor/imgui/imgui.h"
#include "../../Vendor/imgui/imgui_impl_glfw.h"
#include "../../Vendor/imgui/imgui_impl_opengl3.h"
#include "../EditorScene.h"

class SceneHierarchy  {
public:
	SceneHierarchy(EditorScene & scene);

	void PushObject(unsigned int id,std::string name,EditorScene&scene);
	void DeleteObject(unsigned int id, EditorScene& scene);

	std::map<unsigned int, std::string> GetObjects();

	unsigned int GetObjectsCount();

	unsigned int GetSelectedObject();
	void SetSelectedObject(unsigned int id);

	void DeleteNodeById(unsigned int id);

	bool HasSelectedEntity() { 
		return HasSelected;
	}
	Entity& GetSelectedEntity() { return m_SelectedEntity; }
	void SetSelectedEntity(Entity entity) {}

	void Update(float DeltaTime);

	void Render(EditorScene& editorScene);
private:
	void EntityNode(std::unique_ptr<Entity> entity);
		
private:
	std::map<unsigned int,std::string> objects;
	unsigned int m_CountObject;
	unsigned int m_SelectedObject = -1;

	EditorScene* m_Scene;
	Entity m_SelectedEntity;
	bool HasSelected = false;

};


#endif