#ifndef SCENE_HIERARCHY_H
#define SCENE_HIERARCHY_H


#include <iostream>
#include <vector>
#include <string>
#include <map>
#include "../../Vendor/imgui/imgui.h"
#include "../../Vendor/imgui/imgui_impl_glfw.h"
#include "../../Vendor/imgui/imgui_impl_opengl3.h"

class SceneHierarchy  {
public:
	SceneHierarchy();

	void PushObject(unsigned int id,std::string name);
	void DeleteObject(unsigned int id);

	std::map<unsigned int, std::string> GetObjects();

	unsigned int GetObjectsCount();

	void Update(float DeltaTime);

	void Render();

private:
	std::map<unsigned int,std::string> objects;
	unsigned int m_CountObject;
};


#endif