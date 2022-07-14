#include "GUILayer.h"


GUILayer::GUILayer() 
{
	Game::GetWindow().SetTitle("RayCast Editor - Empty Project");

}

void GUILayer::Attach()
{

	m_Window = static_cast<NATIVE_WINDOW*>(Game::GetWindow().GetNativeWindow());
	m_stateMachine = new StateMachine();
	m_EditorScene = std::make_shared<EditorScene>();
	m_stateMachine->Add(m_EditorScene);
	m_stateMachine->SwitchToScene(0);
	m_SceneHierarchy = new SceneHierarchy(*m_EditorScene);
	m_Console = new GuiConsole();
	m_ObjectCreator = new ObjectAdditor();
	m_SceneProps = new SceneProps();
	m_SceneProps->SetGizmosType(0);
	m_ObjectProperties = new ObjectProperties(*m_SceneHierarchy);
	m_ContentBrowser = new ContentBrowserPanel();
	m_SceneSerializer = new SceneSerializer(*m_EditorScene);
	m_MaterialViewer = new MaterialViewer();
	m_Animator = new AnimatorWindow();
	m_TerrainEditor = new TerrainEditor();
	m_EntityCreator = new EntityCreator();

	m_MouseRay = new MousePicker(m_EditorScene->GetMainCamera(), m_EditorScene->GetMainCamera().GetProjectionMatrix());

	IMGUI_CHECKVERSION();
	
	ImGui::CreateContext();

	ImGuiIO& io = ImGui::GetIO(); (void)io;
	io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;       // Enable Keyboard Controls
	//io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls
	io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;           // Enable Docking
	//io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;  www       // Enable Multi-Viewport / Platform Windows

	ImGui::StyleColorsDark();
	
	ImGuiStyle& style = ImGui::GetStyle();
	if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
	{
		style.WindowRounding = 0.0f;
		style.Colors[ImGuiCol_WindowBg].w = 1.0f;
	}
	SetImGuiTheme();

	ImGui_ImplGlfw_InitForOpenGL(m_Window, true);
	ImGui_ImplOpenGL3_Init("#version 450");

	m_ViewPortWidth = m_EditorScene->GetViewPortBuffer()->GetFrameBufferProps().Width;
	m_ViewPortWidth = m_EditorScene->GetViewPortBuffer()->GetFrameBufferProps().Height;

}

void GUILayer::Detach()
{
	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplGlfw_Shutdown();
	ImGui::DestroyContext();
}

void GUILayer::OnEvent()
{
}

void GUILayer::Update(float DeltaTime)
{
	m_stateMachine->Update(DeltaTime);
	const glm::vec2& mouse{ ImGui::GetMousePos().x,ImGui::GetMousePos().y };
	glm::vec2 delta = (mouse - m_InitialMousePos);
	m_InitialMousePos = mouse;	

	m_SceneHierarchy->Update(DeltaTime);
	m_Console->Update(DeltaTime);
	m_ObjectCreator->Update(DeltaTime);
	m_SceneProps->Update(DeltaTime);
	m_ObjectProperties->OnUpdate(DeltaTime);
	m_MaterialViewer->Update(DeltaTime);
	m_Animator->Update(DeltaTime); 
	m_TerrainEditor->Update(DeltaTime);
	m_MouseRay->Update();



	auto& io = ImGui::GetIO();

	if (Input::IsKeyPressed(GLFW_KEY_ESCAPE))
	{
		m_EditorScene->Pause();
		m_EditorScene->StopSimulatePhyiscs();
	}

	
	if (m_ViewportFocused) {

		

		if (!m_EditorScene->OnStart()) {
			if (ImGui::IsMouseDown(ImGuiMouseButton_Right)) {
				m_EditorScene->UpdateMainCamera(DeltaTime);
				m_EditorScene->GetMainCamera().MouseRotate(delta);
			}

			if (ImGui::IsKeyDown(ImGui::GetKeyIndex(ImGuiKey_V))) {
				m_EditorScene->GetMainCamera().MousePan(delta);
			}

		}
		
		if (!ImGui::IsMouseDown(ImGuiMouseButton_Right) && !ImGui::IsMouseDown(ImGuiMouseButton_Left)) 
		{
			if (Input::IsKeyPressed(INPUT_KEY_Q))
			{
				m_SceneProps->SetGizmosType(0); // select trasnalte object mode
			}
			else if (Input::IsKeyPressed(INPUT_KEY_W))
			{
				m_SceneProps->SetGizmosType(1); // select rotate object mode
			}
			else if (Input::IsKeyPressed(INPUT_KEY_E))
			{
				m_SceneProps->SetGizmosType(2); // select scale object mode
			}

	

		}


		if (ImGui::IsMouseDown(ImGuiMouseButton_Right)) {
			m_EditorScene->GetMainCamera().Zoom(io.MouseWheel * 4.f);
		}


		auto [mx, my] = ImGui::GetMousePos();
		mx -= m_ViewportBounds[0].x;
		my -= m_ViewportBounds[0].y;
		glm::vec2 viewportSize = m_ViewportBounds[1] - m_ViewportBounds[0];
		my = viewportSize.y - my;
		int mouseX = (int)mx;
		int mouseY = (int)my;

	//	std::cout << mouseX << " " << mouseY << "\n";

		if (mouseX >= 0 && mouseY >= 0 && mouseX < (int)viewportSize.x && mouseY < (int)viewportSize.y)
		{
		//	ENGINE_INFO("mouse {x}: ", mouseX);
			//ENGINE_INFO("mouse {y}: ", mouseY);
			int pixelData = m_EditorScene->GetViewPortBuffer()->ReadPixel(1, mouseX, mouseY);
			//m_SceneHierarchy->SetSelectedEntity(pixelData == -1 ? *m_EditorScene->GetEntity(0) : *m_EditorScene->GetEntity(pixelData));
			//ENGINE_INFO("pixel data: ", pixelData);
		}



	}

	
	HandleShortcuts();
}

