#include "GUILayer.h"

#pragma warning(disable : 4996) 
#include <iomanip>

GUILayer::GUILayer()
{

}

GUILayer::~GUILayer()
{
}

void GUILayer::Attach()
{

	m_Window = static_cast<GLFWwindow*>(Game::GetWindow().GetNativeWindow());
	m_stateMachie = new StateMachine();
	m_EditorScene = std::make_shared<EditorScene>();
	m_stateMachie->Add(m_EditorScene);
	m_stateMachie->SwitchToScene(0);
	m_SceneHierarchy = new SceneHierarchy();
	m_SceneHierarchyCounter = 0;

	m_SceneHierarchy->PushObject(m_SceneHierarchyCounter,"Main Camera");
	m_SceneHierarchyCounter++;
	
	m_Console = new GuiConsole();
	m_ObjectAdditor = new ObjectAdditor();

	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO(); (void)io;

	ImGui_ImplGlfw_InitForOpenGL(m_Window, true);
	ImGui_ImplOpenGL3_Init("#version 450");

	ImGui::StyleColorsDark();


}

void GUILayer::Detach()
{
}

void GUILayer::OnEvent()
{
}

void GUILayer::Update(float DeltaTime)
{
	m_stateMachie->Update(DeltaTime);
	m_SceneHierarchy->Update(DeltaTime);
	m_Console->Update(DeltaTime);
	m_ObjectAdditor->Update(DeltaTime);
}

void GUILayer::Render()
{
	
	ImGui_ImplOpenGL3_NewFrame();
	ImGui_ImplGlfw_NewFrame();
	ImGui::NewFrame();


	bool my_tool_active = true;


	ImGui::Begin("Topbar Default App", &my_tool_active, ImGuiWindowFlags_MenuBar);
	if (ImGui::BeginMenuBar())
	{
		if (ImGui::BeginMenu("File"))
		{
			if (ImGui::MenuItem("Open..", "Ctrl+O")) { /* Do stuff */ }
			if (ImGui::MenuItem("Save", "Ctrl+S")) { /* Do stuff */ }
			if (ImGui::MenuItem("Close", "Ctrl+W")) { my_tool_active = false; }
			ImGui::EndMenu();
		}

		if (ImGui::MenuItem("Save"))
		{
		
		}

		ImGui::EndMenuBar();
	}


	double xpos, ypos;
	glfwGetCursorPos(Game::GetWindow().GetNativeWindow(), &xpos, &ypos);


	/*ImGui::Begin("Control panel");
	if (ImGui::Button("Model")) {

		std::vector<Vertex> rawModel = OBJLoader::loadObjModel("resources/vanilla/obj/plane.obj");
		Mesh* mesh = new Mesh(rawModel.data(), rawModel.size(), NULL, 0);



		EditorSceneObject* object = new EditorSceneObject(0, "test"+std::to_string(0), "static");

		object->AddMesh(mesh);

		object->SetPosition(glm::vec3(0.f, 0.0f, 0.f));
		object->SetScale(glm::vec3(10.f, 1.0f, 10.f));


		m_EditorScene->AddObject(object);
	//	count++;

		m_SceneHierarchy->PushObject(m_SceneHierarchyCounter,object->GetName());
		m_SceneHierarchyCounter++;

		//ImGui::OpenPopup("Create game object");
	}

	if (ImGui::Button("Plane")) {
		CreateDefaultObject(DefaultObjects::Plane,"Plane",m_SceneHierarchyCounter);

		std::stringstream transTime;

		time_t chrono_time = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());

		transTime << std::put_time(localtime(&chrono_time), "%F %T");

		std::string time = transTime.str();

		m_Console->PushMessage("A new object has been added to the scene (Cube).",time, MessageStatus::Error);
	}

	if (ImGui::Button("Sphere")) {
		CreateDefaultObject(DefaultObjects::Sphere, "Sphere", m_SceneHierarchyCounter);
	}

	if (ImGui::Button("Cylinder")) {
		CreateDefaultObject(DefaultObjects::Cylinder, "Cylinder", m_SceneHierarchyCounter);
	}

	if (ImGui::Button("Cube")) {
		CreateDefaultObject(DefaultObjects::Cube, "Cube", m_SceneHierarchyCounter);
		std::vector<Vertex> rawModel = OBJLoader::loadObjModel("resources/vanilla/obj/cube.obj");
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

		diffuse->unbind();

	}

	if (ImGui::Button("Monkey")) {
		CreateDefaultObject(DefaultObjects::Monkey, "Monkey", m_SceneHierarchyCounter);
	}

	*/
	m_ObjectAdditor->Render(*m_EditorScene, m_SceneHierarchy, m_Console);

	if (ImGui::BeginPopupModal("Create game object"))
	{
		//ImGui::Text("test");
		//char objectname[60] = { 0 };
		//char objecttype[60] = { 0 };
	//	ImGui::InputText("object name", objectname, IM_ARRAYSIZE(objectname));
	//	ImGui::InputText("object type", objecttype, IM_ARRAYSIZE(objecttype));

		ImGui::EndPopup();
	}
	//ImGui::End();

	m_SceneHierarchy->Render();

	ImGui::Begin("Resources");
	ImGui::End();

	m_Console->Render();

	ImGui::Begin("Object settings");
	ImGui::End();




	m_EditorScene->ImGuiScene();
	m_stateMachie->Render();

	ImGui::End();
	ImGui::Render();
	int m_width = 1440, m_height = 900;
	glfwGetFramebufferSize(m_Window, &m_width, &m_height);
	ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
	
	
}

void GUILayer::CreateDefaultObject(DefaultObjects index,std::string name,unsigned int id)
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

	EditorSceneObject* object = new EditorSceneObject(id, name + std::to_string(m_SceneHierarchyCounter), "static");

	object->AddMesh(mesh);

	object->SetPosition(glm::vec3(0.f, 0.0f, 0.f));

	m_EditorScene->AddObject(object);

	m_SceneHierarchy->PushObject(m_SceneHierarchyCounter, object->GetName());
	m_SceneHierarchyCounter++;
}
