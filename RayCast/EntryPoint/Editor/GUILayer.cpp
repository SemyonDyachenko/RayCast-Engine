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
	m_SceneHierarchy = new SceneHierarchy(*m_EditorScene);
	m_SceneHierarchyCounter = 0;

	//m_SceneHierarchy->PushObject(m_SceneHierarchyCounter,"Main Camera");
	m_SceneHierarchyCounter++;
	
	m_Console = new GuiConsole();
	m_ObjectAdditor = new ObjectAdditor();

	m_SceneProps = new SceneProps();

	m_SceneProps->SetGizmosType(0);

	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO();
	io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;

	ImGui::StyleColorsDark();

	ImGui_ImplGlfw_InitForOpenGL(m_Window, true);
	ImGui_ImplOpenGL3_Init("#version 450");



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
	if(!m_ObjectAdditor->OnPopupEvent()) {
		m_EditorScene->UpdateMainCamera(DeltaTime);
	}
	m_SceneHierarchy->Update(DeltaTime);
	m_Console->Update(DeltaTime);
	m_ObjectAdditor->Update(DeltaTime);
	m_SceneProps->Update(DeltaTime);

	ImGuiIO& io = ImGui::GetIO();
	m_EditorScene->GetMainCamera().Zoom(io.MouseWheel*2.f);

}

void GUILayer::Render()
{

	ImGui_ImplOpenGL3_NewFrame();
	ImGui_ImplGlfw_NewFrame();
	ImGui::NewFrame();
	ImGuizmo::BeginFrame();

	bool my_tool_active = true;

	ImGuiWindowFlags window_flags = ImGuiWindowFlags_MenuBar;

	ImGuiViewport* viewport = ImGui::GetMainViewport();
	ImGui::SetNextWindowPos(viewport->Pos);
	ImGui::SetNextWindowSize(viewport->Size);
	ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, 1.0f);
	ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, 5.0f);
	ImGui::PushStyleVar(ImGuiStyleVar_FrameBorderSize, 5.0f);
	window_flags |= ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove;
	window_flags |= ImGuiWindowFlags_NoBringToFrontOnFocus | ImGuiWindowFlags_NoNavFocus;
	window_flags |= ImGuiWindowFlags_NoBackground;

	ImGui::PopStyleVar(3);


	ImGui::Begin("Topbar Default App", &my_tool_active, window_flags);

	ImGuizmo::SetOrthographic(false);
	ImGuizmo::SetDrawList();

	if (ImGui::BeginMenuBar())
	{
		if (ImGui::BeginMenu("File"))
		{
			if (ImGui::MenuItem("Open..", "Ctrl+O")) {}
			if (ImGui::MenuItem("Save", "Ctrl+S")) {  }
			if (ImGui::MenuItem("Close", "Ctrl+W")) { my_tool_active = false; exit(true); Game::GetWindow().Close(); }
			ImGui::EndMenu();
		}

		if (ImGui::MenuItem("Save"))
		{
		
		}

		if (ImGui::BeginMenu("Console"))
		{
			if (ImGui::MenuItem("Clear", "Ctrl+J")) { m_Console->Clear(); }
			ImGui::EndMenu();
		}

		if (ImGui::BeginMenu("Window"))
		{
			

			ImGui::EndMenu();
		}


		if (ImGui::BeginMenu("Help"))
		{
		
			ImGui::EndMenu();
		}


		ImGui::EndMenuBar();
	}

	ImGuiIO& io = ImGui::GetIO();
	ImGuizmo::SetRect(0, 0, io.DisplaySize.x, io.DisplaySize.y);

	if (_drawGrid) {
		const float identityMatrix[16] =
		{ 1.f, 0.f, 0.f, 0.f,
			0.f, 1.f, 0.f, 0.f,
			0.f, 0.f, 1.f, 0.f,
			0.f, 0.f, 0.f, 1.f };

		ImGuizmo::DrawGrid(glm::value_ptr(m_EditorScene->GetMainCamera().GetViewMatrix()), glm::value_ptr(m_EditorScene->GetMainCamera().GetProjectionMatrix()), identityMatrix, m_EditorScene->GetMainCamera().GetFov());

	}
	if (glfwGetKey(Game::GetWindow().GetNativeWindow(), GLFW_KEY_F7) == GLFW_PRESS) {
		if (_drawGrid)
			_drawGrid = false;
		else
			_drawGrid = true;
	}


	if (m_SceneHierarchy->GetSelectedObject() != -1 && m_SceneProps->GetGizmosType() != -1) {	
		

		const glm::mat4& projection = m_EditorScene->GetMainCamera().GetProjectionMatrix();
		glm::mat4 cameraView = m_EditorScene->GetMainCamera().GetViewMatrix();


		glm::mat4 modelmatrix = m_EditorScene->GetObjectById(m_SceneHierarchy->GetSelectedObject())->GetModelMatrix();

		ImGuizmo::Manipulate(glm::value_ptr(cameraView), glm::value_ptr(projection), (ImGuizmo::OPERATION)m_SceneProps->GetGizmosType(), ImGuizmo::LOCAL, glm::value_ptr(modelmatrix));




		if (ImGuizmo::IsUsing())
		{
			glm::vec3 position, rotation, scale;

			DecomposeModelMatrix(modelmatrix, position, rotation, scale);


			glm::vec3 dtRotation = rotation - m_EditorScene->GetSelectedObject()->GetRotation();
			m_EditorScene->GetObjectById(m_SceneHierarchy->GetSelectedObject())->SetPosition(position);

			m_EditorScene->GetObjectById(m_SceneHierarchy->GetSelectedObject())->SetRotation(m_EditorScene->GetSelectedObject()->GetRotation() + dtRotation);
			m_EditorScene->GetObjectById(m_SceneHierarchy->GetSelectedObject())->SetScale(scale);

		}
	}



	m_ObjectAdditor->Render(*m_EditorScene, m_SceneHierarchy, m_Console);

	m_SceneHierarchy->Render();

	ImGui::Begin("Resources");
	ImGui::End();


	m_Console->Render();

	ImGui::Begin("Properties");	
	ImGui::End();


	
	m_EditorScene->ImGuiScene();
	m_SceneProps->Render();
	m_stateMachie->Render();



	ImGui::End();
	ImGui::Render();
	ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

}
	
