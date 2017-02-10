#include "cutman.h"
#define IMAGE_LOCATION "./anhlamgame/icon_master_cut_man.png" 

cutman::cutman(LPDIRECT3DDEVICE9 d3ddev, LPD3DXSPRITE SpriteHandler) : Sprite(d3ddev,SpriteHandler)
{
	this->id = CUTMAN;
	this->Vx = 0;
	this->Vy = 0;
	this->Ax = 0;
	this->Ay = -granvity;
	this->currPosition = { 550, 95, 0 };
}
void cutman::UpdateRender(LARGE_INTEGER stp)
{
	//this->UpdatePosition();
}

bool cutman::Init()
{
	HRESULT result;
	D3DXIMAGE_INFO imgCutman;
	result = D3DXGetImageInfoFromFile(IMAGE_LOCATION, &imgCutman);
	float center_x = imgCutman.Width / 2.0;
	float center_y = imgCutman.Height / 2.0;
	this->center = { center_x, center_y, 0 };

	result = D3DXCreateTextureFromFileEx(this->d3ddev, IMAGE_LOCATION, imgCutman.Width, imgCutman.Height, 1, D3DUSAGE_DYNAMIC, D3DFMT_UNKNOWN, D3DPOOL_DEFAULT, D3DX_DEFAULT, D3DX_DEFAULT, D3DCOLOR_XRGB(0, 0, 0), &imgCutman, NULL,
		&this->texture);
	result = D3DXCreateSprite(this->d3ddev, &this->SpriteHandler);
	if(FAILED(result))
	{
		return false;
	}
	return true;
}
void cutman::Render(camera gameCamera)
{
	RECT src = {0, 0, 32, 32};
	this->SpriteHandler->Begin(D3DXSPRITE_ALPHABLEND);
	this->SpriteHandler->Draw(this->texture, &src, &this->center, &gameCamera.intoCamera(this->currPosition, this->FaceDirection), D3DCOLOR_XRGB(255, 255, 255));
	this->SpriteHandler->End();
}
void cutman::ProcessCollision(collisionType type, Sprite * sprite)
{
	if (type == TOP)
	{
		this->Vx = 0;
		this->Vx = this->Vx + sprite->getVx();
		this->Vy = 0;
	}
	if (type == RIGHT)
	{
		this->Vx = 0.2;
		this->Vy = 0.18;
	}
}
void cutman::UpdatePosition()
{
	this->currPosition.x += this->Vx * (1000.0 / 60);
	this->currPosition.y += this->Vy * (1000.0 / 60);
}
void cutman::UpdateVelocity()
{
	this->Vx += Ax * (1000.0 / 60);
	this->Vy += Ay * (1000.0 / 60);
}
cutman::~cutman()
{

}