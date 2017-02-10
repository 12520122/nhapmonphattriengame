#include "BrickHidden.h"
#define IMG_LOCATION_CLAMPER "./anhlamgame/clamper.png"
BrickHidden::BrickHidden(LPDIRECT3DDEVICE9 d3ddev, LPD3DXSPRITE SpriteHandler) : Sprite(d3ddev,SpriteHandler)
{
	this->id = BRICKHIDDEN;
	this->count = 41;
	this->Vx = 0;
	this->Vy = 0;
}
bool BrickHidden::Init()
{
	HRESULT result;
	D3DXIMAGE_INFO ImageSprite;
	
	result = D3DXGetImageInfoFromFile(IMG_LOCATION_CLAMPER, &ImageSprite);
	result = D3DXCreateTextureFromFileEx(this->d3ddev, IMG_LOCATION_CLAMPER, ImageSprite.Width, ImageSprite.Height,
		1, D3DUSAGE_DYNAMIC, D3DFMT_UNKNOWN, D3DPOOL_DEFAULT, D3DX_DEFAULT, D3DX_DEFAULT, D3DCOLOR_XRGB(0, 0, 0), &ImageSprite, NULL,
		&this->TextureSprite);

	this->center.x = count * ImageSprite.Width / 2;
	this->center.y = ImageSprite.Height / 2;
	this->currPosition = D3DXVECTOR3(300,24,0);
	if (result != D3D_OK)
	{
		return false;
	}
	return true;
}
void BrickHidden::Render(camera gameCamera)
{
	this->SpriteHandler->Begin(D3DXSPRITE_ALPHABLEND);
	for (int i = 0; i < count; i++)
	{
		D3DXVECTOR3 titleCenter = D3DXVECTOR3(8, 8, 0);
		D3DXVECTOR3 titlePosition;
		titlePosition.x = (this->currPosition.x - this->center.x) + titleCenter.x * 2 * (i)+titleCenter.x / 2;
		titlePosition.y = this->currPosition.y;
		this->SpriteHandler->Draw(this->TextureSprite, NULL, &titleCenter, &gameCamera.intoCamera(titlePosition, this->FaceDirection), D3DCOLOR_XRGB(255, 255, 255));
	}
	this->SpriteHandler->Draw(this->TextureSprite, NULL, &D3DXVECTOR3(8, 8, 0), &gameCamera.intoCamera(D3DXVECTOR3(100, 80, 0), this->FaceDirection), D3DCOLOR_XRGB(255, 255, 255));
	this->SpriteHandler->End();
}
BrickHidden::~BrickHidden()
{

}