void GUILayer::Render()
{

	static bool dockspaceOpen = true;
	static bool opt_fullscreen_persistant = true;
	bool opt_fullscreen = opt_fullscreen_persistant;
	static ImGuiDockNodeFlags dockspace_flags = ImGuiDockNodeFlags_None;
	
	ImGui_ImplOpenGL3_NewFrame();
	ImGui_ImplGlfw_NewFrame();
	ImGui::NewFrame();
	ImGuizmo::BeginFrame();

	ImGuiWindowFlags window_flags = ImGuiWindowFlags_MenuBar | ImGuiWindowFlags_NoDocking;
	if (opt_fullscreen)
	{
		ImGuiViewport* viewport = ImGui::GetMainViewport();
		ImGui::SetNextWindowPos(viewport->Pos);
		ImGui::SetNextWindowSize(viewport->Size);
		ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, 0.0f);
		ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, 0.0f);
		window_flags |= ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove;
		window_flags |= ImGuiWindowFlags_NoBringToFrontOnFocus | ImGuiWindowFlags_NoNavFocus;
	}
	if (dockspace_flags & ImGuiDockNodeFlags_PassthruCentralNode)
		window_flags |= ImGuiWindowFlags_NoBackground;
	

	ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0.0f, 0.0f));
	ImGui::Begin("TopBar Default App", &dockspaceOpen, window_flags);
	ImGui::PopStyleVar();

	if (opt_fullscreen)
		ImGui::PopStyleVar(2);

	ImGuiIO& io = ImGui::GetIO();
	ImGuiStyle& style = ImGui::GetStyle();
	// minWinSizeX = style.WindowMinSize.x;
	//style.WindowMinSize.x = 370.0f;
	if (io.ConfigFlags & ImGuiConfigFlags_DockingEnable)
	{
		ImGuiID dockspace_id = ImGui::GetID("MyDockSpace");
		ImGui::DockSpace(dockspace_id, ImVec2(0.0f, 0.0f), dockspace_flags);
	}
	//style.WindowMinSize.x = minWinSizeX;

	//ImGuizmo::SetOrthographic(false);
	//ImGuizmo::SetDrawList();

	if (ImGui::BeginMenuBar())
	{
		if (ImGui::BeginMenu("File"))
		{
			if (ImGui::MenuItem("Open..", "Ctrl+O"))
			{
				std::string path = FileDialogs::OpenFile("RayCast Scene (*.raycast)\0*.raycast\0");
				m_SceneSerializer->Deserialize(path, *m_EditorScene);
				m_SceneFilename = path;

				const std::filesystem::path systemPath = path;
				const std::string title = "RayCast Editor - " + systemPath.filename().string();

				Game::GetWindow().SetTitle(title);

				

				m_EditorScene->RecalculateEntitiesCount();
			}
			if (ImGui::MenuItem("Save", "Ctrl+S"))
			{
				if (m_SceneFilename.length() == 0) {
					std::string path = FileDialogs::SaveFile("RayCast Scene (*.raycast)\0*.raycast\0");
					m_SceneSerializer->Serialize(path);
					m_SceneFilename = path;

					const std::filesystem::path systemPath = path;
					const std::string title = "RayCast Editor - " + systemPath.filename().string();

					Game::GetWindow().SetTitle(title);

					m_EditorScene->RecalculateEntitiesCount();

					
				}
				else
				{
					m_SceneSerializer->Serialize(m_SceneFilename);
					m_EditorScene->RecalculateEntitiesCount();
				}
			}
			if (ImGui::MenuItem("Close", "Ctrl+W")) { dockspaceOpen = false; exit(true); Game::GetWindow().Close(); }
		
			ImGui::EndMenu();
		}

		if (ImGui::BeginMenu("Edit")) {

			if (ImGui::MenuItem("Undo", "Ctrl + Z")) { }
			if (ImGui::MenuItem("Lock Selected", "L")) { }
			if (ImGui::MenuItem("Delete", "Del")) { }
			if (ImGui::MenuItem("Hide Selection", "Ctrl + H")) { }
			if (ImGui::MenuItem("Show Selection", "Ctrl + H")) { }
			if (ImGui::MenuItem("Duplicate Selection", "Ctrl + D")) { }

			ImGui::EndMenu();
		}

		if (ImGui::BeginMenu("View")) {
			if (ImGui::MenuItem("Material")) { m_MaterialViewer->Open(); }
			if (ImGui::MenuItem("Terrain")) { m_TerrainEditor->Open(); }
			if (ImGui::MenuItem("Animator")) { m_Animator->Open(); }
			if (ImGui::MenuItem("Scene Hierarchy")) {}
			if (ImGui::MenuItem("Inspector")) {}
			if (ImGui::MenuItem("Content Browser")) {}

			ImGui::EndMenu();
		}


		if (ImGui::BeginMenu("Tools")) {

			if(ImGui::MenuItem("Settings")) {}

			ImGui::EndMenu();
		}

		/*	if (ImGui::MenuItem("Save"))
			{
				if (m_SceneFilename.length() != 0) {
					m_SceneSerializer->Serialize(m_SceneFilename);
				}
				else {
					std::string path = FileDialogs::SaveFile("RayCast Scene (*.raycast)\0*.raycast\0");
					m_SceneSerializer->Serialize(path);
					m_SceneFilename = path;

					const std::filesystem::path systemPath = path;
					const std::string title = "RayCast Editor - " + systemPath.filename().string();

					Game::GetWindow().SetTitle(title);
					m_EditorScene->RecalculateEntitiesCount();
				}
			}*/


		if (ImGui::BeginMenu("Entity")) {
			if (ImGui::MenuItem("Cube")) {
				m_ObjectCreator->AddEntity(DefaultObjects::Cube, "Cube", *m_EditorScene, *m_Console);
			}
			if (ImGui::MenuItem("Cylinder")) {
				m_ObjectCreator->AddEntity(DefaultObjects::Cylinder, "Cylinder", *m_EditorScene, *m_Console);
			}
			if (ImGui::MenuItem("Sphere")) {
				m_ObjectCreator->AddEntity(DefaultObjects::Sphere, "Sphere", *m_EditorScene, *m_Console);
			}
			if (ImGui::MenuItem("Plane")) {
				m_ObjectCreator->AddEntity(DefaultObjects::Plane, "Plane", *m_EditorScene, *m_Console);
			}
			if (ImGui::MenuItem("Monkey")) {
				m_ObjectCreator->AddEntity(DefaultObjects::Monkey, "Monkey", *m_EditorScene, *m_Console);
			}
			if (ImGui::MenuItem("Terrain")) {
				auto& entity = m_EditorScene->CreateEntity(m_EditorScene->GetEntitiesCount(), "New Landscape");
				m_EditorScene->RecalculateEntitiesCount();
				auto* terrain = new Terrain(static_cast<unsigned int>(128.f),static_cast<unsigned int>(128.f)); // default grid size
				entity.AddComponent<TerrainComponent>(*terrain);
				if (entity.HasComponent<TerrainComponent>()) {
					auto& ter = entity.GetComponent<TerrainComponent>();
					glm::vec3 solidColor = { 0.8f,0.8f,0.8f };
					entity.AddComponent<MeshComponent>(ter.terrain.GetTerrainMesh(), solidColor);
				}
				m_Console->PushMessage("A new object has been added to the scene (Landscape)", m_ObjectCreator->CalculateTime(), MessageStatus::Default);
			}

			if (ImGui::MenuItem("Directional Light")) {
				auto& entity = m_EditorScene->CreateEntity(m_EditorScene->GetEntitiesCount(), "Directional Light");
				auto* light = new Light(m_EditorScene->GetLightCount(), LightMode::DIRECTIONAL_LIGHT, entity.GetComponent<TransformComponent>().Position, glm::vec3(150.f, 150.f, 150.f));
				m_EditorScene->AddLight();
				entity.AddComponent<LightComponent>(*light);
				m_Console->PushMessage("A new object has been added to the scene (Directional Light).", m_ObjectCreator->CalculateTime(), MessageStatus::Default);
				m_EditorScene->RecalculateEntitiesCount();
			}

			if (ImGui::MenuItem("Light Point")) {
				auto& entity = m_EditorScene->CreateEntity(m_EditorScene->GetEntitiesCount(), "Light Point");
				
				auto* light = new Light(m_EditorScene->GetLightCount(), LightMode::POINT_LIGHT, entity.GetComponent<TransformComponent>().Position, glm::vec3(255, 0, 0));
				m_EditorScene->AddLight();
				entity.AddComponent<LightComponent>(*light);
				m_Console->PushMessage("A new object has been added to the scene (Light Point).", m_ObjectCreator->CalculateTime(), MessageStatus::Default);
				m_EditorScene->RecalculateEntitiesCount();
			}

			if (ImGui::MenuItem("Static Mesh")) {
				if (std::string path = FileDialogs::OpenFile("RayCast Scene (*.obj)\0*.obj\0"); path.length() > 0) {
					m_ObjectCreator->AddEntity(path, "New Entity", *m_EditorScene, *m_Console);
					m_EditorScene->RecalculateEntitiesCount();
				}
			}
			


			ImGui::EndMenu();
		}

		if (ImGui::BeginMenu("Scripts"))
		{

			if (ImGui::MenuItem("New Script")) { /* ...  */}
			if (ImGui::MenuItem("Recompile Scripts")) { m_EditorScene->RecompileScripts(); }
			ImGui::EndMenu();
		}

		if (ImGui::BeginMenu("Window"))
		{


			ImGui::EndMenu();
		}


		ImGui::EndMenuBar();
	}

	if (_drawGrid) {
		const float identityMatrix[16] =
		{ 1.f, 0.f, 0.f, 0.f,
			0.f, 1.f, 0.f, 0.f,
			0.f, 0.f, 1.f, 0.f,
			0.f, 0.f, 0.f, 1.f };

		ImGuizmo::DrawGrid(glm::value_ptr(m_EditorScene->GetMainCamera().GetViewMatrix()), glm::value_ptr(m_EditorScene->GetMainCamera().GetProjectionMatrix()), identityMatrix, m_EditorScene->GetMainCamera().GetFov());

	}

	if (ImGui::IsKeyPressed(ImGui::GetKeyIndex(ImGuiKey_Insert))) {
		_drawGrid = _drawGrid ? false : true;
	}

	// render material viewer before viewport
	m_MaterialViewer->Render(*m_SceneHierarchy,*m_Console);
	m_Animator->Render(*m_SceneHierarchy);
	
