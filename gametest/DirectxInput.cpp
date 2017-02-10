#include "DirectxInput.h"
#include <string>
DirectxInput::DirectxInput()
{
	//this->keyboardEvent = new DIDEVICEOBJECTDATA[KEYBOARD_BUFFER_SIZE];
}
bool DirectxInput::CreateInput()
{
	HRESULT result;
	result = DirectInput8Create(GetModuleHandle(NULL), DIRECTINPUT_VERSION, IID_IDirectInput8, (void**)&this->pInput, NULL);
	if (FAILED(result))
	{
		return false;
	}
	return true;
}

bool DirectxInput::CreateKeyboardInput(HWND hWnd)
{
	HRESULT result;
	result = this->pInput->CreateDevice(GUID_SysKeyboard, &this->pKeyboardDevice, NULL);
	if (FAILED(result))
	{
		return false;
	}
	result = this->pKeyboardDevice->SetDataFormat(&c_dfDIKeyboard);
	result = this->pKeyboardDevice->SetCooperativeLevel(hWnd, DISCL_FOREGROUND | DISCL_NONEXCLUSIVE);
	DIPROPDWORD dipdw;
	dipdw.diph.dwSize = sizeof(DIPROPDWORD);
	dipdw.diph.dwHeaderSize = sizeof(DIPROPHEADER);
	dipdw.diph.dwObj = 0;
	dipdw.diph.dwHow = DIPH_DEVICE;
	dipdw.dwData = KEYBOARD_BUFFER_SIZE; // Arbitary buffer size //KEYBOARD_BUFFER_SIZE

	result = this->pKeyboardDevice->SetProperty(DIPROP_BUFFERSIZE, &dipdw.diph);
	if (result != DI_OK)
	{
		return false;
	}
	result = this->pKeyboardDevice->Acquire(); //test chiem quyen dieu khien
	result = this->pKeyboardDevice->Unacquire();
	if (FAILED(result))
	{
		return false;
	}

	return true;
}

void DirectxInput::ProcessKeyBoard()
{
	int b = 0;
	DWORD dwItems = KEYBOARD_BUFFER_SIZE;
	char buffer[512];
	HRESULT result, result1, result2;
	result = this->pKeyboardDevice->Acquire();
	result2 = this->pKeyboardDevice->GetDeviceState(sizeof(this->ListKeyActive), (LPVOID)&this->ListKeyActive);
	result1 = this->pKeyboardDevice->GetDeviceData(sizeof(DIDEVICEOBJECTDATA), this->keyboardEvent, &dwItems, 0);
	if (result1 != DI_OK)
	{
		MessageBox(NULL, "getdevicedata fail", NULL, NULL);
	}
	//if (result2 != DI_OK)
	//{
	//	MessageBox(NULL, "getdevicedata fail", NULL, NULL);

	//}
	if (result == DIERR_INPUTLOST || result == DIERR_NOTACQUIRED)
	{
		this->pKeyboardDevice->Acquire();
	}
	if (result1 == DI_BUFFEROVERFLOW)
	{
		MessageBox(NULL, "overflow", NULL, NULL);
	}
	if (IsKeyDown(DIK_SPACE))
	{
		int a = 1;
		//ZeroMemory(this->keyboardEvent, sizeof(DIDEVICEOBJECTDATA));
//      sprintf_s(buffer, "%d", this->ListKeyActive[DIK_LEFT]);
		//MessageBox(NULL, buffer, "left-1", MB_OK);
	}
}
bool DirectxInput::IsKeyDown(int Key)
{
	bool ret = this->ListKeyActive[Key] & 0x80;
	return ret;
}
char* DirectxInput::GetListKeyActive()
{
	return this->ListKeyActive;
}
DIDEVICEOBJECTDATA* DirectxInput::GetKeyBoardEvent()
{
	return this->keyboardEvent;
}
DirectxInput::~DirectxInput()
{
	if (pKeyboardDevice != NULL)
	{
		this->pKeyboardDevice->Unacquire();
		this->pKeyboardDevice->Release();
	}
	
}