#include "GUILayer.h"



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
}

void GUILayer::Render()
{
	
	ImGui_ImplOpenGL3_NewFrame();
	ImGui_ImplGlfw_NewFrame();
	ImGui::NewFrame();

	m_stateMachie->Render();

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
	

	ImGui::Begin("Control panel");
	if (ImGui::Button("New game object")) {
		ImGui::OpenPopup("Create game object");
	}

	if (ImGui::BeginPopupModal("Create game object"))
	{
		//ImGui::Text("test");
		//char objectname[60] = { 0 };
		//char objecttype[60] = { 0 };
	//	ImGui::InputText("object name", objectname, IM_ARRAYSIZE(objectname));
	//	ImGui::InputText("object type", objecttype, IM_ARRAYSIZE(objecttype));

		ImGui::EndPopup();
	}
	ImGui::End();

	ImGui::Begin("Scene Hierarchy");
	ImGui::End();

	ImGui::Begin("Resources");
	ImGui::End();


	m_EditorScene->ImGuiScene();


	ImGui::End();
	ImGui::Render();
	int m_width = 1440, m_height = 900;
	glfwGetFramebufferSize(m_Window, &m_width, &m_height);
	ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
	
	
}
