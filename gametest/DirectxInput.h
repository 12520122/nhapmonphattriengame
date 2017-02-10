#pragma once
#include <dinput.h>
#define KEYBOARD_BUFFER_SIZE 20
class DirectxInput
{
private:
	LPDIRECTINPUT8 pInput;
	LPDIRECTINPUTDEVICE8 pKeyboardDevice;
	LPDIRECTINPUTDEVICE8 pMouseDevice;
	char ListKeyActive[256];
	DIDEVICEOBJECTDATA keyboardEvent[KEYBOARD_BUFFER_SIZE];
public:
	DirectxInput();
	bool CreateInput();
	bool CreateKeyboardInput(HWND hWnd);
	void ProcessKeyBoard();
	bool IsKeyDown(int Key);
	char * GetListKeyActive();
	DIDEVICEOBJECTDATA * GetKeyBoardEvent();
	~DirectxInput();
};