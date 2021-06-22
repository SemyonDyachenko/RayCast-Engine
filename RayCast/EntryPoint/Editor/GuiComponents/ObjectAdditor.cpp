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
	Mesh* mesh = new Mesh(rawModel.data(), rawModel.size(), NULL, 0);

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

void ObjectAdditor::AddObjectToScene(int id,DefaultObjects index, std::string name, EditorScene& editorScene, SceneHierarchy* sceneHierarchy, GuiConsole* console)
{
	console->PushMessage("A new object has been added to the scene (" + name+").", CalculateTime(), MessageStatus::Default);
	editorScene.AddObject(CreateDefaultObject(index, name, id));
	sceneHierarchy->PushObject(id, name + std::to_string(id), editorScene);
	sceneHierarchy->SetSelectedObject(id);
}

void ObjectAdditor::Render(EditorScene& editorScene,SceneHierarchy* sceneHierarchy,GuiConsole* console)
{
	ImGui::Begin("Object Creator");

	if (ImGui::Button("Model")) {
		ImGui::OpenPopup("New Object");
		m_OnPopup = true;
	}

	if (ImGui::BeginPopupModal("New Object"))
	{

		ImGui::InputText("Name", m_NewObjectNameBuffer,IM_ARRAYSIZE(m_NewObjectNameBuffer));
		ImGui::InputText("Type", m_NewObjectTypeBuffer, IM_ARRAYSIZE(m_NewObjectTypeBuffer));
		ImGui::InputText("File name", m_NewObjectModelPath, IM_ARRAYSIZE(m_NewObjectModelPath));

		ImGui::InputFloat("X", &m_NewObjectPosition.x, 1.f);
	
		ImGui::InputFloat("Y", &m_NewObjectPosition.y, 1.f);
	
		ImGui::InputFloat("Z", &m_NewObjectPosition.z, 1.f);

		if (ImGui::Button("Create")) {

			std::string filename(m_NewObjectModelPath);
			std::string name(m_NewObjectNameBuffer);
			std::string type(m_NewObjectTypeBuffer);

			std::vector<Vertex> rawModel = OBJLoader::loadObjModel("resources/models/Assets/"+filename);
			Mesh* mesh = new Mesh(rawModel.data(), rawModel.size(), NULL, 0);

			EditorSceneObject* object = new EditorSceneObject(sceneHierarchy->GetObjectsCount(), name, type);
			object->AddMesh(mesh);

			object->SetPosition(m_NewObjectPosition);

			console->PushMessage("A new object has been added to the scene ("+name+").", CalculateTime(), MessageStatus::Default);
			editorScene.AddObject(object);
			sceneHierarchy->PushObject(m_ObjectsCount, name, editorScene);
			m_ObjectsCount++;

			m_NewObjectPosition = { 0.0f,0.0f,0.0f };
			memset(m_NewObjectNameBuffer, 0, IM_ARRAYSIZE(m_NewObjectNameBuffer) * sizeof(char));
			memset(m_NewObjectTypeBuffer, 0, IM_ARRAYSIZE(m_NewObjectTypeBuffer) * sizeof(char));
			memset(m_NewObjectModelPath, 0, IM_ARRAYSIZE(m_NewObjectModelPath) * sizeof(char));
			ImGui::CloseCurrentPopup();
			m_OnPopup = false;

		}
		ImGui::SameLine();

		if (ImGui::Button("Cancel")) {
			ImGui::CloseCurrentPopup();
			m_OnPopup = false;
		}

		ImGui::EndPopup();
	}


	ImGui::SameLine();

	if (ImGui::Button("Plane")) {
		//AddObjectToScene(m_ObjectsCount, DefaultObjects::Plane, "Plane", editorScene, sceneHierarchy, console);
		
		
	
		auto& entity = editorScene.CreateEntity(editorScene.GetEntitiesCount(), "Plane");
		editorScene.RecalculateEntitiesCount();
		glm::vec3 defaultColor = { 1.0f,1.0f,1.0f };

		std::vector<Vertex> rawModel = OBJLoader::loadObjModel("resources/vanilla/obj/cube.obj");
		Mesh* mesh = new Mesh(rawModel.data(), rawModel.size(), NULL, 0);

		entity.AddComponent<MeshComponent>(*mesh,defaultColor);

		console->PushMessage("A new object has been added to the scene (" + std::to_string(entity.GetId()) +").", CalculateTime(), MessageStatus::Default);

	
		//sceneHierarchy->PushObject(entity.GetId(), "Plane" + std::to_string(entity.GetId()),editorScene);
		//sceneHierarchy->SetSelectedObject(entity.GetId());
	}
	ImGui::SameLine();

	 if (ImGui::Button("Sphere")) {
		 AddObjectToScene(m_ObjectsCount, DefaultObjects::Sphere, "Sphere", editorScene, sceneHierarchy, console);

	}

	 if (ImGui::Button("Cylinder")) {
		 AddObjectToScene(m_ObjectsCount, DefaultObjects::Cylinder, "Cylinder", editorScene, sceneHierarchy, console);
	}
	 ImGui::SameLine();

	 if (ImGui::Button("Cube")) {
		 AddObjectToScene(m_ObjectsCount, DefaultObjects::Cube, "Cube", editorScene, sceneHierarchy, console);

	 }
	 ImGui::SameLine();

	 if (ImGui::Button("Monkey")) {
		 AddObjectToScene(m_ObjectsCount, DefaultObjects::Monkey, "Monkey", editorScene, sceneHierarchy, console);
	}

	ImGui::End();
}

EditorSceneObject* ObjectAdditor::CreateDefaultObject(DefaultObjects index, std::string name, unsigned int id)
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

	EditorSceneObject* object = new EditorSceneObject(id, name + std::to_string(id), "static");
	object->AddMesh(mesh);

	object->SetPosition(glm::vec3(0.f, 0.0f, 0.f));

	return object;

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

