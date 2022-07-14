#ifndef INPUT_H
#define INPUT_H

#include <GL/glew.h>
#include <iostream>
#include <glm.hpp>

#define INPUT_GAMEPAD_DRAP_UP 0x0001
#define INPUT_GAMEPAD_DRAP_DOWN 0x0002
#define INPUT_GAMEPAD_DRAP_LEFT 0x0004
#define INPUT_GAMEPAD_DRAP_RIGHT 0x0008
#define INPUT_GAMEPAD_START 0x0010
#define INPUT_GAMEPAD_BACK 0x0020
#define INPUT_GAMEPAD_LEFT_THUMB 0x0040
#define INPUT_GAMEPAD_RIGHT_THUMB 0x0080
#define INPUT_GAMEPAD_LEFT_SHOULDER 0x0100
#define INPUT_GAMEPAD_RIGHT_SHOULDER 0x0200
#define INPUT_GAMEPAD_A 0x1000
#define INPUT_GAMEPAD_B 0x2000
#define INPUT_GAMEPAD_X 0x4000
#define INPUT_GAMEPAD_Y 0x8000

#define INPUT_KEY_SPACE 32
#define INPUT_KEY_0 48
#define INPUT_KEY_1 49
#define INPUT_KEY_2 50
#define INPUT_KEY_3 51
#define INPUT_KEY_4 52
#define INPUT_KEY_5 53
#define INPUT_KEY_6 54
#define INPUT_KEY_7 55
#define INPUT_KEY_8 56
#define INPUT_KEY_9 57
#define INPUT_KEY_A 65
#define INPUT_KEY_B 66
#define INPUT_KEY_C 67
#define INPUT_KEY_D 68
#define INPUT_KEY_E 69
#define INPUT_KEY_F 70
#define INPUT_KEY_G 71
#define INPUT_KEY_H 72
#define INPUT_KEY_I 73
#define INPUT_KEY_J 74
#define INPUT_KEY_K 75
#define INPUT_KEY_L 76
#define INPUT_KEY_M 77
#define INPUT_KEY_N 78
#define INPUT_KEY_O 79
#define INPUT_KEY_P 80
#define INPUT_KEY_Q 81
#define INPUT_KEY_R 82
#define INPUT_KEY_S 83
#define INPUT_KEY_T 84
#define INPUT_KEY_U 85
#define INPUT_KEY_V 86
#define INPUT_KEY_W 87
#define INPUT_KEY_X 88
#define INPUT_KEY_Y 89
#define INPUT_KEY_Z 90




namespace Gamepad
{

	enum Axis {
		X, Y, Z, R,
		U, V,
		PovX, PovY
	};
}


class Input {
public:

	Input() {}
	//Input(const Input&) = delete;

	virtual ~Input() = default;

	static bool IsKeyPressed(int key);

	static bool IsMouseButtonPressed(int button);

	static bool IsKeyReleased(int key);

	static glm::vec2 GetMousePosition();

	static void SetMousePosition(float x,float y);

	static bool GamepadIsConnected(unsigned int gamepad);

	static bool GamepadHasAxis(unsigned int gamepad, Gamepad::Axis axis);

	static bool GamepadIsButtonPressed(unsigned int gamepad, unsigned int button);

	static float GamepadGetAxisPosition(unsigned int gamepad, Gamepad::Axis axis);


};

class LuaInput {
public:
	LuaInput() {}

	~LuaInput() {}

