#ifndef CONTENT_BROWSER_H
#define CONTENT_BROWSER_H

#include <iostream>
#include <filesystem>
#include <fstream>
#include <sstream>


#include "../Utils/IconsFontAwesome5.h"
#include "../SceneHierarchy/SceneHierarchy.h"
#include "../GuiComponents/ObjectAdditor.h"
#include "../../../Runtime/Utils/FilesystemUtils.h"


class ContentBrowserPanel
{
public: 
	ContentBrowserPanel();
	virtual ~ContentBrowserPanel() {}

	void OnRender(EditorScene & scene);
private:
	std::filesystem::path m_CurrentDirectory;
	Texture * m_DirectoryIcon;
	Texture * m_FileIcon;


	std::string m_SelectedDirectory = "";

	std::string m_SelectedItem = "";
	std::string m_LastSelected = "";
	bool m_OnRename = false;

	std::string m_Clipboard = "";

};

#endif