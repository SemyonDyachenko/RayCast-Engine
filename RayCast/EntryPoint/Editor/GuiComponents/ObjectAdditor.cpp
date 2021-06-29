#include "../../../stdafx.h"
#include "ObjectAdditor.h"


#pragma warning(disable : 4996) 
#include <iomanip>

ObjectAdditor::ObjectAdditor()
{
	m_ObjectsCount = 0;
}

void ObjectAdditor::Update(float DeltaTime)
{
}

bool& ObjectAdditor::OnPopupEvent()
{
	return m_OnPopup;
}

Mesh* ObjectAdditor::AddMesh(DefaultObjects object)
{
	std::string path;

	switch (object)
	{
	case DefaultObjects::Plane:
		path = "resources/vanilla/obj/plane.obj";
		break;
	case DefaultObjects::Sphere:
		path = "resources/vanilla/obj/sphere.obj";
		break;
	case DefaultObjects::Cylinder:
		path = "resources/vanilla/obj/cylinder.obj";
		break;
	case DefaultObjects::Cube:
		path = "resources/vanilla/obj/cube.obj";
		break;
	case DefaultObjects::Monkey:
		path = "resources/vanilla/obj/monkey.obj";
		break;

	default:
		break;
	}

	std::vector<Vertex> rawModel = OBJLoader::loadObjModel(path);
	Mesh* mesh = new Mesh(rawModel.data(), rawModel.size(), NULL, 0,path);

	return mesh;
}

void ObjectAdditor::AddEntity(DefaultObjects object,std::string name,EditorScene & target,GuiConsole& console)
{
	auto& entity = target.CreateEntity(target.GetEntitiesCount(), name);
	glm::vec3 defaultColor = { 0.8,0.8,0.8 };
	entity.AddComponent<MeshComponent>(*AddMesh(object), defaultColor);
	console.PushMessage("A new object has been added to the scene ("+name+").", CalculateTime(), MessageStatus::Default);
	target.RecalculateEntitiesCount();
}

void ObjectAdditor::AddEntity(std::string meshPath, std::string name, EditorScene& target, GuiConsole& console)
{
	auto& entity = target.CreateEntity(target.GetEntitiesCount(), name);
	std::vector<Vertex> rawModel = OBJLoader::loadObjModel(meshPath);
	Mesh* mesh = new Mesh(rawModel.data(), rawModel.size(), NULL, 0);	glm::vec3 defaultColor = { 0.8,0.8,0.8 };
	entity.AddComponent<MeshComponent>(*mesh, defaultColor);
	console.PushMessage("A new object has been added to the scene (" + name + ").", CalculateTime(), MessageStatus::Default);
	target.RecalculateEntitiesCount();
}


void ObjectAdditor::Render(EditorScene& editorScene,SceneHierarchy* sceneHierarchy,GuiConsole* console)
{
	ImGui::Begin("Object Creator");

	if (ImGui::Button("Model")) {
		ImGui::OpenPopup("New Object");
		m_OnPopup = true;
	}

	ImGui::End();
}

Mesh* ObjectAdditor::CreateDefaultEntity(DefaultObjects index, std::string name, unsigned int id)
{
	std::string path;

	switch (index)
	{
	case DefaultObjects::Plane:
		path = "resources/vanilla/obj/plane.obj";
		break;
	case DefaultObjects::Sphere:
		path = "resources/vanilla/obj/sphere.obj";
		break;
	case DefaultObjects::Cylinder:
		path = "resources/vanilla/obj/cylinder.obj";
		break;
	case DefaultObjects::Cube:
		path = "resources/vanilla/obj/cube.obj";
		break;
	case DefaultObjects::Monkey:
		path = "resources/vanilla/obj/monkey.obj";
		break;

	default:
		break;
	}

	std::vector<Vertex> rawModel = OBJLoader::loadObjModel(path);
	Mesh* mesh = new Mesh(rawModel.data(), rawModel.size(), NULL, 0);

	return mesh;
}

std::string ObjectAdditor::CalculateTime()
{
	std::stringstream transTime;

	time_t chrono_time = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());

	transTime << std::put_time(localtime(&chrono_time), "%F %T");

	std::string time = transTime.str();

	return time;
}

