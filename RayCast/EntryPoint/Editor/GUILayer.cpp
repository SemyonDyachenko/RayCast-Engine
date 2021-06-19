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

	m_ObjectProperties = new ObjectProperties(*m_SceneHierarchy);

	m_ContentBrowser = new ContentBrowserPanel();

	m_SceneSerializer = new SceneSerializer(*m_EditorScene);

	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO();
	io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;

	ImGui::StyleColorsDark();
	SetImGuiTheme();

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
	const glm::vec2& mouse{ImGui::GetMousePos().x,ImGui::GetMousePos().y};
	glm::vec2 delta = (mouse - m_InitialMousePos);
	m_InitialMousePos = mouse;



	if (ImGui::IsMouseDown(ImGuiMouseButton_Right)) {
		m_EditorScene->UpdateMainCamera(DeltaTime);
		m_EditorScene->GetMainCamera().MouseRotate(delta);
	}

	if (ImGui::IsKeyDown(ImGui::GetKeyIndex(ImGuiKey_V))) {
		m_EditorScene->GetMainCamera().MousePan(delta);
	}


	m_SceneHierarchy->Update(DeltaTime);
	m_Console->Update(DeltaTime);
	m_ObjectAdditor->Update(DeltaTime);
	m_SceneProps->Update(DeltaTime);
	m_ObjectProperties->OnUpdate(DeltaTime);

	ImGuiIO& io = ImGui::GetIO();
	m_EditorScene->GetMainCamera().Zoom(io.MouseWheel*4.f);


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
			if (ImGui::MenuItem("Open..", "Ctrl+O")) 
			{
				std::string path = FileDialogs::OpenFile("RayCast Scene (*.obj)\0*.obj\0");


			}
			if (ImGui::MenuItem("Save", "Ctrl+S"))
			{
				std::string file = FileDialogs::SaveFile("RayCast Scene (*.raycast)\0*.raycast\0");
				m_SceneSerializer->Serialize(file);
			}
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

		if (ImGui::BeginMenu("Game Object")) {
			if (ImGui::MenuItem("Cube")) { }
			if (ImGui::MenuItem("Cylinder")) { }
			if (ImGui::MenuItem("Sphere")) { }
			if (ImGui::MenuItem("Plane")) { }
			if (ImGui::MenuItem("Monkey")) { }

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
	if (ImGui::IsKeyPressed(ImGui::GetKeyIndex(ImGuiKey_Insert))) {
		if (_drawGrid)
			_drawGrid = false;
		else
			_drawGrid = true;
	}


	if (m_SceneHierarchy->HasSelectedEntity() && m_SceneProps->GetGizmosType() != -1) {	
		

		const glm::mat4& projection = m_EditorScene->GetMainCamera().GetProjectionMatrix();
		glm::mat4 cameraView = m_EditorScene->GetMainCamera().GetViewMatrix();

		auto& ts = m_SceneHierarchy->GetSelectedEntity().GetComponent<TransformComponent>();

		glm::mat4 modelmatrix = ts.GetTrasnform();

		ImGuizmo::Manipulate(glm::value_ptr(cameraView), glm::value_ptr(projection), (ImGuizmo::OPERATION)m_SceneProps->GetGizmosType(), ImGuizmo::LOCAL, glm::value_ptr(modelmatrix));




		if (ImGuizmo::IsUsing())
		{
			glm::vec3 position, rotation, scale;

			DecomposeModelMatrix(modelmatrix, position, rotation, scale);


			glm::vec3 dtRotation = rotation - ts.Rotation;
			ts.Position = position;
			ts.Rotation += dtRotation;
			ts.Scale = scale;

		}
	}
	


	m_ObjectAdditor->Render(*m_EditorScene, m_SceneHierarchy, m_Console);

	m_SceneHierarchy->Render(*m_EditorScene);

	m_ContentBrowser->OnRender();


	m_Console->Render();

	m_ObjectProperties->OnRender(*m_EditorScene);


	SceneSerializer serializer(*m_EditorScene);
	serializer.Serialize("resources/scenes/example.raycast");

	
	m_EditorScene->ImGuiScene();
	m_SceneProps->Render();
	m_stateMachie->Render();



	ImGui::End();
	ImGui::Render();
	ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

}

