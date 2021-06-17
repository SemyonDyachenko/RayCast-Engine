#include "ContentBrowserPanel.h"



static const std::filesystem::path s_AssetsPath = "resources";

ContentBrowserPanel::ContentBrowserPanel() : m_CurrentDirectory(s_AssetsPath)
{
	
}

ContentBrowserPanel::~ContentBrowserPanel()
{
}

void ContentBrowserPanel::OnRender()
{
	ImGui::Begin("Content Browser");

	if (m_CurrentDirectory != std::filesystem::path(s_AssetsPath)) {
		if (ImGui::Button("<-")) {
			m_CurrentDirectory = m_CurrentDirectory.parent_path();
		}
	}

	for (auto& it : std::filesystem::directory_iterator(m_CurrentDirectory)) {

		const auto& path = it.path();
		auto relativePath = std::filesystem::relative(path, s_AssetsPath);
		std::string filenameString = relativePath.filename().string();

		if (it.is_directory()) {
			
			if (ImGui::Button(filenameString.c_str())) {
				m_CurrentDirectory /= path.filename();
			}
			ImGui::SameLine();

		}
		else {
			if (ImGui::Button(filenameString.c_str())) {
				
			}
			ImGui::SameLine();
		}

	}

	ImGui::End();

}