	int StringToKey(std::string key) {
		if (key == "A") return KEY_A;
		else if (key == "B") return KEY_B;
		else if (key == "C") return KEY_C;
		else if (key == "D") return KEY_D;
		else if (key == "E") return KEY_E;
		else if (key == "F") return KEY_F;
		else if (key == "G") return KEY_G;
		else if (key == "H") return KEY_H;
		else if (key == "I") return KEY_I;
		else if (key == "J") return KEY_J;
		else if (key == "K") return KEY_K;
		else if (key == "L") return KEY_L;
		else if (key == "M") return KEY_M;
		else if (key == "N") return KEY_N;
		else if (key == "O") return KEY_O;
		else if (key == "P") return KEY_P;
		else if (key == "Q") return KEY_Q;
		else if (key == "R") return KEY_R;
		else if (key == "S") return KEY_S;
		else if (key == "T") return KEY_T;
		else if (key == "U") return KEY_U;
		else if (key == "V") return KEY_V;
		else if (key == "W") return KEY_W;
		else if (key == "X") return KEY_X;
		else if (key == "Y") return KEY_Y;
		else if (key == "Z") return KEY_Z;

		else if (key == "0") return KEY_0;
		else if (key == "1") return KEY_1;
		else if (key == "2") return KEY_2;
		else if (key == "3") return KEY_3;
		else if (key == "4") return KEY_4;
		else if (key == "5") return KEY_5;
		else if (key == "6") return KEY_6;
		else if (key == "7") return KEY_7;
		else if (key == "8") return KEY_8;
		else if (key == "9") return KEY_9;

		else if (key == "KP_0") return KEY_KP_0;
		else if (key == "KP_1") return KEY_KP_1;
		else if (key == "KP_2") return KEY_KP_2;
		else if (key == "KP_3") return KEY_KP_3;
		else if (key == "KP_4") return KEY_KP_4;
		else if (key == "KP_5") return KEY_KP_5;
		else if (key == "KP_6") return KEY_KP_6;
		else if (key == "KP_7") return KEY_KP_7;
		else if (key == "KP_8") return KEY_KP_8;
		else if (key == "KP_9") return KEY_KP_9;

		else if (key == "F1") return KEY_F1;
		else if (key == "F2") return KEY_F2;
		else if (key == "F3") return KEY_F3;
		else if (key == "F4") return KEY_F4;
		else if (key == "F5") return KEY_F5;
		else if (key == "F6") return KEY_F6;
		else if (key == "F7") return KEY_F7;
		else if (key == "F8") return KEY_F8;
		else if (key == "F9") return KEY_F9;
		else if (key == "F10") return KEY_F10;
		else if (key == "F11") return KEY_F11;
		else if (key == "F12") return KEY_F12;

		else if (key == "Space") return KEY_SPACE;
		else if (key == "Left Shift") return KEY_LSHIFT;
		else if (key == "Left Ctrl") return KEY_LCTRL;
		else if (key == "Left Alt") return KEY_LALT;
		else if (key == "Right Shift") return KEY_RSHIFT;
		else if (key == "Right Ctrl") return KEY_RCTRL;
		else if (key == "Right Alt") return KEY_RALT;

		else if (key == "Esc") return KEY_ESCAPE;
		else if (key == "Delete") return KEY_DELETE;
		else if (key == "Home") return KEY_HOME;

		else if (key == "Arrow Up") return KEY_UP;
		else if (key == "Arrow Down") return KEY_DOWN;
		else if (key == "Arrow Left") return KEY_LEFT;
		else if (key == "Arrow Right") return KEY_RIGHT;

		else return KEY_UNKNOWN;
	}

	glm::vec2 GetMousePosition()
	{
		return Input::GetMousePosition();
	}

	glm::vec2 GetMouseDelta()
	{
		glm::vec2 position = GetMousePosition();
		glm::vec2 delta = position - InitialMousePosition;
		InitialMousePosition = position;
		return delta;
	}
	
	void SetMousePosition(float x,float y)
	{
		Input::SetMousePosition(x,y);
	}
	
	bool IsKeyReleased(int key) {
		return Input::IsKeyReleased(key);
	}

	bool IsKeyPressed(int key) {
		return Input::IsKeyPressed(key);
	}

	bool IsMouseButtonPressed(int button) {
		return Input::IsMouseButtonPressed(button);
	}
private:
	glm::vec2 InitialMousePosition;
public:
	int KEY_UNKNOWN = GLFW_KEY_UNKNOWN;
	int KEY_A = GLFW_KEY_A;
	int KEY_B = GLFW_KEY_B;
	int KEY_C = GLFW_KEY_C;
	int KEY_D = GLFW_KEY_D;
	int KEY_E = GLFW_KEY_E;
	int KEY_F = GLFW_KEY_F;
	int KEY_G = GLFW_KEY_G;
	int KEY_H = GLFW_KEY_H;
	int KEY_I = GLFW_KEY_E;
	int KEY_J = GLFW_KEY_J;
	int KEY_K = GLFW_KEY_K;
	int KEY_L = GLFW_KEY_L;
	int KEY_M = GLFW_KEY_M;
	int KEY_N = GLFW_KEY_N;
	int KEY_O = GLFW_KEY_O;
	int KEY_P = GLFW_KEY_P;
	int KEY_Q = GLFW_KEY_Q;
	int KEY_R = GLFW_KEY_R;
	int KEY_S = GLFW_KEY_S;
	int KEY_T = GLFW_KEY_T;
	int KEY_U = GLFW_KEY_U;
	int KEY_V = GLFW_KEY_V;
	int KEY_W = GLFW_KEY_W;
	int KEY_X = GLFW_KEY_X;
	int KEY_Y = GLFW_KEY_Y;
	int KEY_Z = GLFW_KEY_Z;

	int KEY_0 = GLFW_KEY_0;
	int KEY_1 = GLFW_KEY_1;
	int KEY_2 = GLFW_KEY_2;
	int KEY_3 = GLFW_KEY_3;
	int KEY_4 = GLFW_KEY_4;
	int KEY_5 = GLFW_KEY_5;
	int KEY_6 = GLFW_KEY_6;
	int KEY_7 = GLFW_KEY_7;
	int KEY_8 = GLFW_KEY_8;
	int KEY_9 = GLFW_KEY_9;


