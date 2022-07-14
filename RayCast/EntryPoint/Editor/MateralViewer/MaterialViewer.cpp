#include "MaterialViewer.h"


MaterialViewer::MaterialViewer()
{
	m_Scene = new MaterialScene();
	m_Transparent = new Texture("resources/images/editor/transparentbg.jpg");

	ApplyMaterial();
}

MaterialViewer::~MaterialViewer()
{

}

 

void MaterialViewer::Update(float deltaTime)
{
	m_Scene->Update(deltaTime);
}

void MaterialViewer::ApplyMaterial()
{
	if (m_CurrentMaterialPath.length() > 0) {
		m_Structure = MaterialController::Deserailize(m_CurrentMaterialPath);
		m_Scene->ApplyMaterial(m_Structure);
		m_Scene->LoadMaterial();
	}
}

void MaterialViewer::Render(SceneHierarchy & sceneHierarchy,GuiConsole & console)
{
	const ImGuiTreeNodeFlags flags = ImGuiTreeNodeFlags_DefaultOpen | ImGuiTreeNodeFlags_Framed | ImGuiTreeNodeFlags_SpanAvailWidth | ImGuiTreeNodeFlags_AllowItemOverlap | ImGuiTreeNodeFlags_FramePadding;

	if (m_Opened) {
		ImGui::Begin("Material", &m_Opened);

		m_Scene->Render();

		ImGui::Image((ImTextureID)m_Scene->GetFrameBuffer()->GetTextureID(), { 400,300 }, { 0,1 }, { 1,0 });

		if (ImGui::BeginDragDropTarget()) {

			const ImGuiPayload* payload = ImGui::AcceptDragDropPayload("contentelement");

			if (payload) {
				const wchar_t* payloadPath = (const wchar_t*)payload->Data;
				const char* cstr = (const char*)payloadPath;
				std::string finalPath = std::string(cstr);

				std::filesystem::path filesystemPath = finalPath;
				std::filesystem::directory_entry it(filesystemPath);

				if (!it.is_directory()) {
					if (filesystemPath.has_extension()) {
						auto ext = filesystemPath.extension().string();

						if (ext == ".rcasset") {
							m_CurrentMaterialPath = finalPath;
							ApplyMaterial();

							if (m_Structure.AlbedoColor.length() == 0)
								console.PushMessage("No data to apply material",CalculateTime(), MessageStatus::Error);
							else
								console.PushMessage("Success apply material", CalculateTime(), MessageStatus::Default);
						}
					}
				}
			}

			ImGui::EndDragDropTarget();
		}

		if (ImGui::TreeNodeEx("##materialalbedocolor", flags,"Albedo Color")) {

			unsigned int m_AlbedoTexId = m_Scene->GetMaterial().m_AlbedoMap ? m_Scene->GetMaterial().m_AlbedoMap->GetId() : m_Transparent->GetId();

			ImGui::ImageButton((ImTextureID)m_AlbedoTexId, { 64,64 }, { 0,1 }, { 1,0 });

			if (ImGui::BeginDragDropTarget()) {

				const ImGuiPayload* payload = ImGui::AcceptDragDropPayload("contentelement");

				if (payload) {
					const wchar_t* payloadPath = (const wchar_t*)payload->Data;
					const char* cstr = (const char*)payloadPath;
					std::string finalPath = std::string(cstr);
						
					m_Structure.AlbedoColor = finalPath;
				}

				ImGui::EndDragDropTarget();
			}

			ImGui::SameLine();

			glm::vec3 color = { 1,1,1 };

			ImGui::ColorEdit3("##materialalbedocolor4",glm::value_ptr(color));

			ImGui::TreePop();
		}

	
		if (ImGui::TreeNodeEx("##materialnormalmap", flags, "Normal Map")) {

			unsigned int m_NormalTexId = m_Scene->GetMaterial().m_NormalMap ? m_Scene->GetMaterial().m_NormalMap->GetId() : m_Transparent->GetId();

			ImGui::ImageButton((ImTextureID)m_NormalTexId, { 64,64 }, { 0,1 }, { 1,0 });

			if (ImGui::BeginDragDropTarget()) {

				const ImGuiPayload* payload = ImGui::AcceptDragDropPayload("contentelement");

				if (payload) {
					const wchar_t* payloadPath = (const wchar_t*)payload->Data;
					const char* cstr = (const char*)payloadPath;
					std::string finalPath = std::string(cstr);

					m_Structure.NormalMap = finalPath;
				}

				ImGui::EndDragDropTarget();
			}

			ImGui::TreePop();
		}

		if (ImGui::TreeNodeEx("##materialmetallicmap", flags, "Metallic Map")) {


			unsigned int m_MetallicTexId = m_Scene->GetMaterial().m_MetallicMap ? m_Scene->GetMaterial().m_MetallicMap->GetId() : m_Transparent->GetId();

			ImGui::ImageButton((ImTextureID)m_MetallicTexId, { 64,64 }, { 0,1 }, { 1,0 });

			if (ImGui::BeginDragDropTarget()) {

				const ImGuiPayload* payload = ImGui::AcceptDragDropPayload("contentelement");

				if (payload) {
					const wchar_t* payloadPath = (const wchar_t*)payload->Data;
					const char* cstr = (const char*)payloadPath;
					std::string finalPath = std::string(cstr);

					m_Structure.MetallicMap = finalPath;
				}

				ImGui::EndDragDropTarget();
			}

			ImGui::TreePop();
		}


		if (ImGui::TreeNodeEx("##materialroughnessmap", flags, "Roughness Map")) {

			unsigned int m_RoughnessTexId = m_Scene->GetMaterial().m_RoughnessMap ? m_Scene->GetMaterial().m_RoughnessMap->GetId() : m_Transparent->GetId();

			ImGui::ImageButton((ImTextureID)m_RoughnessTexId, { 64,64 }, { 0,1 }, { 1,0 });

			if (ImGui::BeginDragDropTarget()) {

				const ImGuiPayload* payload = ImGui::AcceptDragDropPayload("contentelement");

				if (payload) {
					const wchar_t* payloadPath = (const wchar_t*)payload->Data;
					const char* cstr = (const char*)payloadPath;
					std::string finalPath = std::string(cstr);

					m_Structure.RoughnessMap = finalPath;
				}

				ImGui::EndDragDropTarget();
			}

			ImGui::TreePop();
		}
	

		if (ImGui::TreeNodeEx("##materialaomap", flags, "Ao Map")) {

			unsigned int m_AoTexId = m_Scene->GetMaterial().m_AoMap ? m_Scene->GetMaterial().m_AoMap->GetId() : m_Transparent->GetId();

			ImGui::ImageButton((ImTextureID)m_AoTexId, { 64,64 }, { 0,1 }, { 1,0 });

			if (ImGui::BeginDragDropTarget()) {

				const ImGuiPayload* payload = ImGui::AcceptDragDropPayload("contentelement");

				if (payload) {
					const wchar_t* payloadPath = (const wchar_t*)payload->Data;
					const char* cstr = (const char*)payloadPath;
					std::string finalPath = std::string(cstr);

					m_Structure.AoMap = finalPath;
				}

				ImGui::EndDragDropTarget();
			}

			ImGui::TreePop();
		}



		if (ImGui::Button("View", {200,25 })) {
			m_Scene->ApplyMaterial(m_Structure);
			m_Scene->LoadMaterial();
		}

		ImGui::SameLine();

		ImGui::PushItemWidth(200);
		if (ImGui::Button("Save", { 200,25 })) {
			MaterialController::Serialize(m_CurrentMaterialPath, m_Structure);
		}

	

		ImGui::End();
	}
}
