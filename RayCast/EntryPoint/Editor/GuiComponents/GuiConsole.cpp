
#include "../../../stdafx.h"
#include "GuiConsole.h"

GuiConsole::GuiConsole()
{
}

void GuiConsole::Update(float DeltaTime)
{
}

void GuiConsole::PushMessage(std::string text, std::string time, MessageStatus status)
{
	ConsoleMessage msg;
	msg.text = text;
	msg.time = time;
	msg.status = status;

	m_Messages.push_back(msg);

}

void GuiConsole::Clear()
{
	m_Messages.clear();
}

std::string GuiConsole::MessageStatusToString(MessageStatus status)
{
	switch (status)
	{
	case MessageStatus::Default:
		return "Info";
		break;
	case MessageStatus::Warning:
		return "Warning";
		break;
	case MessageStatus::Error:
		return "Error";
		break;
	case MessageStatus::Exception:
		return "Exception";
		break;
	default:
		return "Default";
		break;
	}

	return "Default";
}

void GuiConsole::Render()
{

	ImGuiWindowFlags window_flags = 0;
	auto ptr = true;
	ImGui::Begin("Console", &ptr, window_flags);

	for (size_t i = 0; i < m_Messages.size(); i++) {
		std::string msg = m_Messages[i].time + " " + "[" + MessageStatusToString(m_Messages[i].status) + "]" + " " + m_Messages[i].text;

		if (m_Messages[i].status == MessageStatus::Error) {
			ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(ImColor(255, 0, 0)));
			ImGui::Text(msg.c_str());
			ImGui::PopStyleColor(1);
		}

		if (m_Messages[i].status == MessageStatus::Warning) {
			ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(ImColor(255, 255, 0)));
			ImGui::Text(msg.c_str());
			ImGui::PopStyleColor(1);
		}

		if (m_Messages[i].status == MessageStatus::Default) {
			ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(ImColor(255, 255, 255)));
			ImGui::Text(msg.c_str());
			ImGui::PopStyleColor(1);
		}

		if (m_Messages[i].status == MessageStatus::Exception) {
			ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(ImColor(255, 165, 0)));
			ImGui::Text(msg.c_str());
			ImGui::PopStyleColor(1);
		}


	}
	ImGui::End();
}