/*	ImGuiIO& io = ImGui::GetIO();
	ImGuizmo::SetRect(0, 0, io.DisplaySize.x, io.DisplaySize.y);

	if (m_SceneHierarchy->HasSelectedEntity() && m_SceneProps->GetGizmosType() != -1) {


		const glm::mat4& ProjectionMatrix = m_EditorScene->GetMainCamera().GetProjectionMatrix();
		glm::mat4 ViewMatrix = m_EditorScene->GetMainCamera().GetViewMatrix();

		auto& ts = m_SceneHierarchy->GetSelectedEntity().GetComponent<TransformComponent>();

		glm::mat4 ModelMatrix = ts.GetTrasnform();

		ImGuizmo::Manipulate(glm::value_ptr(ViewMatrix), glm::value_ptr(ProjectionMatrix), static_cast<ImGuizmo::OPERATION>(m_SceneProps->GetGizmosType()), ImGuizmo::LOCAL, glm::value_ptr(ModelMatrix));


		if (ImGuizmo::IsUsing())
		{
			glm::vec3 position, rotation, scale;

			DecomposeModelMatrix(ModelMatrix, position, rotation, scale);


			glm::vec3 dtRotation = rotation - ts.Rotation;
			ts.Position = position;
			ts.Rotation += dtRotation;
			ts.Scale = scale;

		}
	}
	*/
	
	auto ptr = true;
	ImGuiWindowFlags viewportFlags = ImGuiWindowFlags_NoScrollbar;
	ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2{ 0.f,0.f });
	
	ImGui::Begin("Viewport",&ptr, viewportFlags);
	
	m_ViewportFocused = ImGui::IsWindowFocused();

	auto windowSize = ImGui::GetWindowSize();
	ImVec2 minBound = ImGui::GetWindowPos();
	
	auto viewportMinRegion = ImGui::GetWindowContentRegionMin();
	auto viewportMaxRegion = ImGui::GetWindowContentRegionMax();
	auto viewportOffset = ImGui::GetWindowPos();

	m_ViewportBounds[0] = { viewportMinRegion.x + viewportOffset.x, viewportMinRegion.y + viewportOffset.y };
	m_ViewportBounds[1] = { viewportMaxRegion.x + viewportOffset.x, viewportMaxRegion.y + viewportOffset.y };

	ImVec2 viewportSize = ImGui::GetContentRegionAvail();


	if (m_ViewPortWidth != viewportSize.x && m_ViewPortHeight != viewportSize.y) {
		m_EditorScene->GetViewPortBuffer()->Resize(static_cast<unsigned int>(viewportSize.x), static_cast<unsigned int>(viewportSize.y));
		m_ViewPortWidth = viewportSize.x;
		m_ViewPortHeight = viewportSize.y;
	}

	m_EditorScene->GetMainCamera().OnResize(m_ViewPortWidth, m_ViewPortHeight);

	ImGui::Image((void*)m_EditorScene->GetViewPortBuffer()->GetTextureID(),
		{ m_ViewPortWidth,m_ViewPortHeight }, { 0,1 }, { 1,0 });

	if (ImGui::BeginDragDropTarget()) {

		const ImGuiPayload* payload = ImGui::AcceptDragDropPayload("contentelement");

		if (payload) {
			const wchar_t*  path = (const wchar_t*)payload->Data;
			const char* cstr = (const char*)path;
			std::string finalPath = std::string(cstr);

			std::filesystem::path filesystemPath = finalPath;
			std::filesystem::directory_entry it(filesystemPath);

			if (!it.is_directory()) {
				if (filesystemPath.has_extension()) {
					auto ext = filesystemPath.extension().string();

					if (ext == ".obj" || ext == ".fbx") {
						m_ObjectCreator->AddEntity(finalPath, "Static Mesh", *m_EditorScene, *m_Console);
						m_EditorScene->RecalculateEntitiesCount();
						
					}
					else if (ext == ".raycast") {
						m_EditorScene->GetManager().Clear();
						m_SceneSerializer->Deserialize(finalPath, *m_EditorScene);
						m_SceneFilename = finalPath;
					}
					else if (ext == ".rcasset") {
						
						if (m_SceneHierarchy->HasSelectedEntity()) {
							
							auto& entity = m_SceneHierarchy->GetSelectedEntity();

							Entity* m_Entity = nullptr;
							m_Entity = &(*m_EditorScene->GetEntity(m_SceneHierarchy->GetSelectedEntity().GetId()));

							if (m_Entity->HasComponent<PBRMaterialComponent>()) {
								m_Entity->GetComponent<PBRMaterialComponent>().material.Apply(finalPath);
							}
							else {
								m_Entity->AddComponent<PBRMaterialComponent>();
								m_Entity->GetComponent<PBRMaterialComponent>().material.Apply(finalPath);
							}
						}
					}
					
				}
			}
		}

		ImGui::EndDragDropTarget();
	}


	ImGuizmo::SetDrawList();
	ImGuizmo::SetRect(m_ViewportBounds[0].x, m_ViewportBounds[0].y, m_ViewportBounds[1].x - m_ViewportBounds[0].x, m_ViewportBounds[1].y - m_ViewportBounds[0].y);
	 

	if (m_SceneHierarchy->HasSelectedEntity() && m_SceneProps->GetGizmosType() != -1) {


		const glm::mat4& ProjectionMatrix = m_EditorScene->GetMainCamera().GetProjectionMatrix();
		glm::mat4 ViewMatrix = m_EditorScene->GetMainCamera().GetViewMatrix();

		auto& ts = m_SceneHierarchy->GetSelectedEntity().GetComponent<TransformComponent>();

		glm::mat4 ModelMatrix = ts.GetTrasnform();

		ImGuizmo::Manipulate(glm::value_ptr(ViewMatrix), glm::value_ptr(ProjectionMatrix), static_cast<ImGuizmo::OPERATION>(m_SceneProps->GetGizmosType()), ImGuizmo::LOCAL, glm::value_ptr(ModelMatrix));


		if (ImGuizmo::IsUsing())
		{
			glm::vec3 position, rotation, scale;

			DecomposeModelMatrix(ModelMatrix, position, rotation, scale);


			glm::vec3 dtRotation = rotation - ts.Rotation;
			ts.Position = position;
			ts.Rotation += dtRotation;
			ts.Scale = scale;

		}
	}


	ImGui::End();
	ImGui::PopStyleVar();


	// ------------ GUI COMPONENTS RENDER ----------------- //

	m_SceneHierarchy->Render(*m_EditorScene);
	m_ContentBrowser->OnRender(*m_EditorScene);
	m_Console->Render();
	m_EntityCreator->Render(*m_ObjectCreator);
	m_ObjectProperties->OnRender(*m_EditorScene, *m_Console);
	m_SceneProps->Render(*m_EditorScene);
	m_TerrainEditor->Render(*m_EditorScene, *m_SceneHierarchy);
	m_stateMachine->Render();


	// ------------ ----------------- --------------------//

	ImGui::End();
	ImGui::Render();	
	ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

	if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
	{
		GLFWwindow* backup_current_context = glfwGetCurrentContext();
		ImGui::UpdatePlatformWindows();
		//ImGui::RenderPlatformWindowsDefault();
		glfwMakeContextCurrent(backup_current_context);
	}

}