	int KEY_F1 = GLFW_KEY_F1;
	int KEY_F2 = GLFW_KEY_F1;
	int KEY_F3 = GLFW_KEY_F1;
	int KEY_F4 = GLFW_KEY_F4;
	int KEY_F5 = GLFW_KEY_F5;
	int KEY_F6 = GLFW_KEY_F6;
	int KEY_F7 = GLFW_KEY_F7;
	int KEY_F8 = GLFW_KEY_F8;
	int KEY_F9 = GLFW_KEY_F9;
	int KEY_F10 = GLFW_KEY_F10;
	int KEY_F11 = GLFW_KEY_F11;
	int KEY_F12 = GLFW_KEY_F12;
	int KEY_F13 = GLFW_KEY_F13;
	int KEY_F14 = GLFW_KEY_F14;
	int KEY_F15 = GLFW_KEY_F15;
	int KEY_F16 = GLFW_KEY_F16;
	int KEY_F17 = GLFW_KEY_F17;
	int KEY_F18 = GLFW_KEY_F18;
	int KEY_F19 = GLFW_KEY_F19;
	int KEY_F20 = GLFW_KEY_F20;
	int KEY_F21 = GLFW_KEY_F21;
	int KEY_F22 = GLFW_KEY_F22;
	int KEY_F23 = GLFW_KEY_F23;
	int KEY_F24 = GLFW_KEY_F24;

	int KEY_BACKSPACE = GLFW_KEY_BACKSPACE;
	int KEY_TAB = GLFW_KEY_TAB;
	int KEY_RETURN = GLFW_KEY_ENTER;
	//static int KEY_RETURN2 = GLFW_KEY_ENTER;
	int KEY_ENTER = GLFW_KEY_ENTER;

	int KEY_NUMLOCKCLEAR = GLFW_KEY_NUM_LOCK;
	int KEY_SCROLLLOCK = GLFW_KEY_SCROLL_LOCK;

	int KEY_RSHIFT = GLFW_KEY_RIGHT_SHIFT;
	int KEY_LSHIFT = GLFW_KEY_LEFT_SHIFT;
	int KEY_RCTRL = GLFW_KEY_RIGHT_CONTROL;
	int KEY_LCTRL = GLFW_KEY_LEFT_CONTROL;
	int KEY_RALT = GLFW_KEY_RIGHT_ALT;
	int KEY_LALT = GLFW_KEY_LEFT_ALT;

	int KEY_PAUSE = GLFW_KEY_PAUSE;
	int KEY_CAPSLOCK = GLFW_KEY_CAPS_LOCK;
	int KEY_ESCAPE = GLFW_KEY_ESCAPE;
	int KEY_SPACE = GLFW_KEY_SPACE;
	int KEY_PAGEUP = GLFW_KEY_PAGE_UP;
	int KEY_PAGEDOWN = GLFW_KEY_PAGE_DOWN;
	int KEY_END = GLFW_KEY_END;
	int KEY_HOME = GLFW_KEY_HOME;

	int KEY_LEFT = GLFW_KEY_LEFT;
	int KEY_UP = GLFW_KEY_UP;
	int KEY_RIGHT = GLFW_KEY_RIGHT;
	int KEY_DOWN = GLFW_KEY_DOWN;

	int KEY_PRINTSCREEN = GLFW_KEY_PRINT_SCREEN;
	int KEY_INSERT = GLFW_KEY_INSERT;
	int KEY_DELETE = GLFW_KEY_DELETE;

	int KEY_KP_MULTIPLY = GLFW_KEY_KP_MULTIPLY;
	int KEY_KP_ADD = GLFW_KEY_KP_ADD;
	int KEY_KP_EQUAL = GLFW_KEY_KP_EQUAL;
	int KEY_KP_SUBTRACT = GLFW_KEY_KP_SUBTRACT;
	int KEY_KP_DIVIDE = GLFW_KEY_KP_DIVIDE;


	int KEY_KP_0 = GLFW_KEY_KP_0;
	int KEY_KP_1 = GLFW_KEY_KP_1;
	int KEY_KP_2 = GLFW_KEY_KP_2;
	int KEY_KP_3 = GLFW_KEY_KP_3;
	int KEY_KP_4 = GLFW_KEY_KP_4;
	int KEY_KP_5 = GLFW_KEY_KP_5;
	int KEY_KP_6 = GLFW_KEY_KP_6;
	int KEY_KP_7 = GLFW_KEY_KP_7;
	int KEY_KP_8 = GLFW_KEY_KP_8;
	int KEY_KP_9 = GLFW_KEY_KP_9;
};


#endif