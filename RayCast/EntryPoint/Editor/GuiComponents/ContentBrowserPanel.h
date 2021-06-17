#ifndef CONTENT_BROWSER_H
#define CONTENT_BROWSER_H

#include <iostream>
#include <filesystem>



#include "SceneHierarchy.h"

class ContentBrowserPanel
{
public:
	ContentBrowserPanel();
	virtual ~ContentBrowserPanel();

	void OnRender();
private:
	std::filesystem::path m_CurrentDirectory;
};

#endif