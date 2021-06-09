#include "EditorLayer.h"

EditorLayer::EditorLayer()
{
}

EditorLayer::~EditorLayer()
{
}

void EditorLayer::Attach()
{
	editor = new Editor();
	editor->GetGuiLayer()->Attach();
}

void EditorLayer::OnEvent()
{
}

void EditorLayer::Update(float deltaTime)
{
}

void EditorLayer::Render()
{
	editor->GetGuiLayer()->Render();

}
