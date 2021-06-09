#ifndef INPUT_H
#define INPUT_H

#include <GL/glew.h>
#include <iostream>

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

typedef struct _INPUT_GAMEPAD {
	unsigned int wButtons;
	GLbyte bLeftTrigger;
	GLbyte bRightTrigger;
	short sThumbLX;
	short sThumbLY;
	short sThumbRX;
	short sThumbRY;
} INPUT_GAMEPAD;
	

typedef struct _INPUT_KEYBOARD {
	

} INPUT_KEYBOARD;



#endif