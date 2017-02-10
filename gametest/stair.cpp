#include "stair.h"
#define IMG_LOCATION_STAIR "./anhlamgame/clamper.png"

stair::stair(LPDIRECT3DDEVICE9 d3ddev, LPD3DXSPRITE SpriteHandler):Sprite(d3ddev, SpriteHandler)
{
	this->id = STAIR;
	this->count = 5;
	this->Vx = 0;
	this->Vy = 0;
}
void stair::UpdateRender(LARGE_INTEGER stp)
{

}
void stair::Render(camera gameCamera)
{
	this->SpriteHandler->Begin(D3DXSPRITE_ALPHABLEND);
	for (int i = 0; i < count; i++)
	{
		D3DXVECTOR3 titleCenter = D3DXVECTOR3(8, 8, 0);
		D3DXVECTOR3 titlePosition;
		titlePosition.y = (this->currPosition.y - this->center.y) + titleCenter.y * 2 * (i)+titleCenter.y / 2;
		titlePosition.x = this->currPosition.x;
		this->SpriteHandler->Draw(this->texture, NULL, &titleCenter, &gameCamera.intoCamera(titlePosition, this->FaceDirection), D3DCOLOR_XRGB(255, 255, 255));
	}
	this->SpriteHandler->Draw(this->texture, NULL, &D3DXVECTOR3(8, 8, 0), &gameCamera.intoCamera(D3DXVECTOR3(100, 80, 0), this->FaceDirection), D3DCOLOR_XRGB(255, 255, 255));
	this->SpriteHandler->End();
}
void stair::ProcessCollision(collisionType type, Sprite * sprite)
{

}
bool stair::Init()
{
	HRESULT result;
	D3DXIMAGE_INFO ImageSprite;

	result = D3DXGetImageInfoFromFile(IMG_LOCATION_STAIR, &ImageSprite);
	result = D3DXCreateTextureFromFileEx(this->d3ddev, IMG_LOCATION_STAIR, ImageSprite.Width, ImageSprite.Height,
		1, D3DUSAGE_DYNAMIC, D3DFMT_UNKNOWN, D3DPOOL_DEFAULT, D3DX_DEFAULT, D3DX_DEFAULT, D3DCOLOR_XRGB(0, 0, 0), &ImageSprite, NULL,
		&this->texture);

	this->center.y = count * ImageSprite.Height / 2;
	this->center.x = ImageSprite.Width / 2;
	this->currPosition = D3DXVECTOR3(300, 80, 0);
	if (result != D3D_OK)
	{
		return false;
	}
	return true;
}
stair::~stair()
{

}
