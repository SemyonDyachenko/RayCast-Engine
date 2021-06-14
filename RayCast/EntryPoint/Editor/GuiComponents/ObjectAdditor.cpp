#include "ObjectAdditor.h"


#pragma warning(disable : 4996) 
#include <iomanip>

ObjectAdditor::ObjectAdditor()
{
}

void ObjectAdditor::Update(float DeltaTime)
{
}

void ObjectAdditor::Render(EditorScene& editorScene,SceneHierarchy* sceneHierarchy,GuiConsole* console)
{
	ImGui::Begin("Object Creator");

	if (ImGui::Button("Model")) {

		std::vector<Vertex> rawModel = OBJLoader::loadObjModel("resources/vanilla/obj/plane.obj");
		Mesh* mesh = new Mesh(rawModel.data(), rawModel.size(), NULL, 0);



		EditorSceneObject* object = new EditorSceneObject(0, "test" + std::to_string(0), "static");

		object->AddMesh(mesh);

		object->SetPosition(glm::vec3(0.f, 0.0f, 0.f));
		object->SetScale(glm::vec3(10.f, 1.0f, 10.f));


		editorScene.AddObject(object);
		//	count++;

		sceneHierarchy->PushObject(sceneHierarchy->GetObjectsCount(), object->GetName());

		//ImGui::OpenPopup("Create game object");
	}

	if (ImGui::Button("Plane")) {
		editorScene.AddObject(CreateDefaultObject(DefaultObjects::Plane, "Plane", sceneHierarchy->GetObjectsCount()));
		sceneHierarchy->PushObject(sceneHierarchy->GetObjectsCount(), "Plane"+ std::to_string(sceneHierarchy->GetObjectsCount()));
		console->PushMessage("A new object has been added to the scene (Plane).", CalculateTime(), MessageStatus::Default);

	}

	if (ImGui::Button("Sphere")) {
		editorScene.AddObject(CreateDefaultObject(DefaultObjects::Sphere, "Sphere", sceneHierarchy->GetObjectsCount()));
		console->PushMessage("A new object has been added to the scene (Sphere).", CalculateTime(), MessageStatus::Default);
		sceneHierarchy->PushObject(sceneHierarchy->GetObjectsCount(), "Sphere" + std::to_string(sceneHierarchy->GetObjectsCount()));
	}

	if (ImGui::Button("Cylinder")) {
		editorScene.AddObject(CreateDefaultObject(DefaultObjects::Cylinder, "Cylinder", sceneHierarchy->GetObjectsCount()));
		console->PushMessage("A new object has been added to the scene (Cylinder).", CalculateTime(), MessageStatus::Default);
		sceneHierarchy->PushObject(sceneHierarchy->GetObjectsCount(), "Cylinder" + std::to_string(sceneHierarchy->GetObjectsCount()));
	}

	if (ImGui::Button("Cube")) {
		editorScene.AddObject(CreateDefaultObject(DefaultObjects::Cube, "Cube", sceneHierarchy->GetObjectsCount()));
		console->PushMessage("A new object has been added to the scene (Cube).", CalculateTime(), MessageStatus::Default);
		sceneHierarchy->PushObject(sceneHierarchy->GetObjectsCount(), "Cube" + std::to_string(sceneHierarchy->GetObjectsCount()));
		/*std::vector<Vertex> rawModel = OBJLoader::loadObjModel("resources/vanilla/obj/cube.obj");
		Mesh* mesh = new Mesh(rawModel.data(), rawModel.size(), NULL, 0);
		Texture* diffuse = new Texture("resources/images/textures/grass.jpg",GL_TEXTURE_2D);
		Texture* specular = new Texture("resources/images/materials/stone.jpg",GL_TEXTURE_2D);

		diffuse->bind(diffuse->GetId());
		specular->bind(specular->GetId());

		Material* material = new Material(glm::vec3(0.1f), glm::vec3(1.f, 0.f, 0.5f), glm::vec3(1.f),
			diffuse->GetId(), specular->GetId());

		EditorSceneObject* object = new EditorSceneObject(count, "test" + std::to_string(count), "static");

		object->AddMaterial(material);
		object->AddMesh(mesh);


		object->SetPosition(glm::vec3(0.f, 0.0f, 0.f));

		m_EditorScene->AddObject(object);
		count++;

		m_SceneHierarchy->PushObject(m_SceneHierarchyCounter, object->GetName());
		m_SceneHierarchyCounter++;

		diffuse->unbind();*/

	}

	if (ImGui::Button("Monkey")) {
		editorScene.AddObject(CreateDefaultObject(DefaultObjects::Monkey, "Monkey", sceneHierarchy->GetObjectsCount()));
		sceneHierarchy->PushObject(sceneHierarchy->GetObjectsCount(), "Monkey" +std::to_string(sceneHierarchy->GetObjectsCount()));
		console->PushMessage("A new object has been added to the scene (Monkey).", CalculateTime(), MessageStatus::Default);
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

std::string ObjectAdditor::CalculateTime()
{
	std::stringstream transTime;

	time_t chrono_time = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());

	transTime << std::put_time(localtime(&chrono_time), "%F %T");

	std::string time = transTime.str();

	return time;
}
