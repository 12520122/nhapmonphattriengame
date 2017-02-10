#include "bubble.h"
#define IMG_LOCATION_BUBBLE_FLY "./anhlamgame/BossCutMan/enemy_bubble_blue.png"
#define BUBBLE_FLY_RATE 7
#define MAX_FLY_INDEX 2
bubble::bubble(LPDIRECT3DDEVICE9 d3ddev, LPD3DXSPRITE SpriteHandler) :Sprite(d3ddev, SpriteHandler)
{
	this->currState = FLY;
	this->Vx = 0.05;
	this->Vy = 0;
	this->currPosition = { 200, 300, 0 };

}
void bubble::UpdateRender(LARGE_INTEGER stp)
{
	this->currIndexState++;
}
void bubble::Render(camera gameCamera)
{
	this->SpriteHandler->Begin(D3DXSPRITE_ALPHABLEND);
	this->SpriteHandler->Draw(this->texture, &this->getRectState(this->currState), &this->getCenterState(this->currState), &gameCamera.intoCamera(this->currPosition, this->FaceDirection), D3DCOLOR_XRGB(255, 255, 255));
	this->SpriteHandler->End();
}
void bubble::ProcessCollision(collisionType type, Sprite * sprite)
{

}
bool bubble::Init()
{
	HRESULT result;
	D3DXIMAGE_INFO ImageSprite;
	//FLY
	result = D3DXGetImageInfoFromFile(IMG_LOCATION_BUBBLE_FLY, &ImageSprite);
	result = D3DXCreateTextureFromFileEx(this->d3ddev, IMG_LOCATION_BUBBLE_FLY, ImageSprite.Width, ImageSprite.Height,
		1, D3DUSAGE_DYNAMIC, D3DFMT_UNKNOWN, D3DPOOL_DEFAULT, D3DX_DEFAULT, D3DX_DEFAULT, D3DCOLOR_XRGB(0, 0, 0), &ImageSprite, NULL,
		&this->texture);
	return true;
}
void bubble::UpdateVelocity()
{
	this->Vx += Ax * (1000.0 / 60);
	this->Vy += Ay * (1000.0 / 60);
}
void bubble::UpdatePosition()
{
	this->currPosition.x += this->Vx * (1000.0 / 60);
	this->currPosition.y += this->Vy * (1000.0 / 60);
}
D3DXVECTOR3 bubble::getCenterState(BubbleState state)
{
	D3DXVECTOR3 center;
	switch (state)
	{
	case FLY:
	{
		center.x = 8;
		center.y = 10;
		center.z = 0;
		break;
	}
	default:
		break;
	}
	return center;
}
RECT bubble::getRectState(BubbleState state)
{
	RECT currRect;
	switch (state)
	{
	case FLY:
	{
		this->currIndexState = this->currIndexState % (BUBBLE_FLY_RATE*MAX_FLY_INDEX);
		if (BUBBLE_FLY_RATE > currIndexState && currIndexState >= 0)
		{
			currRect.top = 0;
			currRect.left = 0;
			currRect.bottom = 20;
			currRect.right = 16;
		}
		if (2 * BUBBLE_FLY_RATE > currIndexState && currIndexState >= BUBBLE_FLY_RATE)
		{
			currRect.top = 0;
			currRect.left = 16;
			currRect.bottom = 20;
			currRect.right = 32;
		}
		break;
	}
	default:
		break;
	}
	return currRect;
}
bubble::~bubble()
{

}