void GUILayer::HandleShortcuts()
{
	// open file
	if (Input::IsKeyPressed(GLFW_KEY_LEFT_CONTROL) && Input::IsKeyPressed(GLFW_KEY_O))
	{
		std::string path = FileDialogs::OpenFile("RayCast Scene (*.raycast)\0*.raycast\0");
		m_SceneSerializer->Deserialize(path, *m_EditorScene);
		m_SceneFilename = path;

		const std::filesystem::path systemPath = path;
		const std::string title = "RayCast Editor - " + systemPath.filename().string();

		Game::GetWindow().SetTitle(title);

		m_EditorScene->RecalculateEntitiesCount();
	}

	//save scene
	if (Input::IsKeyPressed(GLFW_KEY_LEFT_CONTROL) && Input::IsKeyPressed(GLFW_KEY_S))
	{
		if (m_SceneFilename.length() != 0) {
			m_SceneSerializer->Serialize(m_SceneFilename);
		}
		else {
			std::string path = FileDialogs::SaveFile("RayCast Scene (*.raycast)\0*.raycast\0");
			m_SceneSerializer->Serialize(path);
			m_SceneFilename = path;

			const std::filesystem::path systemPath = path;
			const std::string title = "RayCast Editor - " + systemPath.filename().string();

			Game::GetWindow().SetTitle(title);
			m_EditorScene->RecalculateEntitiesCount();
		}
	}

	if (Input::IsKeyPressed(GLFW_KEY_LEFT_CONTROL) && Input::IsKeyPressed(GLFW_KEY_W))
	{
		exit(true);
		Game::GetWindow().Close();
	}

	if (Input::IsKeyPressed(GLFW_KEY_LEFT_CONTROL) && Input::IsKeyPressed(GLFW_KEY_J))
	{
		m_Console->Clear();
	}
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

	static  const ImWchar icons_ranges[] = { ICON_MIN_FA, ICON_MAX_FA, 0 };
	ImFontConfig icons_config; icons_config.MergeMode = true; icons_config.PixelSnapH = true;
	io.Fonts->AddFontFromFileTTF("resources/fonts/fa-solid-900.ttf", 17.f, &icons_config, icons_ranges);
}

