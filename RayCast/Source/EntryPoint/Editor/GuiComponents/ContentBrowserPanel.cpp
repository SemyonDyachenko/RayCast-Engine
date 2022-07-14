#include "stdafx.h"

#include "ContentBrowserPanel.h"

#include "../../../Runtime/Rendering/stb_image.h"

static bool LoadTextureImGui(const char* filename, GLuint* out_texture, int* out_width, int* out_height) {
	int image_width = 0;
	int image_height = 0;
	unsigned char* image_data = stbi_load(filename, &image_width, &image_height, NULL, 4);
	if (image_data == NULL)
		return false;

	// Create a OpenGL texture identifier
	GLuint image_texture;
	glGenTextures(1, &image_texture);
	glBindTexture(GL_TEXTURE_2D, image_texture);

	// Setup filtering parameters for display
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE); // This is required on WebGL for non power-of-two textures
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE); // Same

	// Upload pixels into texture
#if defined(GL_UNPACK_ROW_LENGTH) && !defined(__EMSCRIPTEN__)
	glPixelStorei(GL_UNPACK_ROW_LENGTH, 0);
#endif
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, image_width, image_height, 0, GL_RGBA, GL_UNSIGNED_BYTE, image_data);
	stbi_image_free(image_data);

	*out_texture = image_texture;
	*out_width = image_width;
	*out_height = image_height;

	return true;
}


static const std::filesystem::path s_AssetsPath = "resources";

ContentBrowserPanel::ContentBrowserPanel() : m_CurrentDirectory(s_AssetsPath)
{
	jpgTexture = nullptr;
}

ContentBrowserPanel::~ContentBrowserPanel()
{
}

void ContentBrowserPanel::OnRender()
{
	ImGui::Begin("Content Browser");

	if (m_CurrentDirectory != std::filesystem::path(s_AssetsPath)) {
		if (ImGui::Button(ICON_FA_ARROW_LEFT)) {
			m_CurrentDirectory = m_CurrentDirectory.parent_path();
		}
	}

	for (auto& it : std::filesystem::directory_iterator(m_CurrentDirectory)) {

		const auto& path = it.path();
		auto relativePath = std::filesystem::relative(path, s_AssetsPath);
		std::string filenameString = relativePath.filename().string();

		if (it.is_directory()) {

			
			ImGui::Button(ICON_FA_FOLDER);

			ImGui::SameLine();
	
			if (ImGui::Button(filenameString.c_str())) {
				m_CurrentDirectory /= path.filename();
			}

			
			
		}
		else {
			std::string texturePath = path.string();

			GLuint id = 0;
			int width = 0, height = 0;
			//LoadTextureImGui(texturePath.c_str(), &id, &width, &height);		

			std::string filename = path.filename().string();


			ImGui::Button(ICON_FA_FILE);
			ImGui::SameLine();
			if (ImGui::Button(filename.c_str())) {

			}

		}
	}

	ImGui::End();

}

	

