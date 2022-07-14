#include "../../../stdafx.h"
#include "ContentBrowserPanel.h"



static const std::filesystem::path s_AssetsPath = "resources";

ContentBrowserPanel::ContentBrowserPanel() : m_CurrentDirectory(s_AssetsPath)
{
	m_DirectoryIcon = new Texture("resources/icons/DirectoryIcon.png");
	m_FileIcon = new Texture("resources/icons/FileIcon.png");

}

void ContentBrowserPanel::OnRender(EditorScene& scene)
{
	ImGuiWindowFlags window_flags = 0;

	auto ptr = true;
	ImGuiTreeNodeFlags treeNodeFlags = ImGuiTreeNodeFlags_OpenOnArrow | ImGuiTreeNodeFlags_DefaultOpen;

	ImGui::Begin("Content Folders");

	if (ImGui::TreeNodeEx((void*)(&m_CurrentDirectory), treeNodeFlags, ICON_FA_FOLDER_OPEN" Resources"))
	{
		for (auto& it : std::filesystem::directory_iterator(m_CurrentDirectory))
		{
			ImGuiTreeNodeFlags treeNodeSelectionFlags = (m_SelectedDirectory == it.path().string()) ? ImGuiTreeNodeFlags_Selected : 0 | ImGuiTreeNodeFlags_OpenOnArrow | ImGuiTreeNodeFlags_DefaultOpen;

			const auto& path = it.path();
			auto relativePath = std::filesystem::relative(path, s_AssetsPath);
			std::string filenameString = relativePath.filename().string();

			std::string folderIcon = m_SelectedDirectory == path.string() ? ICON_FA_FOLDER_OPEN : ICON_FA_FOLDER;
			std::string fmt = folderIcon + "  " + filenameString;

			if (it.is_directory())
			{
				if (ImGui::TreeNodeEx((void*)(&it), treeNodeSelectionFlags, fmt.c_str()))
				{

					ImGui::TreePop();
				}

				if (ImGui::IsItemClicked())
				{
					m_SelectedDirectory = path.string();
				}
			}
		}

		ImGui::TreePop();
	}

	ImGui::End();

	ImGui::Begin("Content Browser", &ptr, window_flags);


	ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(0.15f, 0.6f, 0.15f, 1.00f));
	if (ImGui::Button(ICON_FA_FILE"  New File", { 80,25 }))
	{
		ImGui::OpenPopup("File Add");
	}
	ImGui::PopStyleColor();

	ImGui::SameLine();

	ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(0.15f, 0.6f, 0.15f, 1.00f));
	if (ImGui::Button(ICON_FA_FILE"  New Folder", { 100,25 }))
	{
		std::string path = m_SelectedDirectory + "/New Folder";
		if (_mkdir(path.c_str()) == 1)
		{

		}
		else
		{
			ENGINE_ERROR("Cannot to create a new folder!");
		}
	}
	ImGui::PopStyleColor();

	ImGui::SameLine();

	if (ImGui::Button(ICON_FA_FILE_IMPORT"  Import", { 80,25 }))
	{
		if (std::string path = FileDialogs::OpenFile("(*.*)\0*.*\0"); path.length() > 0)
		{
			std::filesystem::path m_path = path;
			std::string filename = m_path.filename().string();
			std::string newFilePath = m_SelectedDirectory.length() > 0 ? m_SelectedDirectory + "\\" + filename : m_CurrentDirectory.string() + "\\" + filename;

			FilesystemUtils::FileCopy(path, newFilePath);
		}
	}
	ImGui::SameLine();

	ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(0.25f, 0.25f, 0.25f, 0.0f));
	if (ImGui::Button(ICON_FA_ARROW_ALT_CIRCLE_LEFT, { 30,25 }))
	{
		std::filesystem::path path = m_SelectedDirectory;
		m_SelectedDirectory = path.parent_path().string();
		m_LastSelected = path.string();
	}
	ImGui::SameLine();

	if (ImGui::Button(ICON_FA_ARROW_ALT_CIRCLE_RIGHT, { 30,25 }))
	{
		if (m_LastSelected.length() > 0) {
			m_SelectedDirectory = m_LastSelected;
			m_LastSelected.clear();
		}
	}
	ImGui::PopStyleColor();

	ImGui::SameLine();

	char search[256];
	memset(search, 0, sizeof(search));
	strcpy_s(search, sizeof(search), "Search");

	ImGui::PushItemWidth(140);
	if (ImGui::InputText("##searchcontent", search, IM_ARRAYSIZE(search)))
	{

	}
	ImGui::PopItemWidth();

	ImGui::Separator();


	float padding = 16.f;
	float thumbnailSize = 64.f;
	float widgetWidth = ImGui::GetContentRegionAvail().x;
	float cellSize = thumbnailSize + padding;

	int columnCount = static_cast<int>(widgetWidth / cellSize);

	if (columnCount < 1)
		columnCount = 1;

	if (m_SelectedDirectory.length() > 0) {


		ImGui::Columns(columnCount, 0, false);

		for (auto& it : std::filesystem::directory_iterator(m_SelectedDirectory)) {

			const auto& path = it.path();
			auto relativePath = std::filesystem::relative(path, m_SelectedDirectory);
			std::string filenameString = relativePath.filename().string();
			auto ext = path.extension().string();


			ImGui::PushID(filenameString.c_str());


			ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(0.25f, 0.25f, 0.25f, 0.0f));
			ImGui::ImageButton(it.is_directory() ? reinterpret_cast<ImTextureID>(m_DirectoryIcon->GetId()) : reinterpret_cast<ImTextureID>(m_FileIcon->GetId()), { thumbnailSize,thumbnailSize }, { 0,1 }, { 1,0 });

			if (ImGui::BeginDragDropSource()) {
				char buffer[256];

				strcpy_s(buffer, path.string().c_str());

				ImGui::SetDragDropPayload("contentelement", buffer, sizeof(char*) * std::size(buffer));

			
				ImGui::Text(buffer);
		
			

				ImGui::EndDragDropSource();
			}


			if (ImGui::BeginDragDropTarget()) {

				const ImGuiPayload* payload = ImGui::AcceptDragDropPayload("contentelement");

				if (payload) {
					const wchar_t* payloadPath = (const wchar_t*)payload->Data;
					const char* cstr = (const char*)payloadPath;
					std::string finalPath = std::string(cstr);

					std::filesystem::path filesystemPath = finalPath;

					if (it.is_directory()) {

						std::filesystem::copy(filesystemPath, path, std::filesystem::copy_options::recursive);
						std::filesystem::remove_all(filesystemPath);
					}


				}


				ImGui::EndDragDropTarget();
			}

			ImGui::PopStyleColor();


			ImGui::PopID();

			if (ImGui::IsMouseClicked(ImGuiMouseButton_Right) && ImGui::IsItemHovered())
			{
				m_OnRename = false;
				m_SelectedItem = it.path().string();
				ImGui::OpenPopup("File properties");
			}


			if (ImGui::IsMouseClicked(ImGuiMouseButton_Left) && ImGui::IsItemHovered())
			{
				m_OnRename = false;
				m_SelectedItem = path.string();
			}

			if (ImGui::IsMouseDoubleClicked(ImGuiMouseButton_Left) && ImGui::IsItemHovered())
			{
				if (it.is_directory())
				{
					std::filesystem::path currentDir = m_SelectedDirectory;
					currentDir /= path.filename();
					m_SelectedDirectory = currentDir.string();
				}
			}

			char name_buffer[256];

			memset(name_buffer, 0, sizeof(name_buffer));

			strcpy_s(name_buffer, sizeof(name_buffer), filenameString.c_str());

			if (m_SelectedItem == it.path().string() && m_OnRename) {
				ImGui::PushItemWidth(70);
				if (ImGui::InputText("##renamefile", name_buffer, IM_ARRAYSIZE(name_buffer)))
				{
					std::string name = std::string(name_buffer);
					std::string nameStr = m_SelectedDirectory + "\\" + name;
					std::filesystem::path finalPath = nameStr;

					if (Input::IsKeyPressed(GLFW_KEY_ENTER) || (ImGui::IsMouseDown(0) && ImGui::IsWindowHovered())) {
						std::filesystem::rename(path, finalPath);
						m_OnRename = false;
						m_SelectedItem = "";
					}
				}
				ImGui::PopItemWidth();

			}
			else {
				ImGui::TextWrapped(filenameString.c_str());
			}

			ImGui::NextColumn();
		}
	}



	if ((ImGui::IsMouseDown(0) && ImGui::IsWindowHovered())) {
		m_OnRename = false;
		m_SelectedItem = "";
	}



	if ((ImGui::IsMouseDown(1) && ImGui::IsWindowHovered()) && m_SelectedItem == "") {
		ImGui::OpenPopup("Global File properties");
	}


	/*------   Popup windows  -------*/



	if (ImGui::BeginPopup("Global File properties"))
	{
		if (ImGui::MenuItem("Paste"))
		{
			if (m_Clipboard.length() > 0)
			{
				std::filesystem::path path = m_Clipboard;
				std::filesystem::directory_entry it(path);

				if (it.is_directory())
				{
					std::string filename = path.filename().string() + " Copy";
					std::string finalPath = m_SelectedDirectory + "\\" + filename;
					std::filesystem::copy(m_Clipboard, finalPath, std::filesystem::copy_options::recursive);
				}
				else
				{
					std::string filename = path.stem().string() + " Copy" + path.extension().string();
					std::string finalPath = m_SelectedDirectory + "\\" + filename;
					FilesystemUtils::FileCopy(m_Clipboard, finalPath);
				}
			}
		}

		ImGui::EndPopup();
	}

	ImGui::PushStyleColor(ImGuiCol_PopupBg, {0.03f, 0.04f, 0.05f, 0.8f});
	if(ImGui::BeginPopup("File properties"))
	{

		if(ImGui::MenuItem("Rename"))
		{
			m_OnRename = true;
		}

		if (ImGui::MenuItem("Copy"))
		{
			m_Clipboard.clear();
			m_Clipboard = m_SelectedItem;
		}

		if (ImGui::MenuItem("Paste"))
		{
			if (m_Clipboard.length() > 0)
			{
				std::filesystem::path path = m_Clipboard;
				std::filesystem::directory_entry it(path);
				
				std::filesystem::path item = m_SelectedItem + "\\" + path.filename().string();

				if (item.string().length() > 0) 
					std::filesystem::copy(m_Clipboard, item.string(), std::filesystem::copy_options::recursive);
				
			}
		}

		if (ImGui::MenuItem("Delete"))
		{
			std::filesystem::path path = m_SelectedItem;
			std::filesystem::directory_entry it(path);

			if(it.is_directory())
			{
				std::filesystem::remove_all(m_SelectedItem);
			}
			else
			{
				std::filesystem::remove(m_SelectedItem);
			}
		}

		
		ImGui::EndPopup();
	}
	ImGui::PopStyleColor();

	if(ImGui::BeginPopup("File Add"))
	{

		if (ImGui::MenuItem(ICON_FA_FILE"  Text File"))
		{
			//std::string a = FileDialogs::OpenMultiplyFiles("(*.*)\0*.*\0");
			//ENGINE_INFO(a);
			std::string path = m_SelectedDirectory + "\\" + "New Doucment.txt";
			FilesystemUtils::NewFile(path);
		}
		
		if (ImGui::MenuItem(ICON_FA_FILE_CODE"  Lua Script"))
		{
			std::filesystem::path dirPath = m_SelectedDirectory;
			std::string parentPath = dirPath.parent_path().string();
			ENGINE_INFO(parentPath);
			if(m_SelectedDirectory == "resources\\scripts" || parentPath == "resources\\scripts")
			{
				std::string path = m_SelectedDirectory + "\\" + "NewScript.lua";
				std::string baseScript =
					"NewScript = ScriptComponent()\nfunction NewScript: init()\nself.input = Input()\nend\n\nfunction NewScript: Start()\nself.transform = self.entity:GetTransform()\nend\nfunction NewScript:Update(deltaTime)\nend\nfunction NewScript:Destroy()\nend\n";

				FilesystemUtils::NewFile(path, baseScript);
				
			}
		}

		if (ImGui::MenuItem(ICON_FA_FILE_IMAGE"  Material"))
		{
			std::string path = m_SelectedDirectory + "\\" + "M_Material.rcasset";
			FilesystemUtils::NewFile(path);
		}

		if (ImGui::MenuItem(ICON_FA_FILE_POWERPOINT"  Physic Material"))
		{
			std::string path = m_SelectedDirectory + "\\" + "PM_Material.rcpm";
			FilesystemUtils::NewFile(path);
		}


		ImGui::EndPopup();
	}
	
	ImGui::Columns(1);

	ImGui::End();

}



