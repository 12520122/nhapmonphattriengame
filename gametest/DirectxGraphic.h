#pragma once
//#include <d3d9.h> //da include <windows.h>
#include <d3dx9.h>
class DirectxGraphic
{
private:
	LPDIRECT3D9 d3d;
	LPDIRECT3DDEVICE9 d3ddev;

	LPDIRECT3DSURFACE9 surface;
	LPDIRECT3DSURFACE9 backbuffer;

	LPDIRECT3DTEXTURE9 Image;
	LPD3DXSPRITE SpriteHandler;
public:
	bool InitD3D(HWND hWnd);
	bool InitSurface();
	bool InitTextture();
	void Draw();
	void DrawTexture();
	DirectxGraphic();
	LPDIRECT3DDEVICE9 getDevice();
	LPD3DXSPRITE getSpriteHandler();
	~DirectxGraphic();
};