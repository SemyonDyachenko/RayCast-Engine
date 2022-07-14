#ifndef GUI_CONSOLE_H
#define GUI_CONSOLE_H



#include <iostream>
#include <math.h>
#include <string>
#include <map>
#include <vector>
#include <chrono>


//#include "../../../Vendor/imgui/imgui.h"
//#include "../../../Vendor/imgui/imgui_impl_glfw.h"
//#include "../../../Vendor/imgui/imgui_impl_opengl3.h"

#include "../../../Vendor/imgui-docking/imgui.h"
#include "../../../Vendor/imgui-docking/imgui_impl_glfw.h"
#include "../../../Vendor/imgui-docking/imgui_impl_opengl3.h"

enum class MessageStatus {
	Default = 0,
	Warning = 1,
	Error = 2,
	Exception = 3, 
};

struct ConsoleMessage {
	std::string text;
	std::string time;
	MessageStatus status;
};

class GuiConsole
{
public:
	GuiConsole();
	virtual ~GuiConsole() = default;

	void Update(float DeltaTime);

	void PushMessage(std::string text,std::string time,MessageStatus status);

	void Clear();

	static std::string MessageStatusToString(MessageStatus status);

	void Render();
private:
	std::vector<ConsoleMessage> m_Messages;
};


#endif