void GUILayer::SetImGuiTheme()
{
	ImGuiIO& io = ImGui::GetIO();
	io.Fonts->AddFontFromFileTTF("resources/fonts/Ruda-Bold.ttf", 15.0f);
	ImGui::GetStyle().FrameRounding = 4.0f;
	ImGui::GetStyle().GrabRounding = 4.0f;

	ImGuiStyle& style = ImGui::GetStyle();
	style.Colors[ImGuiCol_Text] = ImVec4(1.00f, 1.00f, 1.00f, 1.00f);
	style.Colors[ImGuiCol_TextDisabled] = ImVec4(0.50f, 0.50f, 0.50f, 1.00f);
	style.Colors[ImGuiCol_WindowBg] = ImVec4(0.13f, 0.14f, 0.15f, 1.00f);
	style.Colors[ImGuiCol_ChildBg] = ImVec4(0.13f, 0.14f, 0.15f, 1.00f);
	style.Colors[ImGuiCol_PopupBg] = ImVec4(0.13f, 0.14f, 0.15f, 1.00f);
	style.Colors[ImGuiCol_Border] = ImVec4(0.43f, 0.43f, 0.50f, 0.50f);
	style.Colors[ImGuiCol_BorderShadow] = ImVec4(0.00f, 0.00f, 0.00f, 0.00f);
	style.Colors[ImGuiCol_FrameBg] = ImVec4(0.25f, 0.25f, 0.25f, 1.00f);
	style.Colors[ImGuiCol_FrameBgHovered] = ImVec4(0.38f, 0.38f, 0.38f, 1.00f);
	style.Colors[ImGuiCol_FrameBgActive] = ImVec4(0.67f, 0.67f, 0.67f, 0.39f);
	style.Colors[ImGuiCol_TitleBg] = ImVec4(0.08f, 0.08f, 0.09f, 1.00f);
	style.Colors[ImGuiCol_TitleBgActive] = ImVec4(0.08f, 0.08f, 0.09f, 1.00f);
	style.Colors[ImGuiCol_TitleBgCollapsed] = ImVec4(0.00f, 0.00f, 0.00f, 0.51f);
	style.Colors[ImGuiCol_MenuBarBg] = ImVec4(0.14f, 0.14f, 0.14f, 1.00f);
	style.Colors[ImGuiCol_ScrollbarBg] = ImVec4(0.02f, 0.02f, 0.02f, 0.53f);
	style.Colors[ImGuiCol_ScrollbarGrab] = ImVec4(0.31f, 0.31f, 0.31f, 1.00f);
	style.Colors[ImGuiCol_ScrollbarGrabHovered] = ImVec4(0.41f, 0.41f, 0.41f, 1.00f);
	style.Colors[ImGuiCol_ScrollbarGrabActive] = ImVec4(0.51f, 0.51f, 0.51f, 1.00f);
	style.Colors[ImGuiCol_CheckMark] = ImVec4(0.11f, 0.64f, 0.92f, 1.00f);
	style.Colors[ImGuiCol_SliderGrab] = ImVec4(0.11f, 0.64f, 0.92f, 1.00f);
	style.Colors[ImGuiCol_SliderGrabActive] = ImVec4(0.08f, 0.50f, 0.72f, 1.00f);
	style.Colors[ImGuiCol_Button] = ImVec4(0.25f, 0.25f, 0.25f, 1.00f);
	style.Colors[ImGuiCol_ButtonHovered] = ImVec4(0.38f, 0.38f, 0.38f, 1.00f);
	style.Colors[ImGuiCol_ButtonActive] = ImVec4(0.67f, 0.67f, 0.67f, 0.39f);
	style.Colors[ImGuiCol_Header] = ImVec4(0.22f, 0.22f, 0.22f, 1.00f);
	style.Colors[ImGuiCol_HeaderHovered] = ImVec4(0.25f, 0.25f, 0.25f, 1.00f);
	style.Colors[ImGuiCol_HeaderActive] = ImVec4(0.67f, 0.67f, 0.67f, 0.39f);
	style.Colors[ImGuiCol_Separator] = style.Colors[ImGuiCol_Border];
	style.Colors[ImGuiCol_SeparatorHovered] = ImVec4(0.41f, 0.42f, 0.44f, 1.00f);
	style.Colors[ImGuiCol_SeparatorActive] = ImVec4(0.26f, 0.59f, 0.98f, 0.95f);
	style.Colors[ImGuiCol_ResizeGrip] = ImVec4(0.00f, 0.00f, 0.00f, 0.00f);
	style.Colors[ImGuiCol_ResizeGripHovered] = ImVec4(0.29f, 0.30f, 0.31f, 0.67f);
	style.Colors[ImGuiCol_ResizeGripActive] = ImVec4(0.26f, 0.59f, 0.98f, 0.95f);
	style.Colors[ImGuiCol_Tab] = ImVec4(0.08f, 0.08f, 0.09f, 0.83f);
	style.Colors[ImGuiCol_TabHovered] = ImVec4(0.33f, 0.34f, 0.36f, 0.83f);
	style.Colors[ImGuiCol_TabActive] = ImVec4(0.23f, 0.23f, 0.24f, 1.00f);
	style.Colors[ImGuiCol_TabUnfocused] = ImVec4(0.08f, 0.08f, 0.09f, 1.00f);
	style.Colors[ImGuiCol_TabUnfocusedActive] = ImVec4(0.13f, 0.14f, 0.15f, 1.00f);
	//style.Colors[ImGuiCol_DockingPreview] = ImVec4(0.26f, 0.59f, 0.98f, 0.70f);
	//style.Colors[ImGuiCol_DockingEmptyBg] = ImVec4(0.20f, 0.20f, 0.20f, 1.00f);
	style.Colors[ImGuiCol_PlotLines] = ImVec4(0.61f, 0.61f, 0.61f, 1.00f);
	style.Colors[ImGuiCol_PlotLinesHovered] = ImVec4(1.00f, 0.43f, 0.35f, 1.00f);
	style.Colors[ImGuiCol_PlotHistogram] = ImVec4(0.90f, 0.70f, 0.00f, 1.00f);
	style.Colors[ImGuiCol_PlotHistogramHovered] = ImVec4(1.00f, 0.60f, 0.00f, 1.00f);
	style.Colors[ImGuiCol_TextSelectedBg] = ImVec4(0.26f, 0.59f, 0.98f, 0.35f);
	style.Colors[ImGuiCol_DragDropTarget] = ImVec4(0.11f, 0.64f, 0.92f, 1.00f);
	style.Colors[ImGuiCol_NavHighlight] = ImVec4(0.26f, 0.59f, 0.98f, 1.00f);
	style.Colors[ImGuiCol_NavWindowingHighlight] = ImVec4(1.00f, 1.00f, 1.00f, 0.70f);
	style.Colors[ImGuiCol_NavWindowingDimBg] = ImVec4(0.80f, 0.80f, 0.80f, 0.20f);
	style.Colors[ImGuiCol_ModalWindowDimBg] = ImVec4(0.80f, 0.80f, 0.80f, 0.35f);
	style.GrabRounding = style.FrameRounding = 2.3f;
}
	
