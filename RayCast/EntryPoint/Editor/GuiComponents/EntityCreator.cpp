#include "EntityCreator.h"

EntityCreator::EntityCreator()
{
}

void EntityCreator::Update(float deltaTime)
{
}

void EntityCreator::Render(ObjectAdditor& objectAdditor)
{
	ImGuiWindowFlags window_flags = 0;
	auto ptr = true;
	ImGui::Begin("Entity", &ptr, window_flags);

	ImGui::Button("Grass Plane");


	ImGui::End();
}
