#include "EditorScene2D.h"

void EditorScene2D::OnCreate()
{
}

void EditorScene2D::OnDestroy()
{
}

void EditorScene2D::OnActivate()
{
}

Entity& EditorScene2D::CreateEntity(unsigned int id, std::string name)
{
	return m_Manager.CreateEntity(id, name);
}

void EditorScene2D::DeleteEntity(unsigned int id)
{
}

void EditorScene2D::OnDeactivate()
{
}

void EditorScene2D::OnUpdate(float DeltaTime)
{
}

void EditorScene2D::OnRender()
{
}
