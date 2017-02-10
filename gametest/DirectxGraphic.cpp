#include "DirectxGraphic.h"
#include <time.h>
bool DirectxGraphic::InitD3D(HWND hWnd)
{
	d3d = Direct3DCreate9(D3D_SDK_VERSION);
	if (!d3d)
	{
		return false;
	}
	D3DPRESENT_PARAMETERS d3dpp;
	ZeroMemory(&d3dpp, sizeof(d3dpp));
	d3dpp.Windowed = true;
	d3dpp.BackBufferCount = 1;
	d3dpp.BackBufferFormat = D3DFMT_UNKNOWN;
	d3dpp.BackBufferWidth = 600;
	d3dpp.BackBufferHeight = 400;
	d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;
	d3dpp.hDeviceWindow = hWnd;

	HRESULT hr = d3d->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, hWnd, D3DCREATE_SOFTWARE_VERTEXPROCESSING, &d3dpp, &this->d3ddev);
	if (FAILED(hr))
	{
		return false;
	}

	D3DXCreateSprite(this->d3ddev, &this->SpriteHandler);
	return true;
}
bool DirectxGraphic::InitSurface()
{
	RECT des;
	des.top = des.left = 0;
	des.bottom = des.right = 32;
	RECT src;
	src.top = src.left = 0;
	src.bottom = src.right = 32;
	D3DXIMAGE_INFO tmpimage;
	LPCSTR filepath = "./anhlamgame/icon_master_final.png";
	D3DXGetImageInfoFromFile(
		filepath,
		&tmpimage);
	HRESULT result = d3ddev->CreateOffscreenPlainSurface(tmpimage.Width, tmpimage.Height, tmpimage.Format, D3DPOOL_DEFAULT, &this->surface, NULL);//dinh kich thuoc cho surface voi kich thuoc anh dc insert
	if (result != D3D_OK)
	{
		return false;
	}
	result = D3DXLoadSurfaceFromFile(surface, NULL, &des, filepath, &src, D3DX_DEFAULT, 0, NULL);
	d3ddev->GetBackBuffer(0, 0, D3DBACKBUFFER_TYPE_MONO, &this->backbuffer);
	return false;
}
DirectxGraphic::DirectxGraphic(){}
bool DirectxGraphic::InitTextture()
{
	RECT des;
	des.top = des.left = 0;
	des.bottom = des.right = 32;
	RECT src;
	src.top = src.left = 0;
	src.bottom = src.right = 32;
	D3DXVECTOR3 position;
	position.x = 16;
	position.y = 16;
	position.z = 0;
	D3DCOLOR imgcolor;
	D3DXIMAGE_INFO tmpimage;
	LPCSTR filepath = "./anhlamgame/icon_master_cut_man.png";
	D3DXGetImageInfoFromFile(filepath, &tmpimage);
	HRESULT result = D3DXCreateTextureFromFileEx(this->d3ddev, filepath, tmpimage.Width, tmpimage.Height, 1, D3DUSAGE_DYNAMIC,
		D3DFMT_UNKNOWN, D3DPOOL_DEFAULT, D3DX_DEFAULT, D3DX_DEFAULT, D3DCOLOR_XRGB(0, 0, 0), &tmpimage, NULL, &this->Image);
	if (result != D3D_OK)
	{
		return false;
	}
	D3DXCreateSprite(this->d3ddev, &this->SpriteHandler);
	
	return true;
}
void DirectxGraphic::Draw()
{
	srand(time(NULL));
	RECT des;
	int rd = rand() % 300;
	des.top = des.left = 0 + rd;
	des.bottom = des.right = 32 + rd;
	RECT src;
	src.top = src.left = 0;
	src.bottom = src.right = 32;

	d3ddev->Clear(1, NULL, D3DCLEAR_TARGET, D3DCOLOR_XRGB(255, 255, 255), 1, NULL);
	d3ddev->BeginScene();
	d3ddev->StretchRect(surface, NULL, backbuffer, &des, D3DTEXF_NONE);
	d3ddev->EndScene();
	d3ddev->Present(NULL, NULL, NULL, NULL);
}
void DirectxGraphic::DrawTexture()
{
	srand(time(NULL));
	int rd = rand() % 300;
	RECT des;
	des.top = des.left = 0;
	des.bottom = des.right = 32;
	RECT src;
	src.top = src.left = 0;
	src.bottom = src.right = 32;
	D3DXVECTOR3 position;
	position.x = 0 + rd;
	position.y = 0 + rd;
	position.z = 0;
	D3DXVECTOR3 center;
	center.x = 16;
	center.y = 16;
	center.z = 0;
	D3DCOLOR imgcolor;
	d3ddev->Clear(1, NULL, D3DCLEAR_TARGET, D3DCOLOR_XRGB(0,0,0), 1, NULL);
	this->d3ddev->BeginScene();
	this->SpriteHandler->Begin(D3DXSPRITE_ALPHABLEND);
	this->SpriteHandler->Draw(Image, NULL, &center, &position, D3DCOLOR_XRGB(255, 255, 255));
	this->SpriteHandler->End();
	this->d3ddev->EndScene();
	this->d3ddev->Present(NULL, NULL, NULL, NULL);
}
LPDIRECT3DDEVICE9 DirectxGraphic::getDevice()
{
	return this->d3ddev;
}
LPD3DXSPRITE DirectxGraphic::getSpriteHandler()
{
	return this->SpriteHandler;
}
DirectxGraphic::~DirectxGraphic()
{
	if (d3d != NULL)
	{
		d3d->Release();
		d3d = NULL;
	}
	if (d3ddev != NULL)
	{
		d3ddev->Release();
		d3ddev = NULL;
	}
}