#ifndef EDITOR_H
#define EDITOR_H

#include "GUILayer.h"

class Editor
{
public:
	Editor() {
		guiLayer = new GUILayer();
	}

	~Editor() {

	}

	GUILayer* GetGuiLayer() { return guiLayer;  }
private:
	GUILayer* guiLayer;
};

#endif