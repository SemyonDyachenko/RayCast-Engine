#ifndef EDITOR_LAYER_H
#define EDITOR_LAYER_H

#include "../Runtime/Core/Layer.h"
#include "Editor/Editor.h"


class EditorLayer : public Layer
{
public:
	EditorLayer();

	~EditorLayer();

	void Attach() override;

	void OnEvent() override;

	void Update(float deltaTime) override;

	void Render() override;

private:
	Editor* editor;
	
};

